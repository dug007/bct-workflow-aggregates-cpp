#pragma once

#include <string>
#include <vector>
#include <map>
#include "FieldMeta.h"
#include "AssessmentRule.h"
#include "ComputeRule.h"

namespace Bct
{
   namespace Workflow
   {
      namespace Aggregates
      {
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