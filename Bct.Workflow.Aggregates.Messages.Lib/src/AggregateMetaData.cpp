#include "AggregateMetaData.h"
#include <string>
#include <vector>
#include <map>
#include "VersionInfo.h"
#include "FieldMeta.h"
#include "AssessmentRule.h"
#include "ComputeRule.h"
#include "VersionMetaData.h"
#include "FluentMeta.h"
#include "BaseAggregate.h"

namespace Bct
{
   namespace Workflow
   {
      namespace Aggregates
      {
         void AggregateMetaData::addVersion(std::string const &version)
         {
            versionInfo.push_back(VersionInfo(version));
            VersionMetaData vm;
            versionMetaData.push_back(vm);
         }
         FluentMeta AggregateMetaData::addFieldMeta(std::string const &fieldName, FieldStateEnum::FieldState const &fieldState, std::string const &def)
         {
            FieldMeta fm(fieldName, fieldState, def, 0);
            this->fieldMetaData.push_back(fm);
            FluentMeta flu(*this, fm, this->fieldMetaData.size()-1);
            return flu;
         };

         void AggregateMetaData::addFieldMetaToAllVersions(std::string const &fieldName, FieldStateEnum::FieldState const &fieldState, std::string const &def)
         {
            FieldMeta fm(fieldName, fieldState, def, BaseAggregate::InAllVersions);
            this->fieldMetaData.push_back(fm);
            FluentMeta flu(*this, fm, this->fieldMetaData.size() - 1);
            flu.toVersion(0);
         };

         FluentMeta AggregateMetaData::addAggMeta(std::string const &fieldName, FieldStateEnum::FieldState const &fieldState, int16_t childVer)
         {
            FieldMeta fm(fieldName, fieldState, 0, childVer);
            this->fieldMetaData.push_back(fm);
            FluentMeta flu(*this, fm, this->fieldMetaData.size() - 1);
            return flu;
         };

         void AggregateMetaData::addAggMetaToAllVersions(std::string const &fieldName, FieldStateEnum::FieldState const &fieldState, int16_t childVer)
         {
            FieldMeta fm(fieldName, fieldState, BaseAggregate::InAllVersions, childVer);
            this->fieldMetaData.push_back(fm);
            FluentMeta flu(*this, fm, this->fieldMetaData.size() - 1);
            flu.toVersion(0);
         };

         void AggregateMetaData::clear()
         {
            assessmentRules.clear();
            computeRules.clear();
            fieldMetaData.clear();
            versionInfo.clear();
            for (size_t i = 0; i < versionMetaData.size(); i++)
            {
               versionMetaData[i].assessmentRulesI.clear();
               versionMetaData[i].computeRulesI.clear();
               versionMetaData[i].fieldMetaDataI.clear();
            }
            versionMetaData.clear();
         }
      }
   }
}