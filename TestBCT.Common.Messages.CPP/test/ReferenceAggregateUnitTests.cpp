#include "ReferenceAggregate.h"
#include "ReferenceEnum.h"

#include "catch.hpp"

using namespace Bct::Workflow::Aggregates;

TEST_CASE("ReferenceUnitTest", "[test]")
{
   ReferenceAggregate ref;

   CHECK(ref.getVersion() == "1.1.0");
   CHECK(Bct::Workflow::ReferenceEnum::Average == ref.enumField.Value());

}
