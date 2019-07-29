#pragma once

#include <string>
#include <vector>
#include <map>
#include "VersionInfo.h"
#include "FieldMeta.h"
#include "AssessmentRule.h"
#include "ComputeRule.h"
#include "VersionMetaData.h"
#include "FluentMeta.h"

namespace Bct
{
   namespace Workflow
   {
      namespace Aggregates
      {
         class FluentMeta;

         /// <summary>
         /// Metadata across all versions. 
         /// 
         /// Each type of metadata is stored sparsely in a vector of that type.
         /// </summary>
         class AggregateMetaData
         {
         public:
            /// <summary>
            /// Adds a verion to metadata. The first time this is called represents version 0, the second represents version 1, and so forth.
            /// </summary>
            /// <param name="version">The version string of the added version.</param>
            void addVersion(std::string const &version);

            /// <summary>
            /// Adds a field metadata item to the AggregateMetaData::fieldMetaData vector. The versionMetaDataI vector is not updated yet.
            /// Instead a FluentMeta opject is returned to allow fluent adding via FluentMeta::toVersion().
            /// </summary>
            /// <param name="fieldName">The field name for this metadata item.</param>
            /// <param name="fieldState">The field state for this metadata item.</param>
            /// <param name="def">The default value for this metadata item.</param>
            /// <returns>The FluentMeta for continued fluent operations.</returns>
            FluentMeta addFieldMeta(std::string const &fieldName, FieldStateEnum::FieldState const &fieldState, std::string const &def);

            /// <summary>
            /// Adds a field metadata item to the AggregateMetaData::fieldMetaData vector and updates the versionMetaDataI vector for all versions.
            /// </summary>
            /// <param name="fieldName">The field name for this metadata item.</param>
            /// <param name="fieldState">The field state for this metadata item.</param>
            /// <param name="def">The default value for this metadata item.</param>
            void addFieldMetaToAllVersions(std::string const &fieldName, FieldStateEnum::FieldState const &fieldState, std::string const &def);

            /// <summary>
            /// Adds an aggregate metadata item to the AggregateMetaData::fieldMetaData vector. The versionMetaDataI vector is not updated yet.
            /// Instead a FluentMeta opject is returned to allow fluent adding via FluentMeta::toVersion().
            /// </summary>
            /// <param name="fieldName">The field name for this metadata item.</param>
            /// <param name="fieldState">The field state for this metadata item.</param>
            /// <param name="childVer">The version for this metadata item.</param>
            /// <returns>The FluentMeta for continued fluent operations.</returns>
            FluentMeta addAggMeta(std::string const &fieldName, FieldStateEnum::FieldState const &fieldState, int16_t childVer);

            /// <summary>
            /// Adds an aggregate field metadata item to the AggregateMetaData::fieldMetaData vector and updates the versionMetaDataI vector for all versions.
            /// </summary>
            /// <param name="fieldName">The field name for this metadata item.</param>
            /// <param name="fieldState">The field state for this metadata item.</param>
            /// <param name="childVer">The version for this metadata item.</param>
            void addAggMetaToAllVersions(std::string const &fieldName, FieldStateEnum::FieldState const &fieldState, int16_t childVer);

            void clear();

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
         };
      }
   }
}