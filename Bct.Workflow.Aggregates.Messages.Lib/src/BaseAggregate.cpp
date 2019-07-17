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
            _ver(-1), _aggregateMetaData(*metaData)
         {
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

         void BaseAggregate::SyncCurrentVersion()
         {
            AggregateMetaData &ad = _aggregateMetaData;
            if (_ver == -1) // seek most recent version
            {
               _ver = static_cast<uint16_t>(ad.versionInfo.size()-1);
               _version = ad.versionInfo[_ver].Version();
            }
            else
            {
               bool found = false;
               for (size_t i = 0; i < ad.versionInfo.size(); i++)
               {
                  if (ad.versionInfo[i].Version() == _version)
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

            // initialize fields to current version
            for (size_t i = 0; i < _fieldList.size(); i++)
            {
               _fieldList[i]->initMetaData(Ver());
            }
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