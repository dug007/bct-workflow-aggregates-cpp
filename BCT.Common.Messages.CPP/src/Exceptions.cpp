#include <sstream>
#include "Exceptions.h"

Bct::Workflow::Aggregates::NoSuchVersion::NoSuchVersion(const std::string& aggregateName, const std::string& requestedVersion)
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

Bct::Workflow::Aggregates::NoSuchVersion::~NoSuchVersion()
{
}

const char * Bct::Workflow::Aggregates::NoSuchVersion::what() const
{
   return _errorMessage.c_str();
}

const std::string& Bct::Workflow::Aggregates::NoSuchVersion::aggregateName() const
{
   return _aggregateName; 
}

const std::string& Bct::Workflow::Aggregates::NoSuchVersion::requestedVersion() const
{
   return _requestedVersion;
}