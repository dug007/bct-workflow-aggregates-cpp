#pragma once

#include <exception>
#include <string>

namespace Bct
{
   namespace Workflow
   {
      namespace Aggregates
      {
         class NotAbleToSet : public std::exception
         {
         public:
            /// <summary>
            /// Instantiate a NotAbleToSet exception which is thrown if the requested field is trying to set its value while the state is Constant or Unavailable or ComputeOnly
            /// </summary>
            /// <param name="aggregateName">Associated aggregate name for exception</param>
            /// <param name="fieldName">Name of the field trying to be set</param>
            /// <param name="fieldState">State of the field trying to be set</param>
            NotAbleToSet(const std::string& aggregateName, const std::string& fieldName, const std::string& fieldState);

            /// <summary>
            /// Destructor
            /// </summary>
            virtual ~NotAbleToSet();

            /// <summary>
            /// Error message for the exception
            /// </summary>
            /// <returns>The error message for this exception</returns>
            virtual const char * what() const;

            /// <summary>
            /// Aggregate name for exception
            /// </summary>
            /// <returns>Aggregate name associated with this exception</returns>
            const std::string& aggregateName() const;

            /// <summary>
            /// Field name for exception
            /// </summary>
            /// <returns>The field name associated with this exception</returns>
            const std::string& fieldName() const;

            /// <summary>
            /// Field state for exception
            /// </summary>
            /// <returns>The state of the field associated with this exception</returns>
            const std::string& fieldState() const;

         private:
            std::string _errorMessage;
            std::string _aggregateName;
            std::string _fieldName;
            std::string _fieldState;
         };
      }

   }
}
