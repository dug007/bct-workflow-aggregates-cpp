#pragma once

#include <exception>
#include <string>

namespace Bct
{
   namespace Workflow
   {
      namespace Aggregates
      {
         class NoSuchVersion : public std::exception
         {
         public:
            /// <summary>
            /// Instantiate a NoSuchVersion exception which is thrown if the requested version for an aggregate is not defined.
            /// </summary>
            /// <param name="aggregateName">Associated aggregate name for exception</param>
            /// <param name="requestedVersion">Version requested that caused the exception</param>
            NoSuchVersion(const std::string& aggregateName, const std::string& requestedVersion);

            NoSuchVersion(const std::string& aggregateName, const std::string& fieldName, std::string& requestedVersion);

            /// <summary>
            /// Destructor
            /// </summary>
            virtual ~NoSuchVersion() throw();

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
            /// Requested version for exception
            /// </summary>
            /// <returns>The requested version associated with this exception</returns>
            const std::string& requestedVersion() const;

         private:
            std::string _errorMessage;
            std::string _aggregateName;
            std::string _requestedVersion;
            std::string _fieldName;

         };

      }
   }
}
