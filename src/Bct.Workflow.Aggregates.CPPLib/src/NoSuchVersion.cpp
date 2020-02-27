#include <sstream>
#include "NoSuchVersion.h"
#include "demangle.h"

namespace Bct
{
   namespace Workflow
   {
      namespace Aggregates
      {
         NoSuchVersion::NoSuchVersion(const std::string& aggregateName, const std::string& requestedVersion)
            : std::exception()
            , _errorMessage()
            , _aggregateName(demangle(aggregateName.c_str()))
            , _requestedVersion(requestedVersion)
         {
            try
            {
               //std::ostringstream errorMessageBuilder(_errorMessage);
               //errorMessageBuilder << "Bct::Workflow::Aggregates::NoSuchVersion: aggregate=" << _aggregateName << " requestedVersion=" << _requestedVersion;
               _errorMessage = "Bct::Workflow::Aggregates::NoSuchVersion: aggregate=" + _aggregateName + " requestedVersion=" + _requestedVersion;
            }
            catch (...)
            {
               _errorMessage = "Bct::Workflow::Aggregates::NoSuchVersion";
            }
         }

         NoSuchVersion::NoSuchVersion(const std::string& aggregateName, const std::string &fieldName, std::string& requestedVersion)
            : std::exception()
            , _errorMessage()
            , _aggregateName(demangle(aggregateName.c_str()))
            , _fieldName(fieldName)
            , _requestedVersion(requestedVersion)
         {
            try
            {
               //std::ostringstream errorMessageBuilder(_errorMessage);
               //errorMessageBuilder << "Bct::Workflow::Aggregates::NoSuchVersion: aggregate=" << _aggregateName << " requestedVersion=" << _requestedVersion;
               _errorMessage = "Bct::Workflow::Aggregates::NoSuchVersion: aggregate=" + _aggregateName + " field=" + _fieldName + " requestedVersion=" + _requestedVersion;
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
