#ifndef RPNResult_H
#define RPNResult_H
#include "TypeEnum.h"
#include <string>

namespace Bct
{
   namespace RPNEvaluator
   {
      struct RPNResult
      {
         /// <summary>
         /// The resulting data value from the function
         /// </summary>
         std::string answerValue;
         /// <summary>
         /// The value type as an enum
         /// </summary>
         Workflow::TypeEnum::Type answerType;
         /// <summary>
         /// The error message for the result, if the evaluation fails
         /// </summary>
         std::string errorMsg;
      };
   }
}
#endif
