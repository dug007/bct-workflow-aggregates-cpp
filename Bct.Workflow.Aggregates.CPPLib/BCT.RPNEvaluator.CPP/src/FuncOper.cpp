#include "FuncOper.h"

namespace Bct
{

	FuncOper::FuncOper() :
		Name(""),
		ArgNum(0),
		RequiredType(Workflow::TypeEnum::EmptyType),
		ReturnType(Workflow::TypeEnum::EmptyType)
	{
	}

	FuncOper::FuncOper(std::string name, int argNum, Workflow::TypeEnum::Type requiredType, Workflow::TypeEnum::Type returnType) :
		Name(name),
		ArgNum(argNum),
		RequiredType(requiredType),
		ReturnType(returnType)
	{
	}


	FuncOper::~FuncOper()
	{
	}
}