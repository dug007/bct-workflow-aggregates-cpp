#include "ReferenceAggregate.h"
#include "ReferenceEnum.h"

#include "catch.hpp"

using namespace Bct::Workflow;
using namespace Bct::Workflow::Implementation;

TEST_CASE("ReferenceUnitTest", "[test]")
{
   ReferenceAggregate ref;

   CHECK(ref.getVersion() == "1.1.0");
   CHECK(ReferenceEnum::Average == ref.enumField.Value());

   ref.enumField = ReferenceEnum::Poor;
   ref.enumField.Value(ReferenceEnum::Poor);
   CHECK(ReferenceEnum::Poor == ref.enumField);
   CHECK(ref.enumField.EnumName() == "ReferenceEnum::Poor");

}
