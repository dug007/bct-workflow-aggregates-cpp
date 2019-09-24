#include <vector>
#include "FluentMeta.h"
#include "FluentAssessmentRule.h"
#include "AssessmentRule.h"

namespace Bct
{
   namespace Workflow
   {
      namespace Aggregates
      {
         FluentAssessmentRule::FluentAssessmentRule(AggregateMetaData &aggMeta, AssessmentRule &assessmentRule, size_t position) :
            _assessmentRule(assessmentRule), _aggMeta(aggMeta), _position(position)
         {
         };

         FluentAssessmentRule &FluentAssessmentRule::toVersion(int16_t ver)
         {
            int16_t i = static_cast<int16_t>(_position);
            _aggMeta.versionMetaData[ver].assessmentRulesI.push_back(i);
            return *this;
         }
      }
   }
}
