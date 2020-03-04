#pragma once

#include <string>
#include <stdint.h>

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
            /// <param name="fieldId">Field id of field this rule applies to.</param>
            /// <param name="condition">RPN boolean condition. This rule does not fire if this returns false.</param>
            /// <param name="expression">RPN expression to calculate the value associated with this field.</param>
            ComputeRule(std::string const &id, int16_t fieldId, std::string const &condition, std::string const &expression);

            /// <summary>
            /// Field id associated with this rule.
            /// </summary>
            /// <returns>Field name for rule.</returns>
            int16_t fieldId();

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

         private:
            int16_t     _fieldId;
            std::string _id;
            std::string _condition;
            std::string _expression;
         };
      }
   }
}

