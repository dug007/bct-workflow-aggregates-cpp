#pragma once

#include <string>

class AssessmentRule
{
public:
   AssessmentRule(std::string ruleId, std::string condition, std::string expression) : _ruleId(ruleId), _condition(condition), _expression(expression) {};
   std::string RuleId() { return _ruleId; }
   std::string Condition() { return _condition; }
   std::string Expression() { return _expression; }
private:
   std::string _ruleId;
   std::string _condition;
   std::string _expression;
};

