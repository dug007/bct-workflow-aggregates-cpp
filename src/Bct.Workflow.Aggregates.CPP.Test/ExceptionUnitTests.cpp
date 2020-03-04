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


TEST_CASE("AssessRulesTest", "[test]")
{
   ThrowsException e;
   try
   {
      e.ThrowIt();
   }
   catch (const RPNEvalException &exc)
   {
      CHECK(exc.what() == "error was found");
   }
}
