#ifndef FunctionMap_H
#define FunctionMap_H
#include "TypeEnum.h"
#include "FuncOper.h"
#include <map>

namespace Bct
{
   namespace RPNEvaluator
   {
      /// <summary>
      /// A class containing the list of functions in a map
      /// </summary>
      class FunctionMap
      {
      public:
         /// <summary>
         /// The type definition for the function map with the string name and the FuncOper definition for functions and operators.
         /// </summary>
         typedef std::map<std::string, FuncOper> FuncOpersMap;
         /// <summary>
         /// The map containing the functions/operators and units
         /// </summary>
         static FuncOpersMap FuncOpers;

         /// <summary>
         /// Creates the initial map with the name, number of arguments, the required input type of the function, and the return type
         /// </summary>
         /// <returns>The function map as a FuncOpersMap variable containing the string name and the FuncOper definition</returns>
         static FuncOpersMap initFuncOpersMap()
         {
            FuncOpersMap tmpMap;
            tmpMap["$Negate"] = FuncOper("$Negate", 1, Workflow::TypeEnum::EmptyType, Workflow::TypeEnum::EmptyType);
            tmpMap["$Sqrt"] = FuncOper("$Sqrt", 1, Workflow::TypeEnum::DoubleType, Workflow::TypeEnum::EmptyType);
            tmpMap["$Pow"] = FuncOper("$Pow", 2, Workflow::TypeEnum::DoubleType, Workflow::TypeEnum::EmptyType);
            tmpMap["$Min"] = FuncOper("$Min", 99, Workflow::TypeEnum::EmptyType, Workflow::TypeEnum::EmptyType);
            tmpMap["$Max"] = FuncOper("$Max", 99, Workflow::TypeEnum::EmptyType, Workflow::TypeEnum::EmptyType);
            tmpMap["$Mean"] = FuncOper("$Mean", 99, Workflow::TypeEnum::EmptyType, Workflow::TypeEnum::EmptyType);
            tmpMap["!"] = FuncOper("!", 1, Workflow::TypeEnum::BoolType, Workflow::TypeEnum::BoolType);
            tmpMap["*"] = FuncOper("*", 2, Workflow::TypeEnum::EmptyType, Workflow::TypeEnum::EmptyType);
            tmpMap["/"] = FuncOper("/", 2, Workflow::TypeEnum::EmptyType, Workflow::TypeEnum::EmptyType);
            tmpMap["+"] = FuncOper("+", 2, Workflow::TypeEnum::EmptyType, Workflow::TypeEnum::EmptyType);
            tmpMap["-"] = FuncOper("-", 2, Workflow::TypeEnum::EmptyType, Workflow::TypeEnum::EmptyType);
            tmpMap["<"] = FuncOper("<", 2, Workflow::TypeEnum::EmptyType, Workflow::TypeEnum::BoolType);
            tmpMap["<="] = FuncOper("<=", 2, Workflow::TypeEnum::EmptyType, Workflow::TypeEnum::BoolType);
            tmpMap[">"] = FuncOper(">", 2, Workflow::TypeEnum::EmptyType, Workflow::TypeEnum::BoolType);
            tmpMap[">="] = FuncOper(">=", 2, Workflow::TypeEnum::EmptyType, Workflow::TypeEnum::BoolType);
            tmpMap["=="] = FuncOper("==", 2, Workflow::TypeEnum::EmptyType, Workflow::TypeEnum::BoolType);
            tmpMap["!="] = FuncOper("!=", 2, Workflow::TypeEnum::EmptyType, Workflow::TypeEnum::BoolType);
            tmpMap["&"] = FuncOper("&", 2, Workflow::TypeEnum::EmptyType, Workflow::TypeEnum::EmptyType);
            tmpMap["^"] = FuncOper("^", 2, Workflow::TypeEnum::EmptyType, Workflow::TypeEnum::EmptyType);
            tmpMap["|"] = FuncOper("|", 2, Workflow::TypeEnum::EmptyType, Workflow::TypeEnum::EmptyType);
            tmpMap["&&"] = FuncOper("&&", 2, Workflow::TypeEnum::BoolType, Workflow::TypeEnum::BoolType);
            tmpMap["||"] = FuncOper("||", 2, Workflow::TypeEnum::BoolType, Workflow::TypeEnum::BoolType);
            tmpMap["$IsSet"] = FuncOper("$IsSet", 1, Workflow::TypeEnum::VariableType, Workflow::TypeEnum::BoolType);
            tmpMap["$SetState"] = FuncOper("$SetState", 2, Workflow::TypeEnum::VariableType, Workflow::TypeEnum::BoolType);
            tmpMap["$EnteredLater"] = FuncOper("$EnteredLater", 2, Workflow::TypeEnum::VariableType, Workflow::TypeEnum::BoolType);
            tmpMap["$GetState"] = FuncOper("$GetState", 1, Workflow::TypeEnum::VariableType, Workflow::TypeEnum::VariableType);
            tmpMap["$IsComputed"] = FuncOper("$IsComputed", 1, Workflow::TypeEnum::VariableType, Workflow::TypeEnum::BoolType);
            tmpMap["$IsDefault"] = FuncOper("$IsDefault", 1, Workflow::TypeEnum::VariableType, Workflow::TypeEnum::BoolType);
            tmpMap["$IsConstant"] = FuncOper("$IsConstant", 1, Workflow::TypeEnum::VariableType, Workflow::TypeEnum::BoolType);
            tmpMap["$IsNull"] = FuncOper("$IsNull", 1, Workflow::TypeEnum::VariableType, Workflow::TypeEnum::BoolType);
            tmpMap["$HasValue"] = FuncOper("$HasValue", 1, Workflow::TypeEnum::VariableType, Workflow::TypeEnum::BoolType);
            tmpMap["$If"] = FuncOper("$If", 3, Workflow::TypeEnum::EmptyType, Workflow::TypeEnum::EmptyType);
            tmpMap["$RangeCheck"] = FuncOper("$RangeCheck", 3, Workflow::TypeEnum::EmptyType, Workflow::TypeEnum::BoolType);
            tmpMap["$Size"] = FuncOper("$Size", 1, Workflow::TypeEnum::ArrayType, Workflow::TypeEnum::Int32Type);
            tmpMap["true"] = FuncOper("true", 0, Workflow::TypeEnum::BoolType, Workflow::TypeEnum::BoolType);
            tmpMap["false"] = FuncOper("false", 0, Workflow::TypeEnum::BoolType, Workflow::TypeEnum::BoolType);
            return tmpMap;
         }
      };
   }
}
#endif