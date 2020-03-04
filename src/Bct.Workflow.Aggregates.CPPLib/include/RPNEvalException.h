#pragma once

#include <exception>
#include <string>

namespace Bct
{
   namespace Workflow
   {
      namespace Aggregates
      {
         class RPNEvalException : public std::exception
         {
         public:
            /// <summary>
            /// Instantiate an RPNEvalException exception which is thrown if there is an issue with the rpn evaluator evaluation
            /// </summary>
            /// <param name="aggregateName">Associated aggregate name for exception</param>
            /// <param name="rpnExpression">Associated rpnExpression for exception</param>
            /// <param name="rpnErrorMsg">Associated error message created by evaluateRPNExpression</param>
            RPNEvalException(const std::string& aggregateName, const std::string& rpnExpression, const std::string& rpnErrorMsg);

            /// <summary>
            /// Destructor
            /// </summary>
            virtual ~RPNEvalException() throw();

            /// <summary>
            /// Error message for the exception
            /// </summary>
            /// <returns>The error message for this exception</returns>
            virtual const char* what() const throw();

            /// <summary>
            /// Aggregate name for exception
            /// </summary>
            /// <returns>Aggregate name associated with this exception</returns>
            const std::string& aggregateName() const;

            /// <summary>
            /// RPN Expression for exception
            /// </summary>
            /// <returns>RPN expression associated with this exception</returns>
            const std::string& rpnExpression() const;

            /// <summary>
            /// RPN error message for exception
            /// </summary>
            /// <returns>RPN error message associated with this exception</returns>
            const std::string& rpnErrorMsg() const;

         private:
            std::string _errorMessage;
            std::string _aggregateName;
            std::string _rpnExpression;
            std::string _rpnErrorMsg;
         };
      }
   }

}
