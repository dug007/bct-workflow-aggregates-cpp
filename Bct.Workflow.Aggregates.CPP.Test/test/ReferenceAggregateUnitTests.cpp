#include "ReferenceAggregate.h"
#include "ReferenceEnum.h"
#include "EnumField.h"
#include "catch.hpp"

using namespace Bct::Workflow;
using namespace Bct::Workflow::Implementation;

TEST_CASE("ReferenceUnitTest", "[test]")
{ 
   ReferenceAggregate ref;

   CHECK(ref.getVersion() == "1.1.0");

   // EnumField tests

   CHECK(ReferenceEnum::Average == ref.enumField.Value());
   ReferenceEnum::Reference r;
   r = ReferenceEnum::Good;
   ref.enumField = r;
   CHECK(ref.enumField == ReferenceEnum::Good);

   ref.enumField = ReferenceEnum::BelowAverage;
   r = ref.enumField;
   CHECK(ReferenceEnum::BelowAverage == ref.enumField);
   CHECK(r == ReferenceEnum::BelowAverage);

   ref.enumField = ReferenceEnum::Poor;
   CHECK(ref.enumField.EnumName() == "ReferenceEnum::Poor");
   CHECK("2" == ref.enumField.s_enumValueString("ReferenceEnum::Average"));
}
