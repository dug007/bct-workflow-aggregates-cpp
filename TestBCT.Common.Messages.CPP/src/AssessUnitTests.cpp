#include "AssessmentRule.h"
#include "AggAssess.h"
#include "BaseAggregate.h"
#include "AssessMetaData.h"
#include "catch.hpp"

using namespace Bct::Workflow::Aggregates;

TEST_CASE("AssessRulesTest", "[test]")
{
   // Setup metadata then initialize aggregate class with this metadata
   // AggComputeFieldMetaData is defined above
   //AssessMetaData separateMetaData;
   //AggAssess::initMetaData(&separateMetaData.metaData);

   AggAssess a0("1.0.0");
   AggAssess a1("1.1.0");
   AggAssess a2("1.2.0");

   // prove assessment all work in their versions
   AssessmentResult r0 = a0.Assess();
   AssessmentResult r1 = a1.Assess();
   AssessmentResult r2 = a2.Assess();

   CHECK(r0.isSuccess() == false); // field1 field2 ==
   CHECK(r1.isSuccess() == true);  // field1 field2 !=
   CHECK(r2.isSuccess() == true);  // field1 field2 + 11 ==
}
