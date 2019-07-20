#include "BaseAggregate.h"

#include <stdint.h>
#include <sstream>

#include "FieldStateEnum.h"
#include "RPNEvaluator.h"
#include "AssessmentRule.h"
#include "AssessmentResult.h"


namespace Bct
{
   namespace Workflow
   {
      namespace Aggregates
      {
         BaseAggregate::BaseAggregate(const std::string &version, AggregateMetaData * metaData) :
            _version(version), _aggregateMetaData(*metaData)
         {
         }

         BaseAggregate::BaseAggregate(AggregateMetaData *metaData) :
            _ver(BaseAggregate::UseMostRecentVersion), _aggregateMetaData(*metaData)
         {
         }

         BaseAggregate::BaseAggregate(const std::string &fieldName, AggregateMetaData * metaData, BaseAggregate * parent) :
            _fieldName(fieldName), _aggregateMetaData(*metaData), _parent(parent)
         {
         }

         FieldMeta &BaseAggregate::findFieldMeta(int16_t parentVer)
         {
            // check metadata marked version or all versions in the version 0 vector
            std::vector<int16_t> &fmi0 = _parent->MetaData().versionMetaData[0].fieldMetaDataI; // indirection vector for version 0 / all versions
            if (fmi0.size() > 0)
            {
               for (size_t i = 0; i < fmi0.size(); i++)
               {
                  FieldMeta &fm = _parent->MetaData().fieldMetaData[fmi0[i]]; // indirection
                  if (fm.FieldName() == _fieldName)
                  {
                     if (fm._parentVer == BaseAggregate::InAllVersions || (parentVer == 0 && fm._parentVer == 0))
                     {
                        return fm;
                     }
                     else
                     {
                        break;
                     }
                  }
               }
            }

            std::vector<int16_t> &fmi = _parent->MetaData().versionMetaData[parentVer].fieldMetaDataI; // indirection vector for version
            if (fmi.size() > 0)
            {
               for (size_t i = 0; i < fmi.size(); i++)
               {
                  FieldMeta &fm = _parent->MetaData().fieldMetaData[fmi[i]]; // indirection
                  if (fm.FieldName() == _fieldName && fm._parentVer <= parentVer)
                  {
                     return fm;
                  }
               }
            }
            throw "error: metadata missing requested version of aggregate";  // TODO
         }

         void BaseAggregate::SyncChildVersion(int16_t parentVer)
         {
            FieldMeta &meta = findFieldMeta(parentVer);
            _ver = meta._childVer;
            _version = _aggregateMetaData.versionInfo[_ver].Version();
         }

         void BaseAggregate::SyncVersion()
         {
            if (_parent == nullptr)
            {
               if (_ver == BaseAggregate::UseMostRecentVersion) // seek most recent version
               {
                  AggregateMetaData &thisMd = _aggregateMetaData;
                  _ver = static_cast<uint16_t>(thisMd.versionInfo.size() - 1);
                  _version = thisMd.versionInfo[_ver].Version();
               }
               else // use constuctor value
               {
                  bool found = false;
                  AggregateMetaData &thisMd = _aggregateMetaData;
                  for (size_t i = 0; i < thisMd.versionInfo.size(); i++)
                  {
                     if (thisMd.versionInfo[i].Version() == _version)
                     {
                        _ver = (int16_t)i;
                        found = true;
                     }
                  }
                  if (!found)
                  {
                     throw "error: invalid version"; // TODO: internationalize - User Story 126598
                  }
               }
            }

            // initialize fields to current version
            for (size_t i = 0; i < _fieldList.size(); i++)
            {
               _fieldList[i]->initMetaData(Ver());
            }
            // initialize nested aggregates to current version of parent
            for (size_t i = 0; i < _aggList.size(); i++)
            {
               _aggList[i]->SyncChildVersion(Ver());
            }
         }


         /**
          * Destructor
          */
         BaseAggregate::~BaseAggregate() {};

         const std::string& BaseAggregate::getVersion() const
         {
            return _version;
         };

         void BaseAggregate::UpdateCalculatedFields()
         {
            // populate variable map
            std::map<std::string, RPNVariable> varMap;
            for (size_t i = 0; i < _fieldList.size(); i++)
            {
               AbstractField *f = _fieldList[i];
               std::string strVal;
               if (f->State() == FieldStateEnum::NotSet)
               {
                  strVal = "$Notset"; // TODO make sure this is correct - User Story 126600
               }
               else if (f->State() == FieldStateEnum::Unavailable)
               {
                  strVal = "$Unavailable"; // TODO make sure this is correct - User Story 126600
               }
               else
               {
                  strVal = f->ComputedValueString();
               }

               FieldStateEnum::FieldState &state = f->StateRef();
               varMap[f->FieldName()] = RPNVariable(f->FieldName(), f->Type(), strVal, state, f->FieldSetCounter());
            }
 
            std::vector<int16_t> &cRulesV = _aggregateMetaData.versionMetaData[Ver()].computeRulesI;
            for (size_t iRule = 0; iRule < cRulesV.size(); iRule++) // over rules in current version
            {
               ComputeRule cRule = _aggregateMetaData.computeRules[cRulesV[iRule]]; // indirection
               for (size_t iField = 0; iField < _fieldList.size(); iField++) // over fields
               {
                  // find field calcuation in current version
                  AbstractField *f = _fieldList[iField];
                  FieldStateEnum::FieldState state = f->State();
                  TypeEnum::Type type = f->Type();
                  std::string fieldName = f->FieldName();
                  std::string ruleFieldName = cRule.FieldName();
                  if (fieldName == ruleFieldName)
                  {
                     std::string condition = cRule.Condition();
                     std::string expression = cRule.Expression();
                     std::string answerValue;
                     TypeEnum::Type answerType;
                     RPNEvaluator evaluator;
                     evaluator.EvaluateRPNExpression(condition, varMap, answerType, answerValue);
                     if ("true" == answerValue)
                     {
                        evaluator.EvaluateRPNExpression(expression, varMap, answerType, answerValue);
                        f->ComputedValueString(answerValue);
                     }
                  }
               }
            }
         }

         AssessmentResult BaseAggregate::Assess()
         {
            AssessmentResult result;

            // populate variable map
            std::map<std::string, RPNVariable> varMap;
            for (size_t i = 0; i < _fieldList.size(); i++)
            {
               AbstractField *f = _fieldList[i];
               std::string strVal;
               if (f->State() == FieldStateEnum::NotSet)
               {
                  strVal = "$Notset"; // TODO make sure this is correct - User Story 126600
               }
               else if (f->State() == FieldStateEnum::Unavailable)
               {
                  strVal = "$Unavailable"; // TODO make sure this is correct - User Story 126600
               }
               else
               {
                  strVal = f->ComputedValueString();
               }

               FieldStateEnum::FieldState &state = f->StateRef();
               varMap[f->FieldName()] = RPNVariable(f->FieldName(), f->Type(), strVal, state, f->FieldSetCounter());
            }

            std::vector<int16_t> &aRulesV = _aggregateMetaData.versionMetaData[Ver()].assessmentRulesI;
            for (size_t j = 0; j < aRulesV.size(); j++)
            {
               AssessmentRule aRule = _aggregateMetaData.assessmentRules[aRulesV[j]]; // indirection
               std::string condition = aRule.Condition();
               std::string expression = aRule.Expression();
               std::string answerValue;
               TypeEnum::Type answerType;
               RPNEvaluator evaluator;
               evaluator.EvaluateRPNExpression(condition, varMap, answerType, answerValue);
               if ("true" == answerValue)
               {
                  evaluator.EvaluateRPNExpression(expression, varMap, answerType, answerValue);
                  if (answerValue != "true")
                  {
                     result.addError(aRule.RuleId(), answerValue);
                  }
               }
            }
            return result;
         }

         const uint32_t &BaseAggregate::FieldSetCounter()
         {
            _fieldSetCounter++;
            return _fieldSetCounter;
         }

         AggregateMetaData & BaseAggregate::MetaData()
         {
            return _aggregateMetaData;
         }

         std::vector<AbstractField*> & BaseAggregate::FieldList()
         {
            return _fieldList;
         }

         std::vector<AbstractAggregate*> & BaseAggregate::AggList()
         {
            return _aggList;
         }

         int32_t BaseAggregate::Ver() const
         {
            return _ver;
         }

         const std::string & BaseAggregate::Version() const
         {
            return _version;
         }

      }
   }
}