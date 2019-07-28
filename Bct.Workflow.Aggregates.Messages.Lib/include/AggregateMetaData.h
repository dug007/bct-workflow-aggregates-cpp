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
            void addVersion(std::string const &version);

            FluentMeta addFieldMeta(std::string const &fieldName, FieldStateEnum::FieldState const &fieldState, std::string const &def);

            void addFieldMetaToAllVersions(std::string const &fieldName, FieldStateEnum::FieldState const &fieldState, std::string const &def);

            FluentMeta addAggMeta(std::string const &fieldName, FieldStateEnum::FieldState const &fieldState, int16_t childVer);

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