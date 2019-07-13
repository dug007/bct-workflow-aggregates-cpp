#include "PlateletConfigAggregate.h"
#include "PlateletTemplateAggregate.h"

#include "BaseAggregate.h"
#include "catch.hpp"

using namespace Bct::Workflow::Aggregates;

//********** UNIT TESTS **************************************


TEST_CASE("PlateletTemplateAggregate100", "[test]")
{
   // Design doc example version 1.0.0 ----------------------------

   //Create plateletAggregate with version 1.0.0
   PlateletTemplateAggregate Platelet_100("1.0.0");

   //Test for field that is Unavailable
   CHECK(Platelet_100.minYield.State() == FieldStateEnum::FieldState::Unavailable);
   CHECK(Platelet_100.maxYield.State() == FieldStateEnum::FieldState::Unavailable);
   CHECK_THROWS_AS(Platelet_100.minYield.Value(), char*);
   CHECK_THROWS_AS(Platelet_100.maxYield.Value(), char*);

   //Check initial state of fields used in calculation
   CHECK(Platelet_100.volumeMl.State() == FieldStateEnum::FieldState::NotSet);
   CHECK(Platelet_100.cellsPerMl.State() == FieldStateEnum::FieldState::NotSet);
   CHECK(Platelet_100.yield.State() == FieldStateEnum::FieldState::NotSet);

   //Test compute function for 1.0.0
   //Field: Yield
   //   Condition : true
   //   Expression :  VolumeMl * CellsPerMl
   Platelet_100.yield = 0.0;
   Platelet_100.volumeMl = 500.0;
   Platelet_100.cellsPerMl = 5.0e6;
   double expectedYield100 = Platelet_100.volumeMl.Value() * Platelet_100.cellsPerMl.Value();
   CHECK(Platelet_100.volumeMl.State() == FieldStateEnum::FieldState::Set) ;
   CHECK(Platelet_100.cellsPerMl.State() == FieldStateEnum::FieldState::Set);
   Platelet_100.UpdateCalculatedFields();
   CHECK(Platelet_100.yield.Value() == expectedYield100);
   CHECK(Platelet_100.yield.State() == FieldStateEnum::FieldState::Computed);
}

TEST_CASE("PlateletTemplateAggregate110", "[test]")
{
   //Create new plateletAggregate with version 1.1.0
   PlateletTemplateAggregate Platelet_110("1.1.0");

   //Check new fields that were added to vers[1] that were unavailable in vers[0]
   CHECK(Platelet_110.minYield.State() == FieldStateEnum::FieldState::Constant);
   CHECK(Platelet_110.maxYield.State() == FieldStateEnum::FieldState::Constant);

   //Check initial state for values used in calculations
   CHECK(Platelet_110.volumeMl.State() == FieldStateEnum::FieldState::NotSet);
   CHECK(Platelet_110.cellsPerMl.State() == FieldStateEnum::FieldState::NotSet);
   CHECK(Platelet_110.yield.State() == FieldStateEnum::FieldState::NotSet);

   //Test the 3 compute rules given for version 1.1.0 which includes condition expression
   //ComputeRule 1. Compute yield using volumeMl and cellsPerMl
   //Field: Yield
   //   Condition : $EnteredLater(VolumeMl, Yield) && $EnteredLater(CellsPerMl, Yield)
   //   Expression :  VolumeMl * CellsPerMl
   Platelet_110.yield = 0.0;
   Platelet_110.volumeMl = 500.0;
   Platelet_110.cellsPerMl = 5.0e6;
   double expectedYield110 = Platelet_110.volumeMl.Value() * Platelet_110.cellsPerMl.Value();
   CHECK(Platelet_110.volumeMl.State() == FieldStateEnum::FieldState::Set);
   CHECK(Platelet_110.cellsPerMl.State() == FieldStateEnum::FieldState::Set);
   Platelet_110.UpdateCalculatedFields();
   CHECK(Platelet_110.yield.Value() == expectedYield110);
   CHECK(Platelet_110.yield.State() == FieldStateEnum::FieldState::Computed); //check to make sure calculated field updates to computed

   // ComputeRule 2. Compute volumeMl using yield and cellsPerMl
   //Field: VolumeMl
   //   Condition : $EnteredLater(CellsPerMl, VolumeMl) && $EnteredLater(Yield, VolumeMl)
   //   Expression : Yield / CellsPerMl
   Platelet_110.volumeMl = 0.0;
   Platelet_110.yield = 1.0e8;
   Platelet_110.cellsPerMl = 0.5e6;
   double expectedVolumeMl = Platelet_110.yield.Value() / Platelet_110.cellsPerMl.Value();
   CHECK(Platelet_110.yield.State() == FieldStateEnum::FieldState::Set);
   CHECK(Platelet_110.cellsPerMl.State() == FieldStateEnum::FieldState::Set);
   Platelet_110.UpdateCalculatedFields();
   CHECK(Platelet_110.volumeMl.Value() == expectedVolumeMl);
   CHECK(Platelet_110.volumeMl.State() == FieldStateEnum::FieldState::Computed); //check to make sure calculated field updates to computed

   //ComputeRule 3. Compute cellsPerMl using yield and volumeMl
   //Field: CellsPerMl
   //   Condition : $EnteredLater(VolumeMl, CellsPerMl) && $EnteredLater(Yield, CellsPerMl)
   //   Expression :   Yield / VolumeMl
   Platelet_110.cellsPerMl = 0.0;
   Platelet_110.yield = 1.0e9;
   Platelet_110.volumeMl = 250.0;
   double expectedCellsPerMl = Platelet_110.yield.Value() / Platelet_110.volumeMl.Value();
   CHECK(Platelet_110.yield.State() == FieldStateEnum::FieldState::Set);
   CHECK(Platelet_110.volumeMl.State() == FieldStateEnum::FieldState::Set);
   Platelet_110.UpdateCalculatedFields();
   CHECK(Platelet_110.cellsPerMl.Value() == expectedCellsPerMl);
   CHECK(Platelet_110.cellsPerMl.State() == FieldStateEnum::FieldState::Computed); //check to make sure calculated field updates to computed
}
