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
         FluentMeta AggregateMetaData::addFieldMeta(int32_t fieldId, FieldStateEnum::FieldState const &fieldState, std::string const &def)
         {
            FieldMeta fm(fieldId, fieldState, def, 0);
            this->fieldMetaData.push_back(fm);
            FluentMeta flu(*this, fm, this->fieldMetaData.size()-1);
            return flu;
         };

         void AggregateMetaData::addFieldMetaToAllVersions(int32_t fieldId, FieldStateEnum::FieldState const &fieldState, std::string const &def)
         {
            FieldMeta fm(fieldId, fieldState, def, BaseAggregate::InAllVersions);
            this->fieldMetaData.push_back(fm);
            this->versionMetaData[0].fieldMetaDataI.push_back(this->fieldMetaData.size() - 1);
         };

         FluentMeta AggregateMetaData::addAggMeta(int32_t fieldId, FieldStateEnum::FieldState const &fieldState, int16_t childVer)
         {
            FieldMeta fm(fieldId, fieldState, 0, childVer);
            this->fieldMetaData.push_back(fm);
            FluentMeta flu(*this, fm, this->fieldMetaData.size() - 1);
            return flu;
         };

         void AggregateMetaData::addAggMetaToAllVersions(int32_t fieldId, FieldStateEnum::FieldState const &fieldState, int16_t childVer)
         {
            FieldMeta fm(fieldId, fieldState, BaseAggregate::InAllVersions, childVer);
            this->fieldMetaData.push_back(fm);
            this->versionMetaData[0].fieldMetaDataI.push_back(this->fieldMetaData.size() - 1);
         }

         void AggregateMetaData::addField(int16_t fieldId, std::string const &fieldName, TypeEnum::Type const &fieldType)
         {
            FieldInfo fi = FieldInfo(fieldId, fieldName, fieldType);
            fieldInfo.push_back(fi);
         }

         void AggregateMetaData::addField(int16_t fieldId, std::string const &fieldName, TypeEnum::Type const &fieldType, TypeEnum::Type const &fieldSubType = TypeEnum::EmptyType)
         {
            FieldInfo fi = FieldInfo(fieldId, fieldName, fieldType, fieldSubType);
            fieldInfo.push_back(fi);
         }

         void AggregateMetaData::addAggField(int16_t fieldId, std::string const &fieldName)
         {
            FieldInfo fi = FieldInfo(fieldId, fieldName, TypeEnum::ObjectType);
            fieldInfo.push_back(fi);
         }

         FluentComputeRule AggregateMetaData::addComputeRule(std::string const &id, int16_t fieldId, std::string const &condition, std::string const &expression)
         {
            ComputeRule cr(id, fieldId, condition, expression);
            this->computeRules.push_back(cr);
            FluentComputeRule cm(*this, cr, this->computeRules.size() - 1);
            return cm;
         }

         FluentAssessmentRule AggregateMetaData::addAssessmentRule(std::string const &ruleId, std::string const &stringId, std::string const &condition, std::string const &expression)
         {
            AssessmentRule ar(ruleId, stringId, condition, expression);
            this->assessmentRules.push_back(ar);
            FluentAssessmentRule cm(*this, ar, this->assessmentRules.size() - 1);
            return cm;
         }

         FluentVersionChangeRule AggregateMetaData::addVersionChangeRule(int32_t fieldId, int16_t toVersion, std::string condition, std::string expression)
         {
            VersionChangeRule vr(fieldId, toVersion, condition, expression);
            this->versionChangeRules.push_back(vr);
            FluentVersionChangeRule fl(*this, vr, this->versionChangeRules.size() - 1);
            return fl;
         }
      }
   }
}