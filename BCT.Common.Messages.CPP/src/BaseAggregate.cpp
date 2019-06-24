#include "BaseAggregate.h"

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
            _version = std::to_string(_major) + '.' + std::to_string(_minor) + '.' + std::to_string(_patch);
            return _version;
         };

         void BaseAggregate::UpdateCalculatedFields()
         {
            size_t count = _fieldList.size();
            for (size_t i = 0; i < count; i++)
            {
               AbstractField *f = _fieldList[i];
               std::string val = f->ValueString();
               FieldTypeEnum::FieldType type = f->FieldType();
               FieldStateEnum::FieldState state = f->State();
               std::string fieldName = f->FieldName();
               std::vector<ComputeRule> cRules = _aggregateMetaData[_ver].computeRules;
               if (state == FieldStateEnum::Computed)
               {
                  for (size_t j = 0; j < cRules.size(); j++)
                  {
                     auto cRule = cRules[j];
                     std::string condition = cRule.Condition();
                     std::string expression = cRule.Expression();
                     std::string ruleFieldName = cRule.FieldName();
                     if (fieldName == ruleFieldName)
                     {
                        // TODO do calculation
                        f->ValueString("999");
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
                  _ver = i;
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