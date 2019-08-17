#include "ReferenceAggregate.h"
#include "ReferenceEnum.h"
#include "VersionChangeRule.h"
#include "catch.hpp"

using namespace Bct::Workflow;
using namespace Bct::Workflow::Implementation;

TEST_CASE("VersionChangeTest", "[test]")
{
   ReferenceAggregate ref0("1.0.0");
   ReferenceAggregate ref1("1.1.0");

   CHECK(ref0.getVersion() == "1.0.0");
   CHECK(ref1.getVersion() == "1.1.0");

   // convertion from 0 to 1 works with condition
   ref0.doubleField = 99.0;
   ref0.convertToVersion(1);
   CHECK(ref0.doubleField == 99.0);
   ref0.doubleField = 1;
   ref0.convertToVersion(1);
   CHECK(ref0.doubleField == 2);

   // conversion from 1 to 0 works with condition
   ref1.doubleField = 99.0;
   ref1.convertToVersion(0);
   CHECK(ref1.doubleField == 99.0);
   ref1.doubleField = 1;
   ref1.convertToVersion(0);
   CHECK(ref1.doubleField == 3);

   // check non-rules leave field unchanged
   // this is checking version change from/to 0 leaves
   // field unchanged. this is because there is not rule
   // for converting 0 to 0.
   ref0.doubleField = 1;
   ref0.convertToVersion(0);
   CHECK(ref0.doubleField == 1);
}