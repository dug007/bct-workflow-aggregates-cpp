#include <vector>
#include "FluentMeta.h"
#include "FluentComputeRule.h"
#include "ComputeRule.h"

namespace Bct
{
   namespace Workflow
   {
      namespace Aggregates
      {
         FluentComputeRule::FluentComputeRule(AggregateMetaData &aggMeta, ComputeRule &computeRule, size_t position) :
            _computeRule(computeRule), _aggMeta(aggMeta), _position(position)
         {
         };

         FluentComputeRule &FluentComputeRule::toVersion(int16_t ver)
         {
            int16_t i = static_cast<int16_t>(_position);
            _aggMeta.versionMetaData[ver].computeRulesI.push_back(i);
            return *this;
         }
      }
   }
}
