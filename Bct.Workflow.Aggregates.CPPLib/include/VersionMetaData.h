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
         /// Each type of metadata is stored in this class in a vector of that type. Each instance of this class is stored
         /// in a vector in AggregateMetaData. The index in that vector is the ver, so each instance of this class
         /// is the metadata for that ver.
         /// </summary>
         class VersionMetaData
         {
         public:
            /// <summary>
            /// Index into a field metadata item. 
            /// </summary>
            std::vector<int16_t> fieldMetaDataI;
            /// <summary>
            /// Index into an assessment rule metadata item.
            /// </summary>
            std::vector<int16_t> assessmentRulesI;
            /// <summary>
            /// Index into a compute rule metadata item.
            /// </summary>
            std::vector<int16_t> computeRulesI;

         };
      }
   }
}