#include <sstream>
#include "Exceptions.h"

namespace Bct
{
   namespace Workflow
   {
      namespace Aggregates
      {
         NoSuchVersion::NoSuchVersion(const std::string& aggregateName, const std::string& requestedVersion)
            : std::exception()
            , _errorMessage()
            , _aggregateName(aggregateName)
            , _requestedVersion(requestedVersion)
         {
            try
            {
               std::ostringstream errorMessageBuilder(_errorMessage);
               errorMessageBuilder << "Bct::Workflow::Aggregates::NoSuchVersion: aggregate=" << _aggregateName << " requestedVersion=" << _requestedVersion;
            }
            catch (...)
            {
               _errorMessage = "Bct::Workflow::Aggregates::NoSuchVersion";
            }
         }

         NoSuchVersion::~NoSuchVersion()
         {
         }

         const char * NoSuchVersion::what() const
         {
            return _errorMessage.c_str();
         }

         const std::string& NoSuchVersion::aggregateName() const
         {
            return _aggregateName;
         }

         const std::string& NoSuchVersion::requestedVersion() const
         {
            return _requestedVersion;
         }
      }
   }
}