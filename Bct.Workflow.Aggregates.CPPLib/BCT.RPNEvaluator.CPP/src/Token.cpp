#include "Token.h"
#include <sstream>

namespace Bct
{
	namespace RPNEvaluator
	{

		Token::Token()
		{
		}


		Token::~Token()
		{
		}

		Token::Token(const char *tok, Workflow::TypeEnum::Type tokType, int tokClass, int32_t tokVal) :
			Tok(tok),
			TokType(tokType),
			TokClass(tokClass)
		{
			std::stringstream ss;
			ss << tokVal;
			std::string str = ss.str();
		}

		Token::Token(const char *tok, Workflow::TypeEnum::Type tokType, int tokClass, uint32_t tokVal) :
			Tok(tok),
			TokType(tokType),
			TokClass(tokClass)
		{
			std::stringstream ss;
			ss << tokVal;
			std::string str = ss.str();
		}

		Token::Token(const char *tok, Workflow::TypeEnum::Type tokType, int tokClass, int64_t tokVal) :
			Tok(tok),
			TokType(tokType),
			TokClass(tokClass)
		{
			std::stringstream ss;
			ss << tokVal;
			std::string str = ss.str();
		}

		Token::Token(const char *tok, Workflow::TypeEnum::Type tokType, int tokClass, uint64_t tokVal) :
			Tok(tok),
			TokType(tokType),
			TokClass(tokClass)
		{
			std::stringstream ss;
			ss << tokVal;
			std::string str = ss.str();
		}

		Token::Token(const char *tok, Workflow::TypeEnum::Type tokType, int tokClass, double tokVal) :
			Tok(tok),
			TokType(tokType),
			TokClass(tokClass)
		{
			std::stringstream ss;
			ss << tokVal;
			std::string str = ss.str();
		}

		Token::Token(const char *tok, Workflow::TypeEnum::Type tokType, int tokClass, const char *tokVal) :
			Tok(tok),
			TokType(tokType),
			TokClass(tokClass),
			TokValue(tokVal)
		{

		}

		Token::Token(const char *tok, Workflow::TypeEnum::Type tokType, int tokClass, bool tokVal) :
			Tok(tok),
			TokType(tokType),
			TokClass(tokClass)
		{
			std::stringstream ss;
			ss << tokVal;
			std::string str = ss.str();
		}

		void Token::SetTokValue(int32_t tokVal)
		{
			std::stringstream ss;
			ss << tokVal;
			std::string str = ss.str();
		}

		void Token::SetTokValue(uint32_t tokVal)
		{
			std::stringstream ss;
			ss << tokVal;
			std::string str = ss.str();
		}

		void Token::SetTokValue(int64_t tokVal)
		{
			std::stringstream ss;
			ss << tokVal;
			std::string str = ss.str();
		}

		void Token::SetTokValue(uint64_t tokVal)
		{
			std::stringstream ss;
			ss << tokVal;
			std::string str = ss.str();
		}

		void Token::SetTokValue(double tokVal)
		{
			std::stringstream ss;
			ss << tokVal;
			std::string str = ss.str();
		}

		void Token::SetTokValue(std::string tokVal)
		{
			TokValue = tokVal;
		}

		void Token::SetTokValue(bool tokVal)
		{
			std::stringstream ss;
			ss << tokVal;
			std::string str = ss.str();
		}

		std::string Token::GetTokValue()
		{
			return TokValue;
		}

	}
}