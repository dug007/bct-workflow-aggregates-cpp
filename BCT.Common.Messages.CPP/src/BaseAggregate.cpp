#include "BaseAggregate.h"
#include "RPNEvaluator.h"

using namespace BCTCommonUtilitiesRPNEvaluatorCPPWin;

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
                  strVal = "$Notset"; // TODO make sure this is correct
               }
               else if (f->State() == FieldStateEnum::Unavailable)
               {
                  strVal = "$Unavailable"; // TODO make sure this is correct
               }
               else
               {
                  strVal = f->ComputedValueString();
               }

               FieldStateEnum::FieldState &state = f->StateRef();
               varMap[f->FieldName()] = RPNVariable(f->FieldName(), f->TypeCode(), strVal, state, f->FieldSetCounter());
            }
 
            for (size_t i = 0; i < _fieldList.size(); i++)
            {
               AbstractField *f = _fieldList[i];
               FieldStateEnum::FieldState state = f->State();
               FieldTypeEnum::FieldType type = f->FieldType();
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
                     TypeCode answerType;
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

         void BaseAggregate::UpdateVer()
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
            throw "error: invalid version"; // TODO localize
         }

         uint32_t BaseAggregate::FieldSetCounter()
         {
            _fieldSetCounter++;
            return _fieldSetCounter;
         }
      }
   }
}