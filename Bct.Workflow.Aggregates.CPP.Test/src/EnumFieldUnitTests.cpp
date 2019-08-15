#include "ReferenceAggregate.h"
#include "TypeEnum.h"
#include "NestedWithReference.h"

#include "catch.hpp"

using namespace Bct::Workflow::Aggregates;
using namespace Bct::Workflow::Implementation;

TEST_CASE("EnumFieldTests", "[test]")
{
   ReferenceAggregate aOrig;
   aOrig.enumField.Value(ReferenceEnum::Good);

   // check copy
   ReferenceAggregate aCopy = aOrig;
   CHECK(aCopy.enumField == ReferenceEnum::Good);
   aCopy.enumField = ReferenceEnum::Average;
   CHECK(aOrig.enumField != ReferenceEnum::Average);
   CHECK(aCopy.enumField == ReferenceEnum::Average);

   // check assignment
   ReferenceAggregate aAssign;
   aAssign = aCopy;
   CHECK(aAssign.enumField == ReferenceEnum::Average);
   CHECK(aAssign.enumField == 2);

   // check string ops
   CHECK(aAssign.enumField.EnumName() == "ReferenceEnum::Average");
   CHECK(aAssign.enumField.s_enumValueString("ReferenceEnum::Average") == "2"); // needed when RPN eval returns ReferenceEnum::Average
   CHECK("2" == aAssign.enumField.ComputedValueString());
   aAssign.enumField.ComputedValueString("4");
   CHECK(aAssign.enumField == ReferenceEnum::BelowAverage);

   // check interop with wrapped enum
   aAssign.enumField = ReferenceEnum::Poor;
   ReferenceEnum::Reference ref = aAssign.enumField.Value();
   CHECK(ref == ReferenceEnum::Poor);
   ref = ReferenceEnum::VeryGood;
   aAssign.enumField = ref;
   CHECK(aAssign.enumField == ReferenceEnum::VeryGood);

   // check enum in nested field assigns ok
   NestedWithReferenceAggregate na;
   CHECK(na.aggField.enumField == ReferenceEnum::Average);
   na.aggField = aAssign;
   CHECK(na.aggField.enumField == ReferenceEnum::VeryGood);

   // will not compile  aAssign.enumField.Va
   // will not compile = aAssign.enumField;

}
