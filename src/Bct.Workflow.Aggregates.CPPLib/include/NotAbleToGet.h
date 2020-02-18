#pragma once

#include <exception>
#include <string>

namespace Bct
{
   namespace Workflow
   {
      namespace Aggregates
      {
         class NotAbleToGet : public std::exception
         {
         public:
            /// <summary>
            /// Instantiate a NotAbleToGet exception which is thrown if the requested field value is trying to be obtained while the field state is Unavailable or NotSet
            /// </summary>
            /// <param name="aggregateName">Associated aggregate name for exception</param>
            /// <param name="fieldName">Name of the field trying to be obtained</param>
            /// <param name="fieldState">State of the field trying to be obtained</param>
            NotAbleToGet(const std::string& aggregateName, const std::string& fieldName, const std::string& fieldState);

            /// <summary>
            /// Destructor
            /// </summary>
            virtual ~NotAbleToGet();

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