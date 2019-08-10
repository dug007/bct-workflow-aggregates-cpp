#ifndef RPNEvaluator_H
#define RPNEvaluator_H
#include "FuncOper.h"
#include "RPNVariable.h"
#include "Token.h"
#include "TypeEnum.h"
#include <list>
#include <map>
#include <stack>
#include <string>
#include <vector>

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
			void GetVariables(std::string rpn, std::list<std::string> &variables);

			/// <summary>
			/// Evaluates the RPN expression
			/// </summary>
			/// <param name="rpn">The RPN expression as a string</param>
			/// <param name="variableMap">A map containing the variables used for this expression</param>
			/// <param name="valueType">The value type as an enum</param>
			/// <param name="value">The resulting data value from the function</param>
         /// <returns> A boolean value corresponding to if the evaluation is a success</return>
         bool EvaluateRPNExpression(const std::string &rpn, std::map<std::string, RPNVariable> &variableMap, Workflow::TypeEnum::Type &valueType, std::string &value);

		private:
			/// 
			/// Takes a token that just has the name and fills-out the rest of the token information.
			/// It looks up variables and replaces them with values.
			/// 
         static bool ClassifyToken(Token &token, std::map<std::string, RPNVariable> variableMap, std::list<std::string> &variables);

			/// 
			/// Wrapped the pop from the stack so not to duplicate the check every time
			///
			Token PopFromStack(std::stack<Token> &stack);

			///
			/// Takes a list of tokens and upconverts them to the widest type in the group.
			/// Optionally takes a type for the function/operator return to force the input arguments to match.
			/// Can't convert strings to anything.
			///
         static bool NormalizeTypes(std::vector<Token> &argList, Workflow::TypeEnum::Type opReturnType = Workflow::TypeEnum::EmptyType);

			///
			/// Execute the function/operator
			///
         static bool DoOp(std::string op, std::vector<Token> argList, std::map<std::string, RPNVariable> &variableMap, Token &rtnTok);

			///
			/// Template for operations that return a bool but take a numeric type
			///
         template <typename T>
         static bool DoOpBoolNum(std::string op, T lhs, T rhs, bool &rtn)
         {
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
            else
            {
               return false;
            }

            return true;
         }

			///
			/// Template for operations that take and return a type of int
			///
         template <typename T>
         static T DoOpInt(std::string op, std::vector<T> &args, T &rtn)
         {
            T result;
            if (op == "$Negate")
            {
               rtn = args[0] * -1;
            }
            else if (op == "$Min")
            {
               if (args.size() == 0)
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
               if (args.size() == 0)
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
               result = result / args.size();
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
               return false;
            }
            return true;
         }

			// functions for the other cases
         static bool DoOpBoolVar(std::string op, std::vector<Token> argList, std::map<std::string, RPNVariable> &variableMap, bool &rtn);
         static bool DoOpBool(std::string op, bool lhs, bool rhs, bool &rtn);
         static bool DoOpDbl(std::string op, std::vector<double> &args, double &rtn);
         static bool DoOpStr(std::string op, std::vector<std::string> &args, std::string &rtnStr);

			// conversion functions from strings to units
			static int32_t to_int32(const char *str);
			static uint32_t to_uint32(const char *str);
			static int64_t to_int64(const char *str);
			static uint64_t to_uint64(const char *str);
			static double to_double(const char *str);
			static bool to_bool(const char *str);

			// maps of functions/operators and units
			typedef std::map<std::string, FuncOper> FuncOpersMap;
			static FuncOpersMap FuncOpers;
			typedef std::map<Workflow::TypeEnum::Type, int> SupportedTypesMap;
			static SupportedTypesMap SupportedTypes;

			// map: name, number of arguments, the required input type of the function, the return type if it can be different from the inputs
			static FuncOpersMap initFuncOpersMap()
			{
				FuncOpersMap tmpMap;
				tmpMap["$Negate"] = FuncOper("$Negate", 1, Workflow::TypeEnum::EmptyType, Workflow::TypeEnum::EmptyType);
				tmpMap["$Sqrt"] = FuncOper("$Sqrt", 1, Workflow::TypeEnum::DoubleType, Workflow::TypeEnum::EmptyType);
				tmpMap["$Pow"] = FuncOper("$Pow", 2, Workflow::TypeEnum::DoubleType, Workflow::TypeEnum::EmptyType);
				tmpMap["$Min"] = FuncOper("$Min", 99, Workflow::TypeEnum::EmptyType, Workflow::TypeEnum::EmptyType);
				tmpMap["$Max"] = FuncOper("$Max", 99, Workflow::TypeEnum::EmptyType, Workflow::TypeEnum::EmptyType);
				tmpMap["$Mean"] = FuncOper("$Min", 99, Workflow::TypeEnum::EmptyType, Workflow::TypeEnum::EmptyType);
				tmpMap["$Min"] = FuncOper("$Mean", 99, Workflow::TypeEnum::EmptyType, Workflow::TypeEnum::EmptyType);
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
				tmpMap["$SetState"] = FuncOper("$SetState", 1, Workflow::TypeEnum::VariableType, Workflow::TypeEnum::BoolType);
				tmpMap["$EnteredLater"] = FuncOper("$EnteredLater", 2, Workflow::TypeEnum::VariableType, Workflow::TypeEnum::BoolType);
				return tmpMap;
			}

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
				return tmpMap;
			}
		};
	}
}

#endif