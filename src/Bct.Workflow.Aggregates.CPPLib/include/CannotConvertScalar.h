#pragma once

#include <exception>
#include <string>

namespace Bct
{
   namespace Workflow
   {
      namespace Aggregates
      {
         class CannotConvertScalar : public std::exception
         {
         public:
            /// <summary>
            /// Instantiate a CannotConvertScalar exception which is thrown if scalar cannot be converted into an acceptible type
            /// </summary>
            /// <param name="aggregateName">Associated aggregate name for exception</param>
            /// <param name="fieldName">Name of the field trying to be obtained</param>
            CannotConvertScalar(const std::string& aggregateName, const std::string& fieldName);

            /// <summary>
            /// Destructor
            /// </summary>
            virtual ~CannotConvertScalar() throw();

            /// <summary>
            /// Error message for the exception
            /// </summary>
            /// <returns>The error message for this exception</returns>
            virtual const char * what() const throw();

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

         private:
            std::string _errorMessage;
            std::string _aggregateName;
            std::string _fieldName;
         };
      }
   }
}

