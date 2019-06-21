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
            /**
             * Instantiate a NoSuchVersion exception
             * @param aggregateName: associated aggregate name for the exception
             * @param requestedVersion: the version requested that caused the exception
             *
             * This exception is thrown if the requested version for an aggregate is not defined
             */
            NoSuchVersion(const std::string& aggregateName, const std::string& requestedVersion);

            /**
             * Destructor 
             */
            virtual ~NoSuchVersion();

            /**
             * Return the error message for this exception
             */
            virtual const char * what() const;

            /**
             * Return the aggregate name associated with this exception
             */
            const std::string& aggregateName() const;

            /**
             * Return the requested version associated with this exception
             */
            const std::string& requestedVersion() const;

         private:
            std::string _errorMessage;
            std::string _aggregateName;
            std::string _requestedVersion;
         };
      }
   }
}