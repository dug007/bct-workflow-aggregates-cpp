#include "ReferenceAggregate.h"
#include "catch.hpp"

using namespace Bct::Workflow::Implementation;

TEST_CASE("CodeGenerationTest", "[test]")
{
   ReferenceAggregate a;
   a.updateCalculatedFields();
   CHECK(a.doubleField == 4.0);

   a.doubleField = 1;
   a.convertToVersion("v1.0.0");
   CHECK(a.doubleField == 3);


}
