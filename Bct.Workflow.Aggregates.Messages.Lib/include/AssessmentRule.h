#pragma once

#include <string>

/*!
 * Class for assessment rules.
 * 
 */
/// <summary>
/// Class for assessment rules.
/// </summary>
class AssessmentRule
{
public:
   AssessmentRule(std::string ruleId, std::string stringId, std::string condition, std::string expression) : _ruleId(ruleId), _stringId(stringId), _condition(condition), _expression(expression) {};
   std::string RuleId()
   {
      return _ruleId;
   }
   std::string StringId()
   {
      return _stringId;
   }
   std::string Condition() { return _condition; }
   std::string Expression() { return _expression; }
private:
   std::string _ruleId;
   std::string _stringId;
   std::string _condition;
   std::string _expression;
};

