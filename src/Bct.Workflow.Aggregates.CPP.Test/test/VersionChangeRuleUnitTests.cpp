#include "ReferenceAggregate.h"
#include "ReferenceEnum.h"
#include "VersionChangeRule.h"
#include "catch.hpp"

using namespace Bct::Workflow;
using namespace Bct::Workflow::Implementation;

TEST_CASE("VersionChangeTest", "[test]")
{
   // Test these rules
   //tm.addFieldMetaToAllVersions(5, FieldStateEnum::Default, "1.0");       << doubleField
   //tm.addVersionChangeRule(5, 1, "doubleField 1 ==", "2").toVersion(0);  // from 0 to 1
   //tm.addVersionChangeRule(5, 0, "doubleField 1 ==", "3").toVersion(1);  // from 1 to 0

   ReferenceAggregate ref0a("v1.0.0");
   CHECK(ref0a.getVersion() == "v1.0.0");
   // convertion from 0 to 1 works with condition
   ref0a.doubleField = 99.0;
   ref0a.convertToVersion("v1.1.0");
   CHECK(ref0a.doubleField == 99.0);
   CHECK(ref0a.getVersion() == "v1.1.0");

   ReferenceAggregate ref0b("v1.0.0");
   ref0b.doubleField = 1;
   ref0b.convertToVersion("v1.1.0");
   CHECK(ref0b.doubleField == 2);
   CHECK(ref0b.getVersion() == "v1.1.0");

   ReferenceAggregate ref1a("v1.1.0");
   CHECK(ref1a.getVersion() == "v1.1.0");
   // conversion from 1 to 0 works with condition
   ref1a.doubleField = 99.0;
   ref1a.convertToVersion("v1.0.0");
   CHECK(ref1a.doubleField == 99.0);

   ReferenceAggregate ref1b("v1.1.0");
   CHECK(ref1b.getVersion() == "v1.1.0");
   ref1b.doubleField = 1;
   ref1b.convertToVersion("v1.0.0");
   CHECK(ref1b.doubleField == 3);

   // check non-rules leave field unchanged
   // this is checking version change from/to 0 leaves
   // field unchanged. this is because there is not rule
   // for converting 0 to 0.
   ReferenceAggregate ref1c("v1.0.0");
   ref1c.doubleField = 1;
   ref1c.convertToVersion("v1.0.0");
   CHECK(ref1c.doubleField == 1);
}