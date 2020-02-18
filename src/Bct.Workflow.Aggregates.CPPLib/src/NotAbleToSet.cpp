#include <sstream>
#include "NotAbleToSet.h"

namespace Bct
{
   namespace Workflow
   {
      namespace Aggregates
      {
         NotAbleToSet::NotAbleToSet(const std::string& aggregateName, const std::string& fieldName, const std::string& fieldState) :
            std::exception(),
            _errorMessage(),
            _aggregateName(aggregateName),
            _fieldName(fieldName),
            _fieldState(fieldState)
         {
            try
            {
               //std::ostringstream errorMessageBuilder(_errorMessage);
               //errorMessageBuilder << "Bct::Workflow::Aggregates::NotAbleToSet: aggregate=" << _aggregateName << " fieldName=" << _fieldName << " fieldState=" << _fieldState;
               _errorMessage = "Bct::Workflow::Aggregates::NotAbleToSet: aggregate=" + _aggregateName + " fieldName=" + _fieldName + " fieldState=" + _fieldState;
            }
            catch (...)
            {
               _errorMessage = "Bct::Workflow::Aggregates::NotAbleToSet";
            }
         }

         NotAbleToSet::~NotAbleToSet()
         {
         }

         const char * NotAbleToSet::what() const
         {
            return _errorMessage.c_str();
         }

         const std::string& NotAbleToSet::aggregateName() const
         {
            return _aggregateName;
         }

         const std::string& NotAbleToSet::fieldName() const
         {
            return _fieldName;
         }
         const std::string& NotAbleToSet::fieldState() const
         {
            return _fieldState;
         }

      }
   }
}