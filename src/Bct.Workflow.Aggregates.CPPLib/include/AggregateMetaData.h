#pragma once

#include <string>
#include <vector>
#include <map>
#include <stdint.h>
#include "VersionInfo.h"
#include "FieldMeta.h"
#include "AssessmentRule.h"
#include "ComputeRule.h"
#include "VersionChangeRule.h"
#include "VersionMetaData.h"
#include "FluentMeta.h"
#include "FieldInfo.h"
#include "FluentComputeRule.h"
#include "FluentAssessmentRule.h"
#include "FluentVersionChangeRule.h"

namespace Bct
{
   namespace Workflow
   {
      namespace Aggregates
      {
         class FluentMeta;
         class FluentVersionChangeRule;

         /// <summary>
         /// Metadata across all versions. 
         /// 
         /// Each type of metadata is stored sparsely in a vector of that type.
         /// </summary>
         class AggregateMetaData
         {
         public:
            /// <summary>
            /// Adds a version to metadata. The first time this is called represents version 0, the second represents version 1, and so forth.
            /// </summary>
            /// <param name="version">The version string of the added version.</param>
            void addVersion(std::string const &version);

            /// <summary>
            /// Adds a field to metadata. This should be called in the same order that the fields are declared.
            /// </summary>
            /// <param name="fieldId">Field id.</param>
            /// <param name="fieldName">Field name.</param>
            /// <param name="fieldType">Field type.</param>
            void addField(int16_t fieldId, std::string const &fieldName, TypeEnum::Type const &fieldType);

            /// <summary>
            /// Adds a field to metadata. This should be called in the same order that the fields are declared.
            /// </summary>
            /// <param name="fieldId">Field id.</param>
            /// <param name="fieldName">Field name.</param>
            /// <param name="fieldType">Field type.</param>
            /// <param name="fieldSubType">Field subtype.</param>
            void addField(int16_t fieldId, std::string const &fieldName, TypeEnum::Type const &fieldType, TypeEnum::Type const &fieldSubType);


            /// <summary>
            /// Adds a aggregate field to metadata. This should be called in the same order that the fields are declared.
            /// </summary>
            /// <param name="fieldId">Field id.</param>
            /// <param name="fieldName">Field name.</param>
            void addAggField(int16_t fieldId, std::string const &fieldName);

            /// <summary>
            /// Adds a field metadata item. This must be followed immediately with .toVersion() to specify the versions.
            /// Instead a FluentMeta opject is returned to allow fluent adding via FluentMeta::toVersion().
            /// </summary>
            /// <param name="fieldId">The field id for this metadata item.</param>
            /// <param name="fieldState">The field state for this metadata item.</param>
            /// <param name="def">The default value for this metadata item.</param>
            /// <returns>The FluentMeta for continued fluent operations.</returns>
            FluentMeta addFieldMeta(int32_t fieldId, FieldStateEnum::FieldState const &fieldState, std::string const &def);

            /// <summary>
            /// Adds a field metadata item to all versions.
            /// </summary>
            /// <param name="fieldId">The field id for this metadata item.</param>
            /// <param name="fieldState">The field state for this metadata item.</param>
            /// <param name="def">The default value for this metadata item.</param>
            void addFieldMetaToAllVersions(int32_t fieldId, FieldStateEnum::FieldState const &fieldState, std::string const &def);

            /// <summary>
            /// Adds an aggregate metadata item. This must be followed immediately with .toVersion() to specify the versions.
            /// Instead a FluentMeta opject is returned to allow fluent adding via FluentMeta::toVersion().
            /// </summary>
            /// <param name="fieldId">The field name for this metadata item.</param>
            /// <param name="fieldState">The field state for this metadata item.</param>
            /// <param name="childVer">The version for this metadata item.</param>
            /// <returns>The FluentMeta for continued fluent operations.</returns>
            FluentMeta addAggMeta(int32_t fieldId, FieldStateEnum::FieldState const &fieldState, int16_t childVer);

            /// <summary>
            /// Adds an aggregate field metadata item to to all versions.
            /// </summary>
            /// <param name="fieldId">The field id for this metadata item.</param>
            /// <param name="fieldState">The field state for this metadata item.</param>
            /// <param name="childVer">The version for this metadata item.</param>
            void addAggMetaToAllVersions(int32_t fieldId, FieldStateEnum::FieldState const &fieldState, int16_t childVer);

            /// <summary>
            /// Adds an compute rule. This must be followed immediately with .toVersion() to specify the versions.
            /// </summary>
            /// <param name="id">The id for this metadata item.</param>
            /// <param name="fieldId">The field id for this metadata item.</param>
            /// <param name="condition">The condition expression for this compute rule.</param>
            /// <param name="expression">The compute expression for this compute rule.</param>
            /// <returns>The FluentMeta for continued fluent operations.</returns>
            FluentComputeRule addComputeRule(std::string const &id, int16_t fieldId, std::string const &condition, std::string const &expression);

            /// <summary>
            /// Adds an assessment rule. This must be followed immediately with .toVersion() to specify the versions.
            /// </summary>
            /// <param name="ruleId">The assessmint rule id.</param>
            /// <param name="stringId">The string id.</param>
            /// <param name="condition">The condition expression for this assessment rule.</param>
            /// <param name="expression">The compute expression for this assessment rule.</param>
            /// <returns>The FluentMeta for continued fluent operations.</returns>
            FluentAssessmentRule addAssessmentRule(std::string const &ruleId, std::string const &stringId, std::string const &condition, std::string const &expression);

            /// <summary>
            /// Adds a version change rule for a specified field and target version. This must be followed immediately with .toVersion() 
            /// to specify the versions.
            /// </summary>
            /// <param name="fieldId">The assessmint rule id.</param>
            /// <param name="toVersion">The version id to convert to.</param>
            /// <param name="condition">The condition expression for this version change rule.</param>
            /// <param name="expression">The compute expression for this version change.</param>
            /// <returns>The FluentMeta for continued fluent operations.</returns>
            FluentVersionChangeRule addVersionChangeRule(int32_t fieldId, int16_t toVersion, std::string condition, std::string expression);

            /// <summary>
            /// Field info. The vector is ordered by increasing field id.
            /// </summary>
            std::vector <FieldInfo> fieldInfo;

            /// <summary>
            /// Version info for versions. The vector is ordered by increasing version. The vector index IS the ver value.
            /// </summary>
            std::vector <VersionInfo> versionInfo;
            /// <summary>
            /// Version metadata for specific versions. The vector is ordered by increasing version. The vector index IS the ver value.
            /// </summary>
            std::vector<VersionMetaData> versionMetaData;
            /// <summary>
            /// Field metadata. The vector is ordered by increasing version in major order, and field in minor order. The vector index IS NOT the ver value. 
            /// Searching backwards matching both version and field name results in locating the most recent version of a particular field first.
            /// </summary>
            std::vector<FieldMeta> fieldMetaData;
            /// <summary>
            /// Assessment rule metadata. The vector order is NOT the ver value.
            /// </summary>
            std::vector<AssessmentRule> assessmentRules;
            /// <summary>
            /// Compute rule metadata.The vector order is NOT the ver value.
            /// </summary>
            std::vector<ComputeRule> computeRules;
            /// <summary>
            /// Version change rule metadata. The vector order is NOT the ver value.
            /// </summary>
            std::vector<VersionChangeRule> versionChangeRules;
         };
      }
   }
}