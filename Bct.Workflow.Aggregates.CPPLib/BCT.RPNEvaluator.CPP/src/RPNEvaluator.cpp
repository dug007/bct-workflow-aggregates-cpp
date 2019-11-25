#include "RPNEvaluator.h"
#include "TokenClass.h"
#include <algorithm>
#include <cctype>
#include <iomanip>
#include <cmath>
#include <iterator>
#include <queue>
#include <sstream>
#include "FunctionMap.h"

namespace Bct
{
	namespace RPNEvaluator
	{

		FunctionMap::FuncOpersMap FuncOpers = FunctionMap::initFuncOpersMap();
		RPNEvaluator::SupportedTypesMap RPNEvaluator::SupportedTypes = initSupportedTypesMap();

		RPNEvaluator::RPNEvaluator()
		{
		}


		RPNEvaluator::~RPNEvaluator()
		{
		}

		void RPNEvaluator::GetVariables(std::string rpn, std::list<std::string> &variables)
		{
			if (rpn.empty())
			{
				return;
			}

			// split the string by spaces
			std::istringstream rpnStrstr(rpn);
			std::list<std::string> baseTokens;
			std::copy(std::istream_iterator<std::string>(rpnStrstr), std::istream_iterator<std::string>(), std::back_inserter(baseTokens));

			// empty variable map, we don't need it here but ClassifyToken takes it
			std::map<std::string, RPNVariable> variableMap;

			std::list<std::string>::iterator tok_it;

			// find the variables
			for (tok_it = baseTokens.begin(); tok_it != baseTokens.end(); ++tok_it)
			{
				Token token;
				token.Tok = *tok_it;

				ClassifyToken(token, variableMap, variables);
			}

		}
		bool RPNEvaluator::EvaluateRPNExpression(const std::string &rpn, std::map<std::string, RPNVariable> &variableMap, Workflow::TypeEnum::Type &valueType, std::string &value)
		{
			if (rpn.empty())
			{
				//throw std::invalid_argument("rpn is null or empty");
				return false;
			}

			std::map<std::string, RPNVariable>::iterator map_it;

			for (map_it = variableMap.begin(); map_it != variableMap.end(); ++map_it)
			{

				if (SupportedTypes.find(map_it->second.VarType) == SupportedTypes.end())
				{
					//std::stringstream msg;
					//msg << "Type " << TypeName(variable.second.VarType) << " is not supported for variable " << variable.first;
					//throw std::invalid_argument(msg.str());
					return false;
				}
			}

			// split the string by spaces
			std::istringstream rpnStrstr(rpn);
			std::list<std::string> baseTokens;
			std::copy(std::istream_iterator<std::string>(rpnStrstr), std::istream_iterator<std::string>(), std::back_inserter(baseTokens));
			std::queue<Token> rpnQueue;

			// we don't need this, but ClassifyToken takes it
			std::list<std::string> variables;

			std::list<std::string>::iterator it;
			for (it = baseTokens.begin(); it != baseTokens.end(); ++it)
			{
				Token token;
				token.Tok = *it;
				if (!ClassifyToken(token, variableMap, variables))
				{
					return false;
				}
				rpnQueue.push(token);
			}

			// process the tokens - all we should have at this point are values and functions/operators
			std::stack<Token> workStack;
			while (!rpnQueue.empty())
			{
				Token token = rpnQueue.front();
				rpnQueue.pop();

				if (token.TokClass == value_t)
				{
					workStack.push(token);
				}
				else if (token.TokClass == funcOper_t)
				{
					if (FuncOpers.find(token.Tok) != FuncOpers.end())
					{
						uint64_t funcArgNum = 0;
						std::vector<Token> argList;

						// get the # of arguments for functions with variable # of args
						if (FuncOpers[token.Tok].ArgNum == 99)
						{
							Token argNum = PopFromStack(workStack);

							if (argNum.TokClass == value_t && argNum.TokType != Workflow::TypeEnum::DoubleType && argNum.TokType != Workflow::TypeEnum::StringType && argNum.TokType != Workflow::TypeEnum::BoolType)
							{
								funcArgNum = to_uint64(argNum.TokValue.c_str());
							}
							else
							{
								// if the number of arguments isn't a number, use 0
								funcArgNum = 0;
							}
						}
						else
						{
							// get the # of arguments for standard functions/operators
							funcArgNum = (uint64_t)FuncOpers[token.Tok].ArgNum;
						}

						for (uint64_t arg = 0; arg < funcArgNum; ++arg)
						{
							argList.push_back(PopFromStack(workStack));
						}

						// do any type conversions, don't normalize for variable map functions
						if (FuncOpers[token.Tok].RequiredType != Workflow::TypeEnum::VariableType)
						{
							if (!NormalizeTypes(argList, FuncOpers[token.Tok].RequiredType))
							{
								return false;
							}
						}

						// do the function/operation
						Token rtnTok;
						if (!DoOp(token.Tok, argList, variableMap, rtnTok))
						{
							return false;
						}

						// push the result on the stack
						workStack.push(rtnTok);
					}
					else
					{
						//std::stringstream msg;
						//msg << "Unknown function or operator " << token.Tok << " on workQueue";
						//throw std::invalid_argument(msg.str());
						return false;
					}
				}
				else
				{
					//std::stringstream msg;
					//msg << "Unknown token class " << token.TokClass << " on workQueue";
					//throw std::invalid_argument(msg.str());
					return false;
				}
			}

			// grab the top of the stack for output
			Token result = PopFromStack(workStack);
			valueType = result.TokType;
			value = result.TokValue;

			return true;
		}

		///
		/// Execute the function/operator
		///
		bool RPNEvaluator::DoOp(std::string op, std::vector<Token> argList, std::map<std::string, RPNVariable> &variableMap, Token &rtnTok)
		{
			Workflow::TypeEnum::Type argType;
			if (argList.size() > 0)
			{
				argType = argList.front().TokType;
			}
			else
			{
				argType = Workflow::TypeEnum::DoubleType;
			}
			if (op == "true")
			{
				bool result = true;
				//std::string resultStr = result ? "true" : "false";
				rtnTok.Tok = op;
				rtnTok.TokType = Workflow::TypeEnum::BoolType;
				rtnTok.TokClass = value_t;
				rtnTok.TokValue = op;
				return true;
			}
			else if (op == "false")
			{
				bool result = false;
				//std::string resultStr = result ? "true" : "false";
				rtnTok.Tok = op;
				rtnTok.TokType = Workflow::TypeEnum::BoolType;
				rtnTok.TokClass = value_t;
				rtnTok.TokValue = op;
				return true;
			}
			else if (op == "$If")
			{
				if (argList[2].TokValue == "true")
				{
					rtnTok.Tok = argList[1].Tok; //result 1
					rtnTok.TokType = argList[1].TokType;
					rtnTok.TokClass = value_t;
					rtnTok.TokValue = argList[1].TokValue;
					return true;

				}
				else if (argList[2].TokValue == "false")
				{
					rtnTok.Tok = argList[0].Tok; //result 2
					rtnTok.TokType = argList[0].TokType;
					rtnTok.TokClass = value_t;
					rtnTok.TokValue = argList[0].TokValue;
					return true;
				}
				else
				{
					return false;
				}
			}
			// Currently $Size is the only function supported for Arrays
			else if (FuncOpers[op].RequiredType == Workflow::TypeEnum::ArrayType)
			{
				std::string  tmpStr = argList[0].TokValue;
				for (size_t i = 0; i < tmpStr.length(); i++)
				{
					if (!isdigit(tmpStr[i]))
					{
						return false;
					}
				}
					rtnTok.Tok = argList[0].Tok;
					rtnTok.TokType = Workflow::TypeEnum::UInt32Type;
					rtnTok.TokClass = value_t;
					// Array values come in as their size so just return the value
					rtnTok.TokValue = argList[0].TokValue;
					return true;
			}
			else if (FuncOpers[op].RequiredType == Workflow::TypeEnum::VariableType)
			{
				if (FuncOpers[op].Name == "$GetState")
				{
					std::string result;
					if (!DoOpVar(op, argList, variableMap, result))
					{
						return false;
					}
					std::stringstream ss;
					ss << result;
					std::string resultStr = ss.str();

					rtnTok.Tok = resultStr;
					rtnTok.TokType = Workflow::TypeEnum::VariableType;
					rtnTok.TokClass = value_t;
					rtnTok.TokValue = resultStr;
					return true;
				}
				else
				{
					bool result;
					if (!DoOpBoolVar(op, argList, variableMap, result))
					{
						return false;
					}
					std::string resultStr = result ? "true" : "false";
					rtnTok.Tok = resultStr.c_str();
					rtnTok.TokType = Workflow::TypeEnum::BoolType;
					rtnTok.TokClass = value_t;
					rtnTok.TokValue = resultStr.c_str();
					return true;
				}
			}
			else if (FuncOpers[op].ReturnType == Workflow::TypeEnum::BoolType)
			{
				// the compiler will upconvert for us
				if (argType == Workflow::TypeEnum::Int32Type || argType == Workflow::TypeEnum::Int64Type)
				{
					// Int boolean operators need 2 args
					if (argList.size() > 1)
					{
						std::vector<int64_t> argVect;
						std::vector<Token>::iterator argList_it;
						for (argList_it = argList.begin(); argList_it != argList.end(); ++argList_it)
						{
							int64_t tmp = to_int64(argList_it->TokValue.c_str());
							argVect.push_back(tmp);
						}
						bool result;
						if (!DoOpBoolNum(op, argVect, result))
						{
							return false;
						}
						std::string resultStr = result ? "true" : "false";

						rtnTok.Tok = resultStr.c_str();
						rtnTok.TokType = Workflow::TypeEnum::BoolType;
						rtnTok.TokClass = value_t;
						rtnTok.TokValue = resultStr.c_str();
						return true;
					}
					else
					{
						//std::stringstream msg;
						//msg << "Incorrect number of arguments for " << op;
						//throw std::invalid_argument(msg.str());
						return false;
					}
				}
				// the compiler will upconvert for us
				else if (argType == Workflow::TypeEnum::UInt32Type || argType == Workflow::TypeEnum::UInt64Type)
				{
					// Int boolean operators need 2 args
					if (argList.size() > 1)
					{
						std::vector<uint64_t> argVect;
						std::vector<Token>::iterator argList_it;
						for (argList_it = argList.begin(); argList_it != argList.end(); ++argList_it)
						{
							uint64_t tmp = to_int64(argList_it->TokValue.c_str());
							argVect.push_back(tmp);
						}
						bool result;
						if (!DoOpBoolNum(op, argVect, result))
						{
							return false;
						}
						std::string resultStr = result ? "true" : "false";

						rtnTok.Tok = resultStr.c_str();
						rtnTok.TokType = Workflow::TypeEnum::BoolType;
						rtnTok.TokClass = value_t;
						rtnTok.TokValue = resultStr.c_str();
						return true;
					}
					else
					{
						//std::stringstream msg;
						//msg << "Incorrect number of arguments for " << op;
						//throw std::invalid_argument(msg.str());
						return false;
					}
				}
				else if (argType == Workflow::TypeEnum::DoubleType)
				{
					// Int boolean operators need 2 args
					if (argList.size() > 1)
					{
						std::vector<double> argVect;
						std::vector<Token>::iterator argList_it;
						for (argList_it = argList.begin(); argList_it != argList.end(); ++argList_it)
						{
							double tmp = to_double(argList_it->TokValue.c_str());
							argVect.push_back(tmp);
						}
						bool result;
						if (!DoOpBoolNum(op, argVect, result))
						{
							return false;
						}
						std::string resultStr = result ? "true" : "false";

						rtnTok.Tok = resultStr.c_str();
						rtnTok.TokType = Workflow::TypeEnum::BoolType;
						rtnTok.TokClass = value_t;
						rtnTok.TokValue = resultStr.c_str();
						return true;
					}
					else
					{
						//std::stringstream msg;
						//msg << "Incorrect number of arguments for " << op;
						//throw std::invalid_argument(msg.str());
						return false;
					}
				}
				else if (argType == Workflow::TypeEnum::BoolType)
				{
					std::vector<bool> argVect;
					std::vector<Token>::iterator argList_it;
					for (argList_it = argList.begin(); argList_it != argList.end(); ++argList_it)
					{
						bool tmp = false;
						if (argList_it->TokValue == "true")
						{
							tmp = true;
						}
						argVect.push_back(tmp);
					}
					bool result;
					if (!DoOpBool(op, argVect, result))
					{
						return false;
					}
					std::string resultStr = result ? "true" : "false";

					rtnTok.Tok = resultStr.c_str();
					rtnTok.TokType = Workflow::TypeEnum::BoolType;
					rtnTok.TokClass = value_t;
					rtnTok.TokValue = resultStr.c_str();
					return true;
				}
			}
			else if (argType == Workflow::TypeEnum::Int32Type)
			{
				std::vector<int32_t> argVect;
				std::vector<Token>::iterator argList_it;
				for (argList_it = argList.begin(); argList_it != argList.end(); ++argList_it)
				{
					int32_t tmp = to_int32(argList_it->TokValue.c_str());
					argVect.push_back(tmp);
				}

				int32_t result;
				if (!DoOpInt(op, argVect, result))
				{
					return false;
				}

				std::stringstream ss;
				ss << result;
				std::string result_str = ss.str();

				rtnTok.Tok = result_str;
				rtnTok.TokType = argType;
				rtnTok.TokClass = value_t;
				rtnTok.TokValue = result_str;
				return true;
			}
			else if (argType == Workflow::TypeEnum::UInt32Type)
			{
				std::vector<uint32_t> argVect;
				std::vector<Token>::iterator argList_it;
				for (argList_it = argList.begin(); argList_it != argList.end(); ++argList_it)
				{
					uint32_t tmp = to_uint32(argList_it->TokValue.c_str());
					argVect.push_back(tmp);
				}

				uint32_t result;
				if (!DoOpInt(op, argVect, result))
				{
					return false;
				}
				std::stringstream ss;
				ss << result;
				std::string result_str = ss.str();

				rtnTok.Tok = result_str;
				rtnTok.TokType = argType;
				rtnTok.TokClass = value_t;
				rtnTok.TokValue = result_str;
				return true;
			}
			else if (argType == Workflow::TypeEnum::Int64Type)
			{
				std::vector<int64_t> argVect;
				std::vector<Token>::iterator argList_it;
				for (argList_it = argList.begin(); argList_it != argList.end(); ++argList_it)
				{
					int64_t tmp = to_int64(argList_it->TokValue.c_str());
					argVect.push_back(tmp);
				}

				int64_t result;
				if (!DoOpInt(op, argVect, result))
				{
					return false;
				}
				std::stringstream ss;
				ss << result;
				std::string result_str = ss.str();

				rtnTok.Tok = result_str;
				rtnTok.TokType = argType;
				rtnTok.TokClass = value_t;
				rtnTok.TokValue = result_str;
				return true;
			}
			else if (argType == Workflow::TypeEnum::UInt64Type)
			{
				std::vector<uint64_t> argVect;
				std::vector<Token>::iterator argList_it;
				for (argList_it = argList.begin(); argList_it != argList.end(); ++argList_it)
				{
					uint64_t tmp = to_uint64(argList_it->TokValue.c_str());
					argVect.push_back(tmp);
				}

				uint64_t result;
				if (!DoOpInt(op, argVect, result))
				{
					return false;
				}
				std::stringstream ss;
				ss << result;
				std::string result_str = ss.str();

				rtnTok.Tok = result_str;
				rtnTok.TokType = argType;
				rtnTok.TokClass = value_t;
				rtnTok.TokValue = result_str;
				return true;
			}
			else if (argType == Workflow::TypeEnum::DoubleType)
			{
				std::vector<double> argVect;

				std::vector<Token>::iterator argList_it;
				for (argList_it = argList.begin(); argList_it != argList.end(); ++argList_it)
				{
					double tmp = to_double(argList_it->TokValue.c_str());
					argVect.push_back(tmp);
				}

				double result;
				if (!DoOpDbl(op, argVect, result))
				{
					return false;
				}
				std::ostringstream ss;
				ss << std::setprecision(10) << std::fixed << result;
				std::string result_str = ss.str();

				rtnTok.Tok = result_str;
				rtnTok.TokType = argType;
				rtnTok.TokClass = value_t;
				rtnTok.TokValue = result_str;
				return true;
			}
			else if (argType == Workflow::TypeEnum::StringType)
			{
				std::vector<std::string> argVect;

				std::vector<Token>::iterator argList_it;
				for (argList_it = argList.begin(); argList_it != argList.end(); ++argList_it)
				{
					argVect.push_back(argList_it->TokValue);
				}

				std::string result;
				if (!DoOpStr(op, argVect, result))
				{
					return false;
				}

				rtnTok.Tok = result.c_str();
				rtnTok.TokType = argType;
				rtnTok.TokClass = value_t;
				rtnTok.TokValue = result.c_str();
				return true;
			}
			else
			{
				//throw std::invalid_argument("Invalid data type");
				return false;
			}

			rtnTok.Tok = "";
			rtnTok.TokType = Workflow::TypeEnum::EmptyType;
			rtnTok.TokClass = value_t;
			rtnTok.TokValue = "";
			return false;
		}

		///
		/// Operations with boolean return that take do operations on the variable list, like IsSet, etc
		///
		bool RPNEvaluator::DoOpBoolVar(std::string op, std::vector<Token> argList, std::map<std::string, RPNVariable> &variableMap, bool &rtn)
		{
			std::vector<Token>::iterator argList_it;
			for (argList_it = argList.begin(); argList_it != argList.end(); ++argList_it)
			{
				if (variableMap.find(argList_it->Tok) == variableMap.end())
				{
					return false;
				}
			}

			if (op == "$IsSet")
			{
				Token tok = argList[0];
				rtn = (Bct::Workflow::Aggregates::FieldStateEnum::FieldState::Set == variableMap[tok.Tok].VarState);
			}
			else if (op == "$IsComputed")
			{
				Token tok = argList[0];
				rtn = (Bct::Workflow::Aggregates::FieldStateEnum::FieldState::Computed == variableMap[tok.Tok].VarState);
			}
			else if (op == "$IsDefault")
			{
				Token tok = argList[0];
				rtn = (Bct::Workflow::Aggregates::FieldStateEnum::FieldState::Default == variableMap[tok.Tok].VarState);
			}
			else if (op == "$IsConstant")
			{
				Token tok = argList[0];
				rtn = (Bct::Workflow::Aggregates::FieldStateEnum::FieldState::Constant == variableMap[tok.Tok].VarState);
			}
			else if (op == "$IsNull")
			{
				Token tok = argList[0];
				rtn = (Bct::Workflow::Aggregates::FieldStateEnum::FieldState::NotSet == variableMap[tok.Tok].VarState);
			}
			else if (op == "$HasValue")
			{
				Token tok = argList[0];
				rtn = (Bct::Workflow::Aggregates::FieldStateEnum::FieldState::Set == variableMap[tok.Tok].VarState || Bct::Workflow::Aggregates::FieldStateEnum::FieldState::Computed == variableMap[tok.Tok].VarState || Bct::Workflow::Aggregates::FieldStateEnum::FieldState::Default == variableMap[tok.Tok].VarState || Bct::Workflow::Aggregates::FieldStateEnum::FieldState::Constant == variableMap[tok.Tok].VarState);
			}
			else if (op == "$SetState")
			{
				Token state = argList[0];
				Token tok = argList[1];
				variableMap[tok.Tok].VarState = variableMap[state.Tok].VarState;
				rtn = true;
			}
			else if (op == "$EnteredLater")
			{
				if (argList.size() == 2)
				{
					if (variableMap[argList[1].Tok].VarCount > variableMap[argList[0].Tok].VarCount ||
						(variableMap[argList[1].Tok].VarCount > 0 && variableMap[argList[0].Tok].VarCount == 0))
					{
						rtn = true;
					}
					else
					{
						rtn = false;
					}
				}
				else
				{
					//throw std::invalid_argument("Incorrect number of arguments");
					return false;
				}
			}
			else
			{
				//throw std::invalid_argument("Invalid operator for type Variable");
				return false;
			}

			return true;
		}
		bool RPNEvaluator::DoOpVar(std::string op, std::vector<Token> argList, std::map<std::string, RPNVariable> &variableMap, std::string &rtn)
		{
			if (op == "$GetState")
			{
				Token tok = argList[0];
				rtn = Bct::Workflow::Aggregates::FieldStateEnum::FieldStateString(variableMap[tok.Tok].VarState);
			}
			else
			{
				return false;
			}
			return true;
		}

		///
		/// Operations with boolean return that take bools
		///
		bool RPNEvaluator::DoOpBool(std::string op, std::vector<bool> &args, bool &rtn)
		{
			bool lhs, rhs;
			if (args.size() > 1)
			{
				lhs = args[1];
				rhs = args[0];
			}
			else
			{
				lhs = args[0];
			}
			if (op == "!")
			{
				rtn = !lhs;
			}
			else if (op == "==")
			{
				rtn = lhs == rhs;
			}
			else if (op == "!=")
			{
				rtn = lhs != rhs;
			}
			else if (op == "&&")
			{
				rtn = lhs && rhs;
			}
			else if (op == "||")
			{
				rtn = lhs || rhs;
			}
			else
			{
				//throw std::invalid_argument("Invalid operator for type Boolean");
				return false;
			}
			return true;
		}

		///
		/// StringType operations
		///
		bool RPNEvaluator::DoOpStr(std::string op, std::vector<std::string> &args, std::string &rtnStr)
		{
			bool retval = true;
			std::stringstream result;
			if (op == "+")
			{
				result << args[1] << args[0];
				rtnStr = result.str();
				retval = true;
			}
			else
			{
				//throw std::invalid_argument("Invalid operator for type String");
				retval = false;
			}
			return retval;
		}

		///
		/// DoubleType operations
		///
		bool RPNEvaluator::DoOpDbl(std::string op, std::vector<double> &args, double &rtn)
		{
			double result;
			if (op == "$Negate")
			{
				rtn = args[0] * -1;
			}
			else if (op == "$Sqrt")
			{
				rtn = sqrt(args[0]);
			}
			else if (op == "$Pow")
			{
				rtn = pow(args[1], args[0]);
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

					std::vector<double>::iterator args_it;
					for (args_it = args.begin(); args_it != args.end(); ++args_it)
					{
						result = result < *args_it ? result : *args_it;
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

					std::vector<double>::iterator args_it;
					for (args_it = args.begin(); args_it != args.end(); ++args_it)
					{
						result = result > *args_it ? result : *args_it;
					}

					rtn = result;
				}
			}
			else if (op == "$Mean")
			{
				result = 0;

				std::vector<double>::iterator args_it;
				for (args_it = args.begin(); args_it != args.end(); ++args_it)
				{
					result += *args_it;
				}

				result = result / args.size();
				rtn = result;
			}
			else if (op == "$If")
			{
				if (bool(args[2]) == true)
				{
					rtn = args[1]; //result 1
				}
				else if (bool(args[2]) == false)
				{
					rtn = args[0]; //result 2
				}
				else
				{
					return false;
				}
			}
			else if (op == "*")
			{
				rtn = args[0] * args[1];
			}
			else if (op == "/")
			{
				rtn = args[1] / args[0];
			}
			else if (op == "+")
			{
				rtn = args[0] + args[1];
			}
			else if (op == "-")
			{
				rtn = args[1] - args[0];
			}
			else
			{
				//throw std::invalid_argument("Invalid operator for type Double");
				return false;
			}
			return true;
		}

		///
		/// Takes a list of tokens and upconverts them to the widest type in the group.
		/// Optionally takes a type for the function/operator return to force the input arguments to match.
		/// Can't convert strings to anything.
		///
		bool RPNEvaluator::NormalizeTypes(std::vector<Token> &argList, Workflow::TypeEnum::Type opReturnType)
		{
			Workflow::TypeEnum::Type widestType = Workflow::TypeEnum::EmptyType;

			// find the widest type in the list

			std::vector<Token>::iterator argList_it;
			for (argList_it = argList.begin(); argList_it != argList.end(); ++argList_it)
			{
				if (SupportedTypes.find(argList_it->TokType) == SupportedTypes.end())
				{
					//std::stringstream msg;
					//msg << "Unsupported type for " << token.Tok;
					//throw std::invalid_argument(msg.str());
					return false;
				}

				// check if trying to convert from/to a string
				if (
					widestType != Workflow::TypeEnum::EmptyType &&
					(
					(argList_it->TokType == Workflow::TypeEnum::StringType && widestType != Workflow::TypeEnum::StringType)
						||
						(argList_it->TokType != Workflow::TypeEnum::StringType && widestType == Workflow::TypeEnum::StringType)
						)
					)
				{
					//throw std::invalid_argument("Can't convert between string and any other type");
					return false;
				}
				else if (widestType == Workflow::TypeEnum::EmptyType || SupportedTypes[argList_it->TokType] > SupportedTypes[widestType])
				{
					widestType = argList_it->TokType;
				}
			}

			// if the function only has one return type, make sure to normalize to it
			if (opReturnType > Workflow::TypeEnum::EmptyType)
			{
				if (SupportedTypes[widestType] > SupportedTypes[opReturnType])
				{
					//std::stringstream msg;
					//msg << "Can't perform operation on data type " << TypeCodeName(widestType);
					//throw std::invalid_argument(msg.str());
					return false;
				}
				else if (SupportedTypes[widestType] < SupportedTypes[opReturnType])
				{
					widestType = opReturnType;
				}
			}

			// now convert
			for (unsigned int i = 0; i < argList.size(); ++i)
			{
				if (argList[i].TokType != widestType)
				{
					argList[i].TokType = widestType;
				}
			}
			return true;
		}

		/// 
		/// Wrapped the pop from the stack so not to duplicate the check every time
		///
		Token RPNEvaluator::PopFromStack(std::stack<Token> &stack)
		{
			if (!stack.empty())
			{
				Token tmpTok = stack.top();
				stack.pop();
				return tmpTok;
			}
			else
			{
				// if the stack is empty, return a zero (that's what my HP calculator does)
				Token tmpTok("0", Workflow::TypeEnum::Int64Type, value_t, "0");
				return tmpTok;
			}
		}


		/// 
		/// Takes a token that just has the name and fills-out the rest of the token information.
		/// It looks up variables and replaces them with values.
		/// 
		bool RPNEvaluator::ClassifyToken(Token &token, std::map<std::string, RPNVariable> variableMap, std::list<std::string> &variables)
		{
			// functions and operators
			if (FuncOpers.find(token.Tok) != FuncOpers.end())
			{
				token.TokClass = funcOper_t;
				token.TokType = Workflow::TypeEnum::EmptyType;
			}
			// double literals
			else if (token.Tok[0] == '.' || (isdigit(token.Tok[0]) && token.Tok.find(".") != std::string::npos))
			{
				token.TokClass = value_t;
				token.TokType = Workflow::TypeEnum::DoubleType;

				// make sure it converts
				double newDbl = to_double(token.Tok.c_str());
				token.TokValue = token.Tok;
			}
			// integer literals - all converted to Int64
			else if (isdigit(token.Tok[0]) && token.Tok.find(".") == std::string::npos)
			{
				token.TokClass = value_t;
				token.TokType = Workflow::TypeEnum::Int64Type;

				// make sure it converts
				int64_t newInt = to_int64(token.Tok.c_str());
				token.TokValue = token.Tok;
			}
			// variables - converted to their values
			else if (isalpha(token.Tok[0]))
			{
				token.TokClass = value_t;
				variables.push_back(token.Tok);

				if (!variableMap.empty())
				{
					// look up variable
					if (variableMap.find(token.Tok) != variableMap.end())
					{
						token.TokType = variableMap[token.Tok].VarType;
						token.TokValue = variableMap[token.Tok].VarValue;
					}
					else
					{
						//std::stringstream msg;
						//msg << "Variable " << token.Tok << " not in variable map";
						//throw std::invalid_argument(msg.str());
						return false;
					}
				}
			}
			else
			{
				//std::stringstream msg;
				//msg << "Token " << token.Tok << " not recognized";
				//throw std::invalid_argument(msg.str());
				return false;
			}

			return true;
		}

		/// 
		/// Wrapped the convert so not to duplicate the check every time
		///
		int32_t RPNEvaluator::to_int32(const char *str)
		{
			int32_t newInt;
			int i = 0;
			bool isNum = true;
			while (str[i] != 0)
			{
				if ((str[0] < 48 || str[0] > 57) && str[0] != 45)  // if it isn't a number or a '-'
				{
					isNum = false;
					break;
				}
				++i;
			}

			if (isNum)
			{
				std::stringstream(str) >> newInt;
			}
			else
			{
				newInt = 0;
			}

			return newInt;
		}

		/// 
		/// Wrapped the convert so not to duplicate the check every time
		///
		uint32_t RPNEvaluator::to_uint32(const char *str)
		{
			uint32_t newInt;
			int i = 0;
			bool isNum = true;
			while (str[i] != 0)
			{
				if (str[0] < 48 || str[0] > 57)
				{
					isNum = false;
					break;
				}
				++i;
			}

			if (isNum)
			{
				std::stringstream(str) >> newInt;
			}
			else
			{
				newInt = 0;
			}

			return newInt;
		}

		/// 
		/// Wrapped the convert so not to duplicate the check every time
		///
		int64_t RPNEvaluator::to_int64(const char *str)
		{
			int64_t newInt;
			int i = 0;
			bool isNum = true;
			while (str[i] != 0)
			{
				if ((str[0] < 48 || str[0] > 57) && str[0] != 45)  // if it isn't a number or a '-'
				{
					isNum = false;
					break;
				}
				++i;
			}

			if (isNum)
			{
				std::stringstream(str) >> newInt;
			}
			else
			{
				newInt = 0;
			}

			return newInt;
		}

		/// 
		/// Wrapped the convert so not to duplicate the check every time
		///
		uint64_t RPNEvaluator::to_uint64(const char *str)
		{
			uint64_t newInt;
			int i = 0;
			bool isNum = true;
			while (str[i] != 0)
			{
				if (str[0] < 48 || str[0] > 57)
				{
					isNum = false;
					break;
				}
				++i;
			}

			if (isNum)
			{
				std::stringstream(str) >> newInt;
			}
			else
			{
				newInt = 0;
			}

			return newInt;
		}

		/// 
		/// Wrapped the convert so not to duplicate the check every time
		///
		double RPNEvaluator::to_double(const char *str)
		{
			double newVal;
			int i = 0;
			bool isNum = true;
			while (str[i] != 0)
			{
				if ((str[0] < 48 || str[0] > 57) && str[0] != 46 && str[0] != 45) // if it isn't a number or a '.' or a '-'
				{
					isNum = false;
					break;
				}
				++i;
			}

			if (isNum)
			{
				std::stringstream(str) >> newVal;
			}
			else
			{
				newVal = 0.0;
			}

			return newVal;
		}

		/// 
		/// Wrapped the convert so not to duplicate the check every time
		///
		bool RPNEvaluator::to_bool(const char *str)
		{
			std::string tmpStr(str);
			transform(tmpStr.begin(), tmpStr.end(), tmpStr.begin(), ::toupper);

			if (tmpStr == "TRUE")
			{
				return true;
			}
			else
			{
				return false;
			}
		}
	}
}

