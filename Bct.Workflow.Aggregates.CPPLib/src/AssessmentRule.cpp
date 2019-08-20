#include "AssessmentRule.h"
#include <sstream>

namespace Bct
{
   namespace Workflow
   {
      namespace Aggregates
      {
         AssessmentRule::AssessmentRule(std::string const &ruleId, std::string const &stringId, std::string const &condition, std::string const &expression)
            : _ruleId(ruleId), _stringId(stringId), _condition(condition), _expression(expression)
         {
         }

         std::string AssessmentRule::RuleId() const
         {
            return _ruleId;
         }

         const std::string &AssessmentRule::StringId() const
         {
            return _stringId;
         }

         std::string AssessmentRule::Condition() const
         {
            return _condition;
         }

         std::string AssessmentRule::Expression() const
         {
            return _expression;
         }
      }
   }
}

