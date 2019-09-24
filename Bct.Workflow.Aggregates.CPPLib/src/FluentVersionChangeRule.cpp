#include "FluentVersionChangeRule.h"

#include <vector>
#include "VersionChangeRule.h"

namespace Bct
{
   namespace Workflow
   {
      namespace Aggregates
      {
         FluentVersionChangeRule::FluentVersionChangeRule(AggregateMetaData &aggMeta, VersionChangeRule &vcRule, size_t position) :
            _vcRule(vcRule), _aggMeta(aggMeta), _position(position)
         {
         };

         FluentVersionChangeRule &FluentVersionChangeRule::toVersion(int16_t ver)
         {
            int16_t i = static_cast<int16_t>(_position);
            _aggMeta.versionMetaData[ver].versionChangeRulesI.push_back(i);
            return *this;
         }
      }
   }
}
