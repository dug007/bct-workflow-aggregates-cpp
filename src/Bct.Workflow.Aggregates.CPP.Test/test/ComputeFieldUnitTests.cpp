#include "PlateletConfigAggregate.h"
#include "PlateletTemplateAggregate.h"
#include "AggComputeField.h"
#include "TypeEnum.h"
#include "BaseAggregate.h"
#include "catch.hpp"

using namespace Bct::Workflow::Aggregates;
using namespace Bct::Workflow::Implementation;

//********** UNIT TESTS **************************************

TEST_CASE("PlateletTemplateAggregate100", "[test]")
{
   // Design doc example version 1.0.0 ----------------------------

   //Create plateletAggregate with version 1.0.0
   PlateletTemplateAggregate Platelet_100("1.0.0");
   //Test for field that is Unavailable
   CHECK(Platelet_100.minYield.state() == FieldStateEnum::Unavailable);
   CHECK(Platelet_100.maxYield.state() == FieldStateEnum::Unavailable);
   CHECK_THROWS_AS(Platelet_100.minYield.value(), NotAbleToGet); 
   CHECK_THROWS_AS(Platelet_100.maxYield.value(), NotAbleToGet);
   CHECK_THROWS_AS(Platelet_100.minYield.value(5), NotAbleToSet);

   try //Try to get an unavailable field value
   {
      Platelet_100.maxYield.value();
   }
   catch (NotAbleToGet & exc)
   {
      std::string message = "Bct::Workflow::Aggregates::NotAbleToGet: aggregate=class Bct::Workflow::Implementation::PlateletTemplateAggregate fieldName=maxYield fieldState=Unavailable";
      CHECK(exc.what() == message);
   }

   //Check initial state of fields used in calculation
   CHECK(Platelet_100.volumeMl.state() == FieldStateEnum::NotSet);
   CHECK(Platelet_100.cellsPerMl.state() == FieldStateEnum::NotSet);
   CHECK(Platelet_100.yield.state() == FieldStateEnum::NotSet);

   //Test compute function for 1.0.0
   //Field: Yield
   //   Condition : true
   //   Expression :  VolumeMl * CellsPerMl
   Platelet_100.yield = 0.0;
   Platelet_100.volumeMl = 500.0;
   Platelet_100.cellsPerMl = 5.0e6;
   double expectedYield100 = Platelet_100.volumeMl.value() * Platelet_100.cellsPerMl.value();
   CHECK(Platelet_100.volumeMl.state() == FieldStateEnum::Set) ;
   CHECK(Platelet_100.cellsPerMl.state() == FieldStateEnum::Set);
   Platelet_100.updateCalculatedFields();
   CHECK(Platelet_100.yield.value() == expectedYield100);
   CHECK(Platelet_100.yield.state() == FieldStateEnum::Computed);
}

TEST_CASE("PlateletTemplateAggregate110", "[test]")
{
   //Create new plateletAggregate with version 1.1.0
   PlateletTemplateAggregate Platelet_110("1.1.0");

   //Check new fields that were added to vers[1] that were unavailable in vers[0]
   CHECK(Platelet_110.minYield.state() == FieldStateEnum::Constant);
   CHECK(Platelet_110.maxYield.state() == FieldStateEnum::Constant);

   //Check initial state for values used in calculations
   CHECK(Platelet_110.volumeMl.state() == FieldStateEnum::NotSet);
   CHECK(Platelet_110.cellsPerMl.state() == FieldStateEnum::NotSet);
   CHECK(Platelet_110.yield.state() == FieldStateEnum::NotSet);

   //Test the 3 compute rules given for version 1.1.0 which includes condition expression
   //ComputeRule 1. Compute yield using volumeMl and cellsPerMl
   //Field: Yield
   //   Condition : $EnteredLater(VolumeMl, Yield) && $EnteredLater(CellsPerMl, Yield)
   //   Expression :  VolumeMl * CellsPerMl
   Platelet_110.yield = 0.0;
   Platelet_110.volumeMl = 500.0;
   Platelet_110.cellsPerMl = 5.0e6;
   double expectedYield110 = Platelet_110.volumeMl.value() * Platelet_110.cellsPerMl.value();
   CHECK(Platelet_110.volumeMl.state() == FieldStateEnum::Set);
   CHECK(Platelet_110.cellsPerMl.state() == FieldStateEnum::Set);
   Platelet_110.updateCalculatedFields();
   CHECK(Platelet_110.yield.value() == expectedYield110);
   CHECK(Platelet_110.yield.state() == FieldStateEnum::Computed); //check to make sure calculated field updates to computed

   // ComputeRule 2. Compute volumeMl using yield and cellsPerMl
   //Field: VolumeMl
   //   Condition : $EnteredLater(CellsPerMl, VolumeMl) && $EnteredLater(Yield, VolumeMl)
   //   Expression : Yield / CellsPerMl
   Platelet_110.volumeMl = 0.0;
   Platelet_110.yield = 1.0e8;
   Platelet_110.cellsPerMl = 0.5e6;
   double expectedVolumeMl = Platelet_110.yield.value() / Platelet_110.cellsPerMl.value();
   CHECK(Platelet_110.yield.state() == FieldStateEnum::Set);
   CHECK(Platelet_110.cellsPerMl.state() == FieldStateEnum::Set);
   Platelet_110.updateCalculatedFields();
   CHECK(Platelet_110.volumeMl.value() == expectedVolumeMl);
   CHECK(Platelet_110.volumeMl.state() == FieldStateEnum::Computed); //check to make sure calculated field updates to computed

   //ComputeRule 3. Compute cellsPerMl using yield and volumeMl
   //Field: CellsPerMl
   //   Condition : $EnteredLater(VolumeMl, CellsPerMl) && $EnteredLater(Yield, CellsPerMl)
   //   Expression :   Yield / VolumeMl
   Platelet_110.cellsPerMl = 0.0;
   Platelet_110.yield = 1.0e9;
   Platelet_110.volumeMl = 250.0;
   double expectedCellsPerMl = Platelet_110.yield.value() / Platelet_110.volumeMl.value();
   CHECK(Platelet_110.yield.state() == FieldStateEnum::Set);
   CHECK(Platelet_110.volumeMl.state() == FieldStateEnum::Set);
   Platelet_110.updateCalculatedFields();
   CHECK(Platelet_110.cellsPerMl.value() == expectedCellsPerMl);
   CHECK(Platelet_110.cellsPerMl.state() == FieldStateEnum::Computed); //check to make sure calculated field updates to computed
}


// this class is the metadata for the ComputeRuleVersion unit test
class AggComputeFieldMetaData
{
public:

   AggregateMetaData metaData;

   AggComputeFieldMetaData()
   {
      std::string vers[5] =
      {
         "1.0.0",
         "1.1.0",
         "1.2.0",
         "1.3.0",
         "1.4.0"
      };

      for (uint16_t i = 0; i < 5; i++)
      {
         metaData.versionInfo.push_back(VersionInfo(vers[i]));
         VersionMetaData vm;
         metaData.versionMetaData.push_back(vm);
      }

      metaData.addField(0, "field1", Bct::Workflow::TypeEnum::Int32Type);
      metaData.addField(1, "field2", Bct::Workflow::TypeEnum::Int32Type);
      metaData.addField(2, "stringField", Bct::Workflow::TypeEnum::StringType);

      metaData.addFieldMetaToAllVersions(0, FieldStateEnum::Computed, "");
      metaData.addFieldMetaToAllVersions(1, FieldStateEnum::Default, "21");

      metaData.addComputeRule("field1v0",   0,   "field2 21 ==",   "field2 1 +") .toVersion(0);
      metaData.addComputeRule("field1v1",   0,   "field2 21 ==",   "field2 2 +") .toVersion(1);
      metaData.addComputeRule("field1v2",   0,   "field2 21 ==",   "field2 3 +") .toVersion(2);
      metaData.addComputeRule("field1v3_4", 0,   "field2 21 ==",   "field2 4 +")
              .toVersion(3) .toVersion(4);

      metaData.addFieldMetaToAllVersions(2, FieldStateEnum::Default, "");
   };
};


TEST_CASE("ComputeRuleVersion", "[test]")
{
   // Setup metadata then initialize aggregate class with this metadata
   // AggComputeFieldMetaData is defined above
   AggComputeFieldMetaData separateMetaData;
   AggComputeField::bindMetaData(&separateMetaData.metaData);

   // version 0 computes 22
   // version 1 computes 23
   // version 2 computes 24
   // version 3 and 4 computes 25

   AggComputeField a0("1.0.0");
   AggComputeField a1("1.1.0");
   AggComputeField a2("1.2.0");
   AggComputeField a3("1.3.0");
   AggComputeField a4("1.4.0");

   a0.updateCalculatedFields();
   a1.updateCalculatedFields();
   a2.updateCalculatedFields();
   a3.updateCalculatedFields();
   a4.updateCalculatedFields();

   CHECK(a0.field1.value() == 22);
   CHECK(a1.field1.value() == 23);
   CHECK(a2.field1.value() == 24);
   CHECK(a3.field1.value() == 25);
   CHECK(a4.field1.value() == 25);
}
