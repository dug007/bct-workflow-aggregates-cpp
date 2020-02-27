#include <sstream>
#include "AggregateNotFound.h"
#include "demangle.h"

namespace Bct
{
   namespace Workflow
   {
      namespace Aggregates
      {
         AggregateNotFound::AggregateNotFound(const std::string & aggregateName)
            : std::exception()
            , _errorMessage()
            , _aggregateName(demangle(aggregateName.c_str()))
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

         AggregateNotFound::~AggregateNotFound()
         {
         }

         const char * AggregateNotFound::what() const
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
