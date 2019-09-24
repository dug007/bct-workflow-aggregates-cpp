#pragma once

#include <string>

namespace Bct
{
   namespace Workflow
   {
      namespace Aggregates
      {
         /// <summary>
         /// Proveds conversion for a field from the current version to a specified version.
         /// </summary>
         class VersionChangeRule
         {
         public:
            /// <summary>
            /// Constructor
            /// </summary>
            /// <param name="fieldId">Field id of field to convert.</param>
            /// <param name="toVersion">Version id of target version.</param>
            /// <param name="condition">Expression to evaluate to determine if this rule should happen. Returns true if the rule applies.</param>
            /// <param name="expression">Expression to calculate the field for the specified target version.</param>
            VersionChangeRule(int32_t fieldId, int16_t toVersion, std::string condition, std::string expression);
            /// <summary>
            /// Getter to get fieldid of the rule.
            /// </summary>
            /// <returns>Field id.</returns>
            int32_t FieldId();
            /// <summary>
            /// Getter to return the target versionid of the rule.
            /// </summary>
            /// <returns>Target versionid.</returns>
            int16_t ToVersion();
            /// <summary>
            /// Getter to get the condition expression.
            /// </summary>
            /// <returns>Condition expression.</returns>
            std::string Condition();
            /// <summary>
            /// Getter to get the update expression of the rule.
            /// </summary>
            /// <returns>Update expression.</returns>
            std::string Expression();

         private:
            int32_t     _fieldId;
            int16_t     _toVersion;
            std::string _condition;
            std::string _expression;
         };
      }
   }
}
