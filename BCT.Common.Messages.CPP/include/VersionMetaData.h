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
         struct VersionMetaData
         {
            VersionInfo versionInfo;
            std::vector<FieldMeta> fieldMetaData;
            std::vector<AssessmentRule> assessmentRules;
            std::vector<ComputeRule> computeRules;
         };
      }
   }
}