#include "AssessmentRule.h"
#include <sstream>

namespace Bct
{
   namespace Workflow
   {
      namespace Aggregates
      {
         AssessmentRule::AssessmentRule(std::string ruleId, std::string stringId, std::string condition, std::string expression, std::string versions)
            : _ruleId(ruleId), _stringId(stringId), _condition(condition), _expression(expression), _versions(versions)
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

         bool AssessmentRule::InVersion(int16_t ver)
         {
            std::ostringstream ss;
            ss << '.' << ver << '.';
            std::string verStr = ss.str();
            std::size_t f = _versions.find(verStr);
            return (f != std::string::npos);
         }

      }
   }
}

