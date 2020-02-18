#ifndef RPNEvaluator_H
#define RPNEvaluator_H
#include "RPNVariable.h"
#include "Token.h"
#include "TypeEnum.h"
#include <list>
#include <map>
#include <stack>
#include <string>
#include <vector>
#include "RPNResult.h"

namespace Bct
{
   namespace RPNEvaluator
   {
      /// <summary>
      /// This class evaluates a reverse polish notation (RPN) expression.
      /// </summary>
      class RPNEvaluator
      {
      public:
         /// <summary>
         /// Constructor
         /// </summary>
         RPNEvaluator();

         /// <summary>
         /// Destructor
         /// </summary>
         virtual ~RPNEvaluator();

         /// <summary>
         /// Parse the RPN expression and return the list of variables
         /// </summary>
         /// <param name="rpn">The Reverse Polish Notation expression as a string</param>
         /// <param name="variables">The list of variables taken from the rpn string</param>
         void GetVariables(const std::string& rpn, std::list<std::string>& variables, RPNResult & answerResult);

         /// <summary>
         /// Evaluates the RPN expression
         /// </summary>
         /// <param name="rpn">The RPN expression as a string</param>
         /// <param name="variableMap">A map containing the variables used for this expression</param>
         /// /// <param name="answerResult">The result struct for the answer which contains answerType, answerValue, and errorMsg</param>
         bool EvaluateRPNExpression(const std::string& rpn, std::map<std::string, RPNVariable>& variableMap, RPNResult& answerResult);

      private:
         /// 
         /// Takes a token that just has the name and fills-out the rest of the token information.
         /// It looks up variables and replaces them with values.
         /// 
         bool ClassifyToken(Token& token, std::map<std::string, RPNVariable>& variableMap, std::list<std::string>& variables) const;

         /// 
         /// Wrapped the pop from the stack so not to duplicate the check every time
         ///
         static Token PopFromStack(std::stack<Token>& stack);

         ///
         /// Takes a list of tokens and upconverts them to the widest type in the group.
         /// Optionally takes a type for the function/operator return to force the input arguments to match.
         /// Can't convert strings to anything.
         ///
         bool NormalizeTypes(std::vector<Token>& argList, Workflow::TypeEnum::Type opReturnType = Workflow::TypeEnum::EmptyType);

         ///
         /// Execute the function/operator
         ///
         bool DoOp(const std::string& op, const std::vector<Token>& argList, std::map<std::string, RPNVariable>& variableMap, Token& rtnTok);

         ///
         /// Template for operations that return a bool but take a numeric type
         ///
         template <typename T>
         bool DoOpBoolNum(const std::string& op, const std::vector<T>& args, bool& rtn)
         {
            T rhs = args[0];
            T lhs = args[1];
            if (op == "<")
            {
               rtn = lhs < rhs;
            }
            else if (op == "<=")
            {
               rtn = lhs <= rhs;
            }
            else if (op == ">")
            {
               rtn = lhs > rhs;
            }
            else if (op == ">=")
            {
               rtn = lhs >= rhs;
            }
            else if (op == "==")
            {
               rtn = lhs == rhs;
            }
            else if (op == "!=")
            {
               rtn = lhs != rhs;
            }
            else if (op == "$RangeCheck")
            {
               rtn = (args[2] <= args[0] && args[2] >= args[1]); //args[0] = max, args[1] = min
            }
            else
            {
               _rpnResult->errorMsg = op + " is not a valid operator";
               return false;
            }

            return true;
         }

         ///
         /// Template for operations that take and return a type of int
         ///
         template <typename T>
         T DoOpInt(const std::string& op, const std::vector<T>& args, T& rtn)
         {
            T result;
            if (op == "$Negate")
            {
               rtn = args[0] * -1;
            }
            else if (op == "$Min")
            {
               if (args.empty())
               {
                  rtn = 0;
               }
               else
               {
                  result = args[0];
                  for (unsigned int i = 0; i < args.size(); ++i)
                  {
                     result = result < args[i] ? result : args[i];
                  }
                  rtn = result;
               }
            }
            else if (op == "$Max")
            {
               if (args.empty())
               {
                  rtn = 0;
               }
               else
               {
                  result = args[0];
                  for (unsigned int i = 0; i < args.size(); ++i)
                  {
                     result = result > args[i] ? result : args[i];
                  }
                  rtn = result;
               }
            }
            else if (op == "$Mean")
            {
               result = 0;
               for (unsigned int i = 0; i < args.size(); ++i)
               {
                  result += args[i];
               }
               result = result / static_cast<T>(args.size());
               rtn = result;
            }
            else if (op == "*")
            {
               rtn = args[0] * args[1];
            }
            else if (op == "/")
            {
               if (args[0] > 0)
               {
                  rtn = args[1] / args[0];
               }
               else
               {
                  _rpnResult->errorMsg = "Divide by zero error";
                  return false;
               }
            }
            else if (op == "+")
            {
               rtn = args[0] + args[1];
            }
            else if (op == "-")
            {
               rtn = args[1] - args[0];
            }
            else if (op == "&")
            {
               rtn = args[0] & args[1];
            }
            else if (op == "|")
            {
               rtn = args[0] | args[1];
            }
            else if (op == "^")
            {
               rtn = args[0] ^ args[1];
            }
            else
            {
               _rpnResult->errorMsg = op + " is not a valid operator";
               return false;
            }
            return true;
         }

         // functions for the other cases
         bool DoOpBoolVar(const std::string& op, const std::vector<Token>& argList, std::map<std::string, RPNVariable>& variableMap, bool& rtn) const;
         bool DoOpVar(const std::string& op, const std::vector<Token>& argList, std::map<std::string, RPNVariable>& variableMap, std::string& rtn) const;
         bool DoOpBool(const std::string& op, const std::vector<bool>& args, bool& rtn) const;
         bool DoOpDbl(const std::string& op, const std::vector<double>& args, double& rtn) const;
         bool DoOpStr(const std::string& op, const std::vector<std::string>& args, std::string& rtnStr) const;

         // conversion functions from strings to units
         int32_t to_int32(const char* str) const;
         uint32_t to_uint32(const char* str) const;
         int64_t to_int64(const char* str) const;
         uint64_t to_uint64(const char* str) const;
         double to_double(const char* str) const;
         bool to_bool(const char* str) const;

         // maps of functions/operators and units
         typedef std::map<Workflow::TypeEnum::Type, int> SupportedTypesMap;
         static SupportedTypesMap SupportedTypes;

         static SupportedTypesMap initSupportedTypesMap()
         {
            SupportedTypesMap tmpMap;
            tmpMap[Workflow::TypeEnum::BoolType] = 1;
            tmpMap[Workflow::TypeEnum::Int32Type] = 2;
            tmpMap[Workflow::TypeEnum::UInt32Type] = 3;
            tmpMap[Workflow::TypeEnum::Int64Type] = 4;
            tmpMap[Workflow::TypeEnum::UInt64Type] = 5;
            tmpMap[Workflow::TypeEnum::DoubleType] = 6;
            tmpMap[Workflow::TypeEnum::StringType] = 100;
            tmpMap[Workflow::TypeEnum::VariableType] = 200;
            tmpMap[Workflow::TypeEnum::ArrayType] = 300;
            return tmpMap;
         }

         // maps of FieldState
         typedef std::map<std::string, Bct::Workflow::Aggregates::FieldStateEnum::FieldState> FieldStateMap;
         static FieldStateMap StateMap;

         static FieldStateMap initFieldStateMap()
         {
            FieldStateMap tmpMap;
            tmpMap["Unavailable"] = Bct::Workflow::Aggregates::FieldStateEnum::Unavailable;
            tmpMap["NotSet"] = Bct::Workflow::Aggregates::FieldStateEnum::NotSet;
            tmpMap["Set"] = Bct::Workflow::Aggregates::FieldStateEnum::Set;
            tmpMap["Constant"] = Bct::Workflow::Aggregates::FieldStateEnum::Constant;
            tmpMap["Default"] = Bct::Workflow::Aggregates::FieldStateEnum::Default;
            tmpMap["Computed"] = Bct::Workflow::Aggregates::FieldStateEnum::Computed;
            return tmpMap;
         }

         RPNResult * _rpnResult;
      };
   }
}

#endif