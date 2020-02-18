#ifndef RPNVariable_H
#define RPNVariable_H
#include <string>
#include "TypeEnum.h"
#include "FieldStateEnum.h"
#include <map>

namespace Bct
{
   namespace RPNEvaluator
   {
      /// <summary>
      /// This class holds a map of the different variables to be used in the RPN evaluator.
      /// </summary>
      class RPNVariable
      {
      public:
         /// <summary>
         /// Constructor
         /// </summary>
         RPNVariable()
         {};

         /// <summary>
         /// A single instance of a variable that can be used in the RPN evaluator
         /// </summary>
         /// <param name="varName">The variable name</param>
         /// <param name="varType">The data type of the variable</param>
         /// <param name="varValue">The data value of the variable</param>
         /// <param name="varState">The state enum for the variable. For example: Not Set</param>
         /// <param name="varCount">The count associated with the order in which variables were set or entered by a user.</param>
         RPNVariable(std::string varName, Workflow::TypeEnum::Type varType, std::string varValue, Bct::Workflow::Aggregates::FieldStateEnum::FieldState& varState, uint32_t varCount) :
            VarName(varName),
            VarType(varType),
            VarValue(varValue),
            VarState(varState),
            VarCount(varCount)
         {};

         /// <summary>
         /// The name of this variable
         /// </summary>
         std::string VarName;

         /// <summary>
         /// The data type of this variable
         /// </summary>
         Workflow::TypeEnum::Type VarType;

         /// <summary>
         /// The data value of this variable
         /// </summary>
         std::string VarValue;

         /// <summary>
         /// The state enum for this variable. For example: Set, Not Set, Computed, etc.
         /// </summary>
         Bct::Workflow::Aggregates::FieldStateEnum::FieldState VarState;

         /// <summary>
         /// The count of this variable. This signifies the order in which this variable was set or entered by a user compared to other variables that were set by a user.
         /// </summary>
         uint32_t VarCount;
      };
   }
}
#endif