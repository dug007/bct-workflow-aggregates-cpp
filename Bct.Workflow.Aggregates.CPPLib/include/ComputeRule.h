#pragma once

#include <string>

namespace Bct
{
   namespace Workflow
   {
      namespace Aggregates
      {
         /// <summary>
         /// Provide computation rules across versions.
         /// </summary>
         class ComputeRule
         {
         public:
            /// <summary>
            /// Constructor.
            /// </summary>
            /// <param name="id">Id of rule.</param>
            /// <param name="field">Name of field this rule applies to.</param>
            /// <param name="condition">RPN boolean condition. This rule does not fire if this returns false.</param>
            /// <param name="expression">RPN expression to calculate the value associated with this field.</param>
            /// <param name="versions">Version mask. This is a string beginning and ending with a period. This is a period delimited set of versions that this rule applies to. For example, ".3.4." means this rule applies to versions 3 and 4 only.</param>
            ComputeRule(std::string const &id, std::string const &field, std::string const &condition, std::string const &expression, std::string const &versions);

            /// <summary>
            /// Field name associated with this rule.
            /// </summary>
            /// <returns>Field name for rule.</returns>
            std::string FieldName();

            /// <summary>
            /// Id associated with this rule.
            /// </summary>
            /// <returns>Id of this rule.</returns>
            std::string Id();

            /// <summary>
            /// RPN boolean expression. This rule does not fire if this returns false.
            /// </summary>
            /// <returns>RPN expression.</returns>
            std::string Condition();

            /// <summary>
            /// RPN expression to calculate the value associated with this field.
            /// </summary>
            /// <returns>RPN expression.</returns>
            std::string Expression();

            /// <summary>
            /// Determines if this rule applies to the given version.
            /// </summary>
            /// <param name="ver">Version to check.</param>
            /// <returns>True if the rule applies, false if it does not apply.</returns>
            bool InVersion(int16_t ver);
         private:
            std::string _field;
            std::string _id;
            std::string _condition;
            std::string _expression;
            std::string _versions;
         };
      }
   }
}

