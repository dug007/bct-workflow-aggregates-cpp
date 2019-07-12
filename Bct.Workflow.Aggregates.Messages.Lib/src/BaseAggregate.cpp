#include "BaseAggregate.h"

#include <stdint.h>
#include <sstream>

#include "FieldStateEnum.h"
#include "RPNEvaluator.h"


namespace Bct
{
   namespace Workflow
   {
      namespace Aggregates
      {
         BaseAggregate::BaseAggregate(const std::string version) : _version(version)
         {
         }
         /**
          * Destructor
          */
         BaseAggregate::~BaseAggregate() {};

         const std::string& BaseAggregate::getVersion()
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
               std::vector<ComputeRule> cRules = _aggregateMetaData[_ver].computeRules;
               for (size_t j = 0; j < cRules.size(); j++)
               {
                  ComputeRule cRule = cRules[j];
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

         void BaseAggregate::SyncCurrentVersion()
         {
            std::vector<VersionMetaData> &ad = _aggregateMetaData;
            for (size_t i = 0; i < ad.size(); i++)
            {
               if (ad[i].versionInfo.Version() == _version)
               {
                  _ver = (int16_t)i;
                  return;
               }
            }
            throw "error: invalid version"; // TODO: internationalize - User Story 126598
         }

         uint32_t BaseAggregate::FieldSetCounter()
         {
            _fieldSetCounter++;
            return _fieldSetCounter;
         }

         std::vector<VersionMetaData> & BaseAggregate::AggregateMetaData()
         {
            return _aggregateMetaData;
         }

         std::vector<AbstractField*> & BaseAggregate::FieldList()
         {
            return _fieldList;
         }

         int32_t BaseAggregate::Ver()
         {
            return _ver;
         }

         const std::string & BaseAggregate::Version()
         {
            return _version;
         }

      }
   }
}