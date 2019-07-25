#pragma once

#include <string>
#include <vector>
#include <map>
#include "VersionInfo.h"
#include "FieldMeta.h"
#include "AssessmentRule.h"
#include "ComputeRule.h"
#include "VersionMetaData.h"

namespace Bct
{
   namespace Workflow
   {
      namespace Aggregates
      {
         /// <summary>
         /// Metadata across all versions. 
         /// 
         /// Each type of metadata is stored sparsely in a vector of that type.
         /// </summary>
         class AggregateMetaData
         {
         public:
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