#include <sstream>
#include "AggregateNotFound.h"

namespace Bct
{
   namespace Workflow
   {
      namespace Aggregates
      {
         AggregateNotFound::AggregateNotFound(const std::string & aggregateName)
            : std::exception()
            , _errorMessage()
            , _aggregateName(aggregateName)
         {
            try
            {
                _errorMessage = "Bct::Workflow::Aggregates::AggregateNotFound: aggregate=" + _aggregateName;
            }
            catch (...)
            {
               _errorMessage = "Bct::Workflow::Aggregates::AggregateNotFound";
            }
         }

         AggregateNotFound::~AggregateNotFound() throw()
         {
         }

         const char * AggregateNotFound::what() const throw()
         {
            return _errorMessage.c_str();
         }

         const std::string & AggregateNotFound::aggregateName() const
         {
            return _aggregateName;
         }
      }
   }
}