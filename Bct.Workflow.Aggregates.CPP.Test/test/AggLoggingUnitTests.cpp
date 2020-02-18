#include "ReferenceAggregate.h"
#include "PlateletConfigAggregate.h"
#include "PlateletTemplateAggregate.h"
#include "ReferenceEnum.h"
#include "EnumField.h"
#include "catch.hpp"
#include "rapidjson/prettywriter.h"

#include "TestLogger.h"

#include <list>
#include "RPNEvaluator.h"
using namespace Bct::RPNEvaluator;

using namespace Bct::Workflow;
using namespace Bct::Workflow::Implementation;

TEST_CASE("AggLoggingDefaultNullLoggerUnitTest", "[test]")
{
   IBctLogger* logger = nullptr;

   logger = BaseAggregate::getLogger();
   CHECK(logger != nullptr);
   CHECK( typeid(*logger) == typeid(NullLogger));
}


TEST_CASE("AggLoggingTestLoggerUnitTest", "[test]")
{
   IBctLogger* logger = nullptr;
   BaseAggregate::setLogger(*(new TestLogger));
   logger = BaseAggregate::getLogger();
   CHECK(logger != nullptr);
   CHECK(typeid(*logger) == typeid(TestLogger));
}

TEST_CASE("AggLoggingLogsUnitTest", "[test]")
{
   TestLogger* testLogger = new TestLogger;
   BaseAggregate::setLogger(*testLogger);
   std::string message = "";

   // convertToVersion(): NoSuchVersion error
   ReferenceAggregate ref0a("v1.0.0");
   // convertion from 0 to 1 works with condition
   try
   {
      ref0a.convertToVersion("v1.0.a");
   }
   catch (NoSuchVersion & ex)
   {
      message = "logError call successful";
      CHECK(testLogger->getStringOutput()[0] == message);
   }


   // "rpn is null or empty"
   std::string rpnExpr = "";
   RPNEvaluator evaluator;
   RPNResult result;
   std::list<std::string> variables;
   evaluator.GetVariables(rpnExpr, variables, result);
   testLogger->logWarning(result.errorMsg, __FILE__, __LINE__);
   message = "logWarning call successful";
   CHECK(testLogger->getStringOutput()[1] == message);

   std::map<std::string, RPNVariable> varMap;
   bool rc = evaluator.EvaluateRPNExpression(rpnExpr, varMap, result);
   CHECK(rc == false);
   testLogger->logDebug(result.errorMsg, __FILE__, __LINE__);
   message = "logDebug call successful";
   CHECK(testLogger->getStringOutput()[2] == message);

   PlateletTemplateAggregate Platelet_100("1.0.0"); //("a.b.c");
   Platelet_100.yield = 0.0;
   Platelet_100.volumeMl = 500.0;
   Platelet_100.cellsPerMl = 5.0e6 * 6; 
   Platelet_100.updateCalculatedFields(); // Unable to update Calculated Fields
   testLogger->logInfo("Unable to update Calculated Fields", __FILE__, __LINE__); ;
   message = "logInfo call successful";
   CHECK(testLogger->getStringOutput()[3] == message);
}

