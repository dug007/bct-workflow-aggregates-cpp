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
 
            for (size_t i = 0; i < _fieldList.size(); i++)
            {
               AbstractField *f = _fieldList[i];
               FieldStateEnum::FieldState state = f->State();
               TypeEnum::Type type = f->Type();
               std::string fieldName = f->FieldName();
               std::vector<ComputeRule> cRules = _aggregateMetaData.computeRules;
               for (size_t j = 0; j < cRules.size(); j++)
               {
                  ComputeRule cRule = cRules[j];
                  std::string ruleFieldName = cRule.FieldName();
                  if (fieldName == ruleFieldName)
                  {
                     if (cRule.InVersion(Ver()))
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
         }

         AssessmentResult BaseAggregate::Assess(const std::string &id)
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

            std::vector<AssessmentRule> aRules = _aggregateMetaData.assessmentRules;
            for (size_t j = 0; j < aRules.size(); j++)
            {
               AssessmentRule aRule = aRules[j];
               if (aRule.RuleId() == id || id == "*")
               {
                  if (aRule.InVersion(Ver()))
                  {
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
                  else if (id != "*")
                  {
                     throw "error: assessment rule not in version";  // TODO: assessment rule not in version - User Story 127481
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