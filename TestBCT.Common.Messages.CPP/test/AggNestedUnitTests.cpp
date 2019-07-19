#include "AggNested.h"
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
      std::string vers[3] =
      {
         "1.0.0",
         "1.1.0",
         "1.2.0",
      };

      for (uint16_t i = 0; i < std::size(vers); i++)
      {
         metaData.versionInfo.push_back(VersionInfo(vers[i]));
         VersionMetaData vm;
         metaData.versionMetaData.push_back(vm);
      }

      FieldMeta field1Meta("field1", FieldStateEnum::Default, "1", -1);  // -1 means all versions
      FieldMeta field2Meta("field2", FieldStateEnum::Default, "10", -1);
      FieldMeta field300Meta("field3", FieldStateEnum::Constant, 0, 0);  // v0 parent, v0 child
      FieldMeta field311Meta("field3", FieldStateEnum::Constant, 1, 1);  // v1 parent, v1 child
      FieldMeta field321Meta("field3", FieldStateEnum::Constant, 2, 1);  // v2 parent, v1 child

      int16_t k, cnt;

      metaData.fieldMetaData.push_back(field1Meta);
      k = 0; cnt = (int16_t)metaData.fieldMetaData.size() - 1;
      metaData.versionMetaData[k++].fieldMetaDataI.push_back(cnt); // since this is for all versions no need for more vectors

      metaData.fieldMetaData.push_back(field2Meta);
      k = 0; cnt = (int16_t)metaData.fieldMetaData.size() - 1;
      metaData.versionMetaData[k++].fieldMetaDataI.push_back(cnt); // since this is for all versions no need for more vectors

      k = 0;

      metaData.fieldMetaData.push_back(field300Meta);
      cnt = (int16_t)metaData.fieldMetaData.size() - 1;
      metaData.versionMetaData[k++].fieldMetaDataI.push_back(cnt);

      metaData.fieldMetaData.push_back(field311Meta);
      cnt = (int16_t)metaData.fieldMetaData.size() - 1;
      metaData.versionMetaData[k++].fieldMetaDataI.push_back(cnt);

      metaData.fieldMetaData.push_back(field321Meta);
      cnt = (int16_t)metaData.fieldMetaData.size() - 1;
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


TEST_CASE("AggNestedUnitTests", "[test]")
{
   // Setup metadata then initialize aggregate class with this metadata
   // AggComputeFieldMetaData is defined above
   AggAssessmentMetaData separateMetaData;
   AggNested::initMetaData(&separateMetaData.metaData);

   AggNested a0("1.0.0");
   AggNested a1("1.1.0");
   AggNested a2("1.2.0");

   // prove assessment all work in their versions
   AssessmentResult r0 = a0.Assess();
   AssessmentResult r1 = a1.Assess();

   CHECK(r0.isSuccess() == false); // field1 field2 ==
   CHECK(r1.isSuccess() == true);  // field1 field2 !=

   CHECK(a0.field3.getVersion() == "1.0.0");
   CHECK(a1.field3.getVersion() == "1.1.0");
   CHECK(a2.field3.getVersion() == "1.1.0");
}
