#include <sstream>
#include "RPNEvalException.h"

namespace Bct
{
   namespace Workflow
   {
      namespace Aggregates
      {
         RPNEvalException::RPNEvalException(const std::string& aggregateName, const std::string& rpnExpression, const std::string& rpnErrorMsg) :
            std::exception(),
            _errorMessage(),
            _aggregateName(aggregateName),
            _rpnExpression(rpnExpression),
            _rpnErrorMsg(rpnErrorMsg)
         {
            _errorMessage = "Aggregate: " + _aggregateName + ", Expression: " + _rpnExpression + ", Error Message: " + _rpnErrorMsg;
         }

         RPNEvalException::~RPNEvalException() throw()
         {
         }

         const char* RPNEvalException::what() const throw()
         {
            return _errorMessage.c_str();
         }

         const std::string& RPNEvalException::aggregateName() const
         {
            return _aggregateName;
         }

         const std::string& RPNEvalException::rpnExpression() const
         {
            return _rpnExpression;
         }

         const std::string& RPNEvalException::rpnErrorMsg() const
         {
            return _rpnErrorMsg;
         }
      }
   }
}