#pragma once

#include <string>
#include <vector>
#include <map>
#include "VersionInfo.h"
#include "FieldMeta.h"
#include "AssessmentRule.h"
#include "ComputeRule.h"

namespace Bct
{
   namespace Workflow
   {
      namespace Aggregates
      {
         /// <summary>
         /// Metadata across all versions. 
         /// 
         /// Each type of metadata is stored sparsely in a vector of that type. Each metadata item in these vectors
         /// contains the version index that metadata item is associated with. When an aggregate is constucted for a current
         /// version, the aggregate constructor searches for metadata items associated with the current version and initializes
         /// the aggregate with that metadata.
         /// </summary>
         class AggregateMetaData
         {
         public:
            std::vector <VersionInfo> versionInfo;
            std::vector<FieldMeta> fieldMetaData;
            std::vector<AssessmentRule> assessmentRules;
            std::vector<ComputeRule> computeRules;
         };
      }
   }
}