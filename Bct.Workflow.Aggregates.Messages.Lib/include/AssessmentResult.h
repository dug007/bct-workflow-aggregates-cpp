#pragma once

#include <string>
#include <vector>

namespace Bct
{
   namespace Workflow
   {
      namespace Aggregates
      {
         /// <summary>
         /// Result of assessment
         /// </summary>
         class AssessmentResult
         {
         public:
            /// <summary>
            /// Constructor.
            /// </summary>
            AssessmentResult();

            /// <summary>
            /// Add error result to list of errors.
            /// </summary>
            /// <param name="id">Assessment rule id with error.</param>
            /// <param name="context">Context of error.</param>
            void addError(std::string id, std::string context);

            /// <summary>
            /// Gets list of error ids.
            /// </summary>
            /// <returns></returns>
            std::vector<std::string> getErrorIds();

            /// <summary>
            /// Gets list of error contexts.
            /// </summary>
            /// <returns></returns>
            std::vector<std::string> getContexts();

            /// <summary>
            /// Returns true if assessment is successful, false otherwise.
            /// </summary>
            /// <returns>True if success.</returns>
            bool isSuccess();

            /// <summary>
            /// Returns true if assessment is a failure, false otherwise.
            /// </summary>
            /// <returns>True if not successful.</returns>
            bool isFailure();
         private:
            std::vector<std::string> _ids;
            std::vector<std::string> _contexts;
         };
      }
   }
}
