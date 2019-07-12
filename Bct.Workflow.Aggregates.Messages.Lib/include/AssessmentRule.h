#pragma once

#include <string>

/// <summary>
/// Class for assessment rules.
/// </summary>
class AssessmentRule
{
public:
   /// <summary>
   /// Constructor for assessment rule.
   /// </summary>
   /// <param name="ruleId">Unique Identifier for rule</param>
   /// <param name="stringId">Id for localization</param>
   /// <param name="condition">RPN expression that evaluates to bool. true means this rule is evaluated.</param>
   /// <param name="expression">RPN expression that evaluates to bool. true means this rule passes.</param>
   AssessmentRule(std::string ruleId, std::string stringId, std::string condition, std::string expression);
   /// <summary>
   /// Gets rule id.
   /// </summary>
   /// <returns>Rule id.</returns>
   std::string RuleId() const;
   /// <summary>
   /// Gets string id for localization.
   /// </summary>
   /// <returns>Localization string id.</returns>
   std::string StringId() const;
   /// <summary>
   /// Gets condition.
   /// </summary>
   /// <returns>Condition.</returns>
   std::string Condition() const;
   /// <summary>
   /// Gets expression.
   /// </summary>
   /// <returns>Expression.</returns>
   std::string Expression() const;
private:
   std::string _ruleId;
   std::string _stringId;
   std::string _condition;
   std::string _expression;
};

