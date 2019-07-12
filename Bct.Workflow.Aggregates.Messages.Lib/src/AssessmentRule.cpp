#include "AssessmentRule.h"

AssessmentRule::AssessmentRule(std::string ruleId, std::string stringId, std::string condition, std::string expression)
   : _ruleId(ruleId), _stringId(stringId), _condition(condition), _expression(expression)
{
}

std::string AssessmentRule::RuleId() const
{
   return _ruleId;
}

std::string AssessmentRule::StringId() const
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
