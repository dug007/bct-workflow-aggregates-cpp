#ifndef FuncOper_h 
#define FuncOper_h 
#include <string>
#include "TypeEnum.h"

namespace Bct
{
   namespace RPNEvaluator
   {
      /// <summary>
      /// This class holds a map of the different function operations that can be performed.
      /// </summary>
      class FuncOper
      {
      public:
         /// <summary>
         /// Constructor
         /// </summary>
         FuncOper();

         /// <summary>
         /// The instance of a single function operation that can be performed.
         /// </summary>
         /// <param name="name">The string name used to identify the rpn function that begins with "$"</param>
         /// <param name="argNum">The number of arguments used in the rpn function</param>
         /// <param name="requiredType">The required input type of the rpn function</param>
         /// <param name="returnType">The return type of the rpn function if it can be different from the inputs. For example, a boolean compare of integers.</param>
         FuncOper(std::string name, int argNum, Workflow::TypeEnum::Type requiredType, Workflow::TypeEnum::Type returnType);

         /// <summary>
         /// Destructor
         /// </summary>
         virtual ~FuncOper();

         /// <summary>
         /// The string name used to identify the rpn function that begins with "$"
         /// </summary>
         std::string Name;

         /// <summary>
         /// The number of arguments used in the rpn function
         /// </summary>
         int ArgNum;  // 99 == variable number

            /// <summary>
            /// The required input type of the rpn function
            /// </summary>
         Workflow::TypeEnum::Type RequiredType; // = Workflow::TypeEnum::EmptyType;  // the required input type of the function

            /// <summary>
            /// The return type of the rpn function if it can be different from the inputs. For example, a boolean compare of integers.
            /// </summary>
         Workflow::TypeEnum::Type ReturnType; // = Workflow::TypeEnum::EmptyType;  // the return type if it can be different from the inputs - e.g. boolean compares of ints

      };
   }
}
#endif