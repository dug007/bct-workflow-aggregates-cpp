#include "AssessmentRule.h"
#include "AggAssess.h"
#include "BaseAggregate.h"
#include "catch.hpp"

using namespace Bct::Workflow::Aggregates;

// this class is the metadata for the ComputeRuleVersion unit test
class AggAssessmentMetaData
{
public:

   AggregateMetaData metaData;

   AggAssessmentMetaData()
   {
      std::string vers[5] =
      {
         "1.0.0",
         "1.1.0",
         "1.2.0",
         "1.3.0",
         "1.4.0"
      };

      for (uint16_t i = 0; i < std::size(vers); i++)
      {
         metaData.versionInfo.push_back(VersionInfo(vers[i]));
         VersionMetaData vm;
         metaData.versionMetaData.push_back(vm);
      }

      // One set of field metadata for all version
      FieldMeta field1Meta("field1", FieldStateEnum::Default, "1", 0);
      FieldMeta field2Meta("field2", FieldStateEnum::Default, "10", 0);

      metaData.versionMetaData[0].fieldMetaData.push_back(field1Meta);
      metaData.versionMetaData[0].fieldMetaData.push_back(field2Meta);
      metaData.fieldMetaData.push_back(field1Meta);
      metaData.fieldMetaData.push_back(field2Meta);

      AssessmentRule ar0("assessv0", "assessv0", "field2 10 ==", "field1 field2 ==", ".0.");
      AssessmentRule ar1("assessv1", "assessv1", "field2 10 ==", "field1 field2 !=", ".1.");
      AssessmentRule ar2("assessv2", "assessv2", "field2 10 ==", "field1 field2 + 11 ==", ".2.");
      AssessmentRule ar3("assessv012", "assessv012", "field2 10 ==", "field1 field2 + 1 - 10 ==", ".0.1.2.");

      metaData.versionMetaData[0].assessmentRules.push_back(ar0);
      metaData.versionMetaData[1].assessmentRules.push_back(ar1);
      metaData.versionMetaData[2].assessmentRules.push_back(ar2);
      metaData.assessmentRules.push_back(ar3);
   };
};


TEST_CASE("AssessRulesTest", "[test]")
{
   // Setup metadata then initialize aggregate class with this metadata
   // AggComputeFieldMetaData is defined above
   AggAssessmentMetaData separateMetaData;
   AggAssess::initMetaData(&separateMetaData.metaData);

   AggAssess a0("1.0.0");
   AggAssess a1("1.1.0");
   AggAssess a2("1.2.0");

   // prove assessment all work in their versions
   AssessmentResult r0 = a0.Assess("assessv0");
   AssessmentResult r1 = a1.Assess("assessv1");
   AssessmentResult r2 = a2.Assess("assessv2");

   CHECK(r0.isSuccess() == false); // field1 field2 ==
   CHECK(r1.isSuccess() == true);  // field1 field2 !=
   CHECK(r2.isSuccess() == true);  // field1 field2 + 11 ==

   // prove assessv012 is in all versions 
   AssessmentResult r0120 = a0.Assess("assessv012");
   AssessmentResult r0121 = a1.Assess("assessv012");
   AssessmentResult r0122 = a2.Assess("assessv012");

   CHECK(r0120.isSuccess() == true);
   CHECK(r0121.isSuccess() == true);
   CHECK(r0122.isSuccess() == true);

   // assessv1 is not in v0
   CHECK_THROWS_AS(a0.Assess("assessv1"), char*);

   // run all assessments
   AssessmentResult mixed = a0.Assess("*"); // run all rules

   CHECK(mixed.isSuccess() == false);
   CHECK(mixed.getErrorIds().size() == 1);
   CHECK(mixed.getErrorIds()[0] == "assessv0");
}
