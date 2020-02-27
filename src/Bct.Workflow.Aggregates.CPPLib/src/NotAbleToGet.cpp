#include <sstream>
#include "NotAbleToGet.h"
#include "demangle.h"

namespace Bct
{
   namespace Workflow
   {
      namespace Aggregates
      {
         NotAbleToGet::NotAbleToGet(const std::string& aggregateName, const std::string& fieldName, const std::string& fieldState) :
            std::exception(),
            _errorMessage(),
            _aggregateName(demangle(aggregateName.c_str())),
            _fieldName(fieldName),
            _fieldState(fieldState)
         {
            try
            {
               //std::ostringstream errorMessageBuilder(_errorMessage);
               //errorMessageBuilder << "Bct::Workflow::Aggregates::NotAbleToSet: aggregate=" << _aggregateName << " fieldName=" << _fieldName << " fieldState=" << _fieldState;
               _errorMessage = "Bct::Workflow::Aggregates::NotAbleToGet: aggregate=" + _aggregateName + " fieldName=" + _fieldName + " fieldState=" + _fieldState;
            }
            catch (...)
            {
               _errorMessage = "Bct::Workflow::Aggregates::NotAbleToGet";
            }
         }

         NotAbleToGet::~NotAbleToGet()
         {
         }

         const char * NotAbleToGet::what() const
         {
            return _errorMessage.c_str();
         }

         const std::string& NotAbleToGet::aggregateName() const
         {
            return _aggregateName;
         }

         const std::string& NotAbleToGet::fieldName() const
         {
            return _fieldName;
         }
         const std::string& NotAbleToGet::fieldState() const
         {
            return _fieldState;
         }
      }
   }
}
