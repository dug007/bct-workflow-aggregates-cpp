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
         /// Metadata for single version. 
         /// 
         /// Each type of metadata is stored sparsely in a vector of that type. 
         /// </summary>
         class VersionMetaData
         {
         public:
            std::vector<FieldMeta> fieldMetaData;
            std::vector<AssessmentRule> assessmentRules;
            std::vector<ComputeRule> computeRules;
         };
      }
   }
}