#include "BaseAggregate.h"
#include "RPNEvaluator.h"

using namespace BCTCommonUtilitiesRPNEvaluatorCPPWin;

namespace Bct
{
   namespace Workflow
   {
      namespace Aggregates
      {
         BaseAggregate::BaseAggregate(const int16_t major, const int16_t minor, const int16_t patch) : _major(major), _minor(minor), _patch(patch)
         {
         }
         /**
          * Destructor
          */
         BaseAggregate::~BaseAggregate() {};

         const std::string& BaseAggregate::getVersion()
         {
            // TODO: remove _version?
            std::stringstream ss;
            ss << _major << '.' << _minor << '.' << _patch;
            _version = ss.str();
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
                  strVal = f->ValueString();
               }
               varMap[f->FieldName()] = RPNVariable(f->FieldName(), f->TypeCode(), strVal);
            }
 
            for (size_t i = 0; i < _fieldList.size(); i++)
            {
               AbstractField *f = _fieldList[i];
               FieldStateEnum::FieldState state = f->State();
               if (state == FieldStateEnum::Computed)
               {
                  std::string val = f->ValueString();
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
                        evaluator.EvaluateRPNExpression(expression, varMap, answerType, answerValue);
                        // TODO : check answer type?
                        f->ValueString(answerValue);
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
               if (ad[i].versionInfo.Major() == Major() && ad[i].versionInfo.Minor() == Minor() && ad[i].versionInfo.Patch() == Patch())
               {
                  _ver = (int16_t)i;
                  return;
               }
            }
            throw "error: invalid version"; // TODO localize
         }

         const int16_t BaseAggregate::Major()
         {
            return _major;
         }
         const int16_t BaseAggregate::Minor()
         {
            return _minor;
         }
         const int16_t BaseAggregate::Patch()
         {
            return _patch;
         }

      }
   }
}