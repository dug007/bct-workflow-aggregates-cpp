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
            /// <param name="condition">RPN expression that evaluates to bool. true means this rule is evaluated.</param>
            /// <param name="expression">RPN expression that evaluates to bool. true means this rule passes.</param>
            /// <param name="versions">Version mask. This is a string beginning and ending with a period. This is a period delimited set of versions that this rule applies to. For example, ".3.4." means this rule applies to versions 3 and 4 only.</param>
            AssessmentRule(std::string ruleId, std::string stringId, std::string condition, std::string expression, std::string versions);

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

            /// <summary>
            /// Determines if this rule applies to the given version.
            /// </summary>
            /// <param name="ver">Version to check.</param>
            /// <returns>True if the rule applies, falso if it does not apply.</returns>
            bool InVersion(int16_t ver);

         private:
            std::string _ruleId;
            std::string _stringId;
            std::string _condition;
            std::string _expression;
            std::string _versions;
         };
      }
   }
}

