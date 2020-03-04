#include <sstream>
#include "CannotConvertScalar.h"

namespace Bct
{
   namespace Workflow
   {
      namespace Aggregates
      {
         CannotConvertScalar::CannotConvertScalar(const std::string& aggregateName, const std::string& fieldName) :
            std::exception(),
            _errorMessage(),
            _aggregateName(aggregateName),
            _fieldName(fieldName)
         {
            try
            {
               _errorMessage = "Bct::Workflow::Aggregates::CannotConvertScalar: aggregate=" + _aggregateName + " fieldName=" + _fieldName;
            }
            catch (...)
            {
               _errorMessage = "Bct::Workflow::Aggregates::CannotConvertScalar";
            }
         }


         CannotConvertScalar::~CannotConvertScalar() throw()
         {
         }

         const char * CannotConvertScalar::what() const throw()
         {
            return _errorMessage.c_str();
         }

         const std::string& CannotConvertScalar::aggregateName() const
         {
            return _aggregateName;
         }

         const std::string& CannotConvertScalar::fieldName() const
         {
            return _fieldName;
         }
      }
   }
}