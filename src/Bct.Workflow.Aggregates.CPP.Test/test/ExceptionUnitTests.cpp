#include "RPNEvalException.h"
#include "catch.hpp"

using namespace Bct::Workflow::Aggregates;

class ThrowsException
{
public:
   void ThrowIt()
   {
      throw RPNEvalException("aggname", "1 1 +", "error was found");
   }
};


TEST_CASE("RpnExceptionUnitTest", "[test]")
{
   ThrowsException e;
   try
   {
      e.ThrowIt();
   }
   catch (const RPNEvalException &exc)
   {
      std::string expected = "Aggregate: aggname, Expression: 1 1 +, Error Message: error was found";
      std::string actual = exc.what();
      CHECK(expected == actual);
   }
}
