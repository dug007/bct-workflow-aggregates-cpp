#pragma once

#include "AggregateMetaData.h"
using namespace Bct::Workflow::Aggregates;

namespace Bct
{
   namespace Workflow
   {
      namespace Implementation
      {
         class AssessMetaData
         {
         public:

            AggregateMetaData metaData;

            AssessMetaData();
         };
      }
   }
}
