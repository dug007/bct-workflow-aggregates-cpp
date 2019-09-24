#include "AggNested.h"
#include "BaseAggregate.h"
#include "catch.hpp"

using namespace Bct::Workflow::Aggregates;
using namespace Bct::Workflow::Implementation;

class AggNestedMetaData
{
public:

   AggregateMetaData metaData;

   AggNestedMetaData()
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

      metaData.addField(0, "intField1", Bct::Workflow::TypeEnum::Int32Type);
      metaData.addField(1, "intField2", Bct::Workflow::TypeEnum::Int32Type);
      metaData.addAggField(2, "aggField");
      metaData.addAggField(3, "aggFieldV2");
      metaData.addField(4, "enumField", Bct::Workflow::TypeEnum::Int32Type);
      metaData.addField(5, "stringField", Bct::Workflow::TypeEnum::StringType);


      FieldMeta intField1Meta(0, FieldStateEnum::Default, "1", BaseAggregate::InAllVersions);  // all versions have this field
      FieldMeta intField2Meta(1, FieldStateEnum::Default, "10", BaseAggregate::InAllVersions);
      FieldMeta aggField00Meta(2, FieldStateEnum::Constant, 0, 0);  // v0 parent, v0 child
      FieldMeta aggField11Meta(2, FieldStateEnum::Constant, 1, 1);  // v1 parent, v1 child
      FieldMeta aggField21Meta(2, FieldStateEnum::Constant, 2, 1);  // v2 parent, v1 child
      FieldMeta aggFieldV2Meta(3, FieldStateEnum::Constant, BaseAggregate::InAllVersions, 2);  // all parents have v2 child
      FieldMeta enumFieldMeta(4, FieldStateEnum::Default, "2", BaseAggregate::InAllVersions); // all versions have this field, bool type is 2

      int16_t k, cnt;

      metaData.fieldMetaData.push_back(intField1Meta);
      k = 0; cnt = (int16_t)metaData.fieldMetaData.size() - 1;
      metaData.versionMetaData[k++].fieldMetaDataI.push_back(cnt); // since this is for all versions no need for more vectors

      metaData.fieldMetaData.push_back(intField2Meta);
      k = 0; cnt = (int16_t)metaData.fieldMetaData.size() - 1;
      metaData.versionMetaData[k++].fieldMetaDataI.push_back(cnt); // since this is for all versions no need for more vectors

      k = 0;

      metaData.fieldMetaData.push_back(aggField00Meta);
      cnt = (int16_t)metaData.fieldMetaData.size() - 1;
      metaData.versionMetaData[k++].fieldMetaDataI.push_back(cnt);

      metaData.fieldMetaData.push_back(aggField11Meta);
      cnt = (int16_t)metaData.fieldMetaData.size() - 1;
      metaData.versionMetaData[k++].fieldMetaDataI.push_back(cnt);

      metaData.fieldMetaData.push_back(aggField21Meta);
      cnt = (int16_t)metaData.fieldMetaData.size() - 1;
      metaData.versionMetaData[k++].fieldMetaDataI.push_back(cnt);

      metaData.fieldMetaData.push_back(aggFieldV2Meta);
      k = 0; cnt = (int16_t)metaData.fieldMetaData.size() - 1;
      metaData.versionMetaData[k].fieldMetaDataI.push_back(cnt); // since this is for all versions no need for more vectors

      metaData.fieldMetaData.push_back(enumFieldMeta);
      k = 0; cnt = (int16_t)metaData.fieldMetaData.size() - 1;
      metaData.versionMetaData[k].fieldMetaDataI.push_back(cnt); // since this is for all versions no need for more vectors

      metaData.addFieldMetaToAllVersions(5, FieldStateEnum::Default, "test");

      AssessmentRule ar0("assessv0", "assessv0", "intField2 10 ==", "intField1 intField2 ==");      // fails
      AssessmentRule ar1("assessv1", "assessv1", "intField2 10 ==", "intField1 intField2 !=");      // passes
      AssessmentRule ar2("assessv2", "assessv2", "intField2 10 ==", "intField1 intField2 + 11 =="); // passes
      AssessmentRule ar3("assessv012", "assessv012", "intField2 10 ==", "intField1 intField2 + 1 - 10 ==");

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

      metaData.addField(0, "field1", Bct::Workflow::TypeEnum::Int32Type);
      metaData.addField(1, "field2", Bct::Workflow::TypeEnum::Int32Type);
      metaData.addField(2, "stringField", Bct::Workflow::TypeEnum::StringType);

      // One set of field metadata for all version
      FieldMeta intField1Meta(0, FieldStateEnum::Default, "1", BaseAggregate::InAllVersions); // in all
      FieldMeta intField2Meta(1, FieldStateEnum::Default, "10", BaseAggregate::InAllVersions);

      int16_t k, cnt;

      metaData.fieldMetaData.push_back(intField1Meta);
      k = 0; cnt = (int16_t)metaData.fieldMetaData.size() - 1;
      metaData.versionMetaData[k++].fieldMetaDataI.push_back(cnt); // since this is for all versions no need for more vectors

      metaData.fieldMetaData.push_back(intField2Meta);
      k = 0; cnt = (int16_t)metaData.fieldMetaData.size() - 1;
      metaData.versionMetaData[k++].fieldMetaDataI.push_back(cnt);

      metaData.addFieldMetaToAllVersions(2, FieldStateEnum::Default, "test");

      AssessmentRule ar0("assessv0", "assessv0", "field2 10 ==", "field1 field2 ==");      // fails
      AssessmentRule ar1("assessv1", "assessv1", "field2 10 ==", "field1 field2 !=");      // passes
      AssessmentRule ar2("assessv2", "assessv2", "field2 10 ==", "field1 field2 + 11 =="); // passes
      AssessmentRule ar3("assessv012", "assessv012", "field2 10 ==", "field1 field2 + 1 - 10 ==");

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
   AggNestedMetaData parentMetaData;
   ChildMetaData childMetaData;
   AggNested::bindMetaData(&parentMetaData.metaData, &childMetaData.metaData);

   AggNested a0("1.0.0");
   AggNested a1("1.1.0");
   AggNested a2("1.2.0");

   // prove assessment all work in their versions
   AssessmentResult r0a = a0.Assess();
   AssessmentResult r1a = a1.Assess();

   CHECK(r0a.isSuccess() == false); // intField1 intField2 ==
   CHECK(r1a.isSuccess() == true);  // intField1 intField2 !=

   // prove versions as specified
   CHECK(a0.aggField.getVersion() == "1.0.0");
   CHECK(a1.aggField.getVersion() == "1.1.0");
   CHECK(a2.aggField.getVersion() == "1.1.0");

   // prove in all versions
   CHECK(a0.aggFieldV2.getVersion() == "1.2.0");
   CHECK(a1.aggFieldV2.getVersion() == "1.2.0");
   CHECK(a2.aggFieldV2.getVersion() == "1.2.0");

   // prove nested aggField behaves same way
   AssessmentResult r0b = a0.aggField.Assess();
   AssessmentResult r1b = a1.aggField.Assess();

   CHECK(r0b.isSuccess() == false); // intField1 intField2 ==
   CHECK(r1b.isSuccess() == true);  // intField1 intField2 !=

   // enum tests
   CHECK(a0.enumField.Value() == Bct::Workflow::TypeEnum::BoolType);

   // copy constructor tests
   AggNested aOrig;
   aOrig.aggField.field1 = 111;
   AggNested aCopy = aOrig;
   CHECK(aCopy.aggField.field1 == 111);
   std::string actualStr = aCopy.aggField.stringField;
   CHECK((std::string)aCopy.aggField.stringField == "test");
   aOrig.aggField.field1 = 222;
   CHECK(aCopy.aggField.field1 == 111);
   aCopy.aggField.field1 = 333;
   CHECK(aOrig.aggField.field1 == 222);

   // make sure field assignment semantics is working ok - field set counter IS copied
   aCopy.aggField.field1 = 444;
   aCopy.aggField.field1 = 444;
   aCopy.aggField.field1 = 444;
   aOrig.aggField.field1 = aCopy.aggField.field1;
   aOrig.aggField.stringField = aCopy.aggField.stringField;
   CHECK(aOrig.aggField.field1.FieldSetCounter() == aCopy.aggField.field1.FieldSetCounter());
   CHECK(aOrig.aggField.field1 == 444);

   AggNested aAssign;

   aCopy.intField1 = 777;
   aCopy.aggField.field1 = 888;
   aCopy.aggField.stringField = "test999";
   aAssign = aCopy;
   CHECK(aAssign.intField1 == 777);
   CHECK(aAssign.aggField.field1 == 888);
   CHECK(aAssign.aggField.stringField.Value() == "test999");
   CHECK(aAssign.aggField.stringField.FieldSetCounter() != aCopy.aggField.stringField.FieldSetCounter());



}
