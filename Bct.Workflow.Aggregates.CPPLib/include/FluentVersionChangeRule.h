#pragma once

#include "VersionChangeRule.h"
#include "AggregateMetaData.h"

namespace Bct
{
   namespace Workflow
   {
      namespace Aggregates
      {
         class AggregateMetaData;

         class FluentVersionChangeRule
         {
         public:
            FluentVersionChangeRule(AggregateMetaData &aggMeta, VersionChangeRule &vcRule, size_t position);
            FluentVersionChangeRule &toVersion(int16_t ver);
         private:
            VersionChangeRule &_vcRule;
            AggregateMetaData &_aggMeta;
            size_t _position;
         };
      }
   }
}