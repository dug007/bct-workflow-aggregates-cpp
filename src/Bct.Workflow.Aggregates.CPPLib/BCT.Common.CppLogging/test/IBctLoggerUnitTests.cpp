#include "TestLogger.h"
#include "NullLogger.h"
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

/*
This is a set of Unit Tests for IBctLogger using a bare bones implementation
just to verify that the functions can be called. Whoever implements the interface
will need to test the full functionality of these interface functions.
Therefore the message, file and line are not tested within these unit tests. 
*/
using namespace Bct::Common::CppLogging;

/// <summary>
/// Tests that the BctLoggerFactory returns the NullLogger in IBctLogger if no logger is registered.
/// No conditions are passed.
/// </summary>
TEST_CASE("IBctLogger_NoLogger_ShouldReturnNullLogger", "[test]")
{
   IBctLogger * logger = new NullLogger;
   std::string type = typeid(*logger).name(); //Needs to be demangled for VxWorks
   CHECK(type == "class Bct::Common::CppLogging::NullLogger");
}

/// <summary>
/// Tests that the BctLoggerFactory returns the TestLogger in IBctLogger if TestLogger is registered.
/// </summary>
TEST_CASE("IBctLogger_TestLogger_ShouldReturnTestLogger")
{
   IBctLogger * logger = new TestLogger;
   std::string type = typeid(*logger).name();
   CHECK(type == "class Bct::Common::CppLogging::TestLogger");
}

/// <summary>
/// Tests that the string output in TestLogger is empty because 
/// none of the log functions were called that sets the stringOutput
/// </summary>
TEST_CASE("TestLogger_GetStringOutput_ShouldReturnEmptyVector")
{
   TestLogger* logger = new TestLogger;
   CHECK(logger->getStringOutput().empty());
}

/// <summary>
/// Tests the logDebug function can be called and returns the logDebug message set inside the function
/// </summary>
TEST_CASE("LogDebug_TestLogger_ShouldReturnLogDebugMessage")
{
   TestLogger *logger = new TestLogger;
   logger->logDebug("Message", __FILE__, __LINE__);
   CHECK(logger->getStringOutput()[0] == "logDebug call successful");
}

/// <summary>
/// Tests the logInfo function can be called and returns the logInfo message set inside the function
/// </summary>
TEST_CASE("LogInfo_TestLogger_ShouldReturnLogInfoMessage")
{
   TestLogger *logger = new TestLogger;
   logger->logInfo("Message", __FILE__, __LINE__);
   CHECK(logger->getStringOutput()[0] == "logInfo call successful");
}

/// <summary>
/// Tests the logWarning function can be called and returns the logWarning message set inside the function
/// </summary>
TEST_CASE("LogWarning_TestLogger_ShouldReturnLogWarningMessage")
{
   TestLogger *logger = new TestLogger;
   logger->logWarning("Message", __FILE__, __LINE__);
   CHECK(logger->getStringOutput()[0] == "logWarning call successful");
}

/// <summary>
/// Tests the logError function can be called and returns the logError message set inside the function
/// </summary>
TEST_CASE("LogError_TestLogger_ShouldReturnLogWarningMessage")
{
   TestLogger *logger = new TestLogger;
   logger->logError("Message", __FILE__, __LINE__);
   CHECK(logger->getStringOutput()[0] == "logError call successful");
}