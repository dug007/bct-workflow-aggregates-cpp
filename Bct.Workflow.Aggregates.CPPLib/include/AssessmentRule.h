#pragma once

#include <string>

namespace Bct
{
   namespace Workflow
   {
      namespace Aggregates
      {
         /// <summary>
         /// Assessment rule. An assessment rule is used by a user interface to assess if the values for fields are valid.
         /// </summary>
         class AssessmentRule
         {
         public:
            /// <summary>
            /// Constructor for assessment rule.
            /// </summary>
            /// <param name="ruleId">Unique Identifier for rule</param>
            /// <param name="stringId">Id for localization</param>
            /// <param name="condition">RPN condition that evaluates to bool. true means this rule is evaluated.</param>
            /// <param name="expression">RPN expression that evaluates to bool. true means this rule passes.</param>
            AssessmentRule(std::string const &ruleId, std::string const &stringId, std::string const &condition, std::string const &expression);

            /// <summary>
            /// Gets rule id.
            /// </summary>
            /// <returns>Rule id.</returns>
            std::string RuleId() const;

            /// <summary>
            /// Gets string id for localization.
            /// </summary>
            /// <returns>Localization string id.</returns>
            const std::string &StringId() const;

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
      }
   }
}

