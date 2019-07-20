#include "AssessmentRule.h"
#include "AggAssess.h"
#include "BaseAggregate.h"
#include "catch.hpp"

using namespace Bct::Workflow::Aggregates;

// this class is the metadata for the ComputeRuleVersion unit test
class ChildMetaData
{
public:

   AggregateMetaData metaData;

   ChildMetaData()
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
      FieldMeta field1Meta("field1", FieldStateEnum::Default, "1", -1); // -1 means all versions
      FieldMeta field2Meta("field2", FieldStateEnum::Default, "10", -1);

      int16_t k, cnt;

      metaData.fieldMetaData.push_back(field1Meta);
      k = 0; cnt = (int16_t)metaData.fieldMetaData.size() - 1;
      metaData.versionMetaData[k++].fieldMetaDataI.push_back(cnt); // since this is for all versions no need for more vectors

      metaData.fieldMetaData.push_back(field2Meta);
      k = 0; cnt = (int16_t)metaData.fieldMetaData.size() - 1;
      metaData.versionMetaData[k++].fieldMetaDataI.push_back(cnt);

      AssessmentRule ar0("assessv0", "assessv0", "field2 10 ==", "field1 field2 ==", ".0.");      // fails
      AssessmentRule ar1("assessv1", "assessv1", "field2 10 ==", "field1 field2 !=", ".1.");      // passes
      AssessmentRule ar2("assessv2", "assessv2", "field2 10 ==", "field1 field2 + 11 ==", ".2."); // passes
      AssessmentRule ar3("assessv012", "assessv012", "field2 10 ==", "field1 field2 + 1 - 10 ==", ".0.1.2.");

      metaData.assessmentRules.push_back(ar0);
      metaData.versionMetaData[0].assessmentRulesI.push_back((int16_t)metaData.assessmentRules.size() - 1);
      metaData.assessmentRules.push_back(ar1);
      metaData.versionMetaData[1].assessmentRulesI.push_back((int16_t)metaData.assessmentRules.size() - 1);
      metaData.assessmentRules.push_back(ar2);
      metaData.versionMetaData[2].assessmentRulesI.push_back((int16_t)metaData.assessmentRules.size() - 1);
      metaData.assessmentRules.push_back(ar3);
      metaData.versionMetaData[0].assessmentRulesI.push_back((int16_t)metaData.assessmentRules.size() - 1);
      metaData.versionMetaData[1].assessmentRulesI.push_back((int16_t)metaData.assessmentRules.size() - 1);
      metaData.versionMetaData[2].assessmentRulesI.push_back((int16_t)metaData.assessmentRules.size() - 1);
   };
};


TEST_CASE("AssessRulesTest", "[test]")
{
   // Setup metadata then initialize aggregate class with this metadata
   // AggComputeFieldMetaData is defined above
   ChildMetaData separateMetaData;
   AggAssess::initMetaData(&separateMetaData.metaData);

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
