#include "BaseAggregate.h"
#include "FieldInt32.h"
#include "FieldInt32Ro.h"
#include "FieldDouble.h"
#include "FieldDoubleRo.h"
#include "catch.hpp"


//************ CODE GENERATION STARTS HERE ****************

using namespace Bct::Workflow::Aggregates;

class PlateletTemplateAggregrate : public BaseAggregate
{
private:
   void initMetaData()
   {
      VersionMetaData &aggMeta = AggregateMetaData();
      AbstractAggregate *agg = this;
      std::string vers[2] =
      {
         "1.0.0",
         "1.1.0"
      };

      FieldStateEnum::FieldState _volumeMlStates[2] =
      {
         FieldStateEnum::NotSet,
         FieldStateEnum::NotSet
      };

      std::string _volumeMlDefaults[2] =
      {
         "0.0",
         "0.0"
      };

      FieldStateEnum::FieldState _cellsPerMlStates[2] =
      {
         FieldStateEnum::NotSet,
         FieldStateEnum::NotSet
      };

      std::string _cellsPerMlDefaults[2] =
      {
         "0.0",
         "0.0"
      };

      FieldStateEnum::FieldState _yieldStates[2] =
      {
         FieldStateEnum::NotSet,
         FieldStateEnum::NotSet
      };

      std::string _yieldDefaults[2] =
      {
         "0.0",
         "0.0"
      };

      FieldStateEnum::FieldState _minVolumeMlStates[2] =
      {
         FieldStateEnum::Constant,
         FieldStateEnum::Constant
      };

      std::string _minVolumeMlDefaults[2] =
      {
         "100.0",
         "100.0"
      };

      FieldStateEnum::FieldState _maxVolumeMlStates[2] =
      {
         FieldStateEnum::Constant,
         FieldStateEnum::Constant
      };

      std::string _maxVolumeMlDefaults[2] =
      {
         "500.0",
         "500.0"
      };

      FieldStateEnum::FieldState _minCellsPerMlStates[2] =
      {
         FieldStateEnum::Constant,
         FieldStateEnum::Constant
      };

      std::string _minCellsPerMlDefaults[2] =
      {
         "0.5e6",
         "0.5e6"
      };

      FieldStateEnum::FieldState _maxCellsPerMlStates[2] =
      {
         FieldStateEnum::Constant,
         FieldStateEnum::Constant
      };

      std::string _maxCellsPerMlDefaults[2] =
      {
         "5.0e6",
         "5.0e6"
      };

      FieldStateEnum::FieldState _minYieldStates[2] =
      {
         FieldStateEnum::Unavailable,
         FieldStateEnum::Constant
      };

      std::string _minYieldDefaults[2] =
      {
         "0.0",
         "1.0e8"
      };

      FieldStateEnum::FieldState _maxYieldStates[2] =
      {
         FieldStateEnum::Unavailable,
         FieldStateEnum::Constant
      };

      std::string _maxYieldDefaults[2] =
      {
         "0.0",
         "2.0e9"
      };

      for (int16_t i = 0; i < 2; i++)
      {
         aggMeta.versionInfo.push_back(VersionInfo(vers[i]));

         FieldMeta volumeMl_("volumeMl", _volumeMlStates[i], _volumeMlDefaults[i], i);
         FieldMeta cellsPerMl_("cellsPerMl", _cellsPerMlStates[i], _cellsPerMlDefaults[i], i);
         FieldMeta yield_("yield", _yieldStates[i], _yieldDefaults[i], i);
         FieldMeta minVolumeMl_("minVolumeMl", _minVolumeMlStates[i], _minVolumeMlDefaults[i], i);
         FieldMeta maxVolumeMl_("maxVolumeMl", _maxVolumeMlStates[i], _maxVolumeMlDefaults[i], i);
         FieldMeta minCellsPerMl_("minCellsPerMl", _minCellsPerMlStates[i], _minCellsPerMlDefaults[i], i);
         FieldMeta maxCellsPerMl_("maxCellsPerMl", _maxCellsPerMlStates[i], _maxCellsPerMlDefaults[i], i);
         FieldMeta minYield_("minYield", _minYieldStates[i], _minYieldDefaults[i], i);
         FieldMeta maxYield_("maxYield", _maxYieldStates[i], _maxYieldDefaults[i], i);

         aggMeta.fieldMetaData.push_back(volumeMl_);
         aggMeta.fieldMetaData.push_back(cellsPerMl_);
         aggMeta.fieldMetaData.push_back(yield_);
         aggMeta.fieldMetaData.push_back(minVolumeMl_);
         aggMeta.fieldMetaData.push_back(maxVolumeMl_);
         aggMeta.fieldMetaData.push_back(minCellsPerMl_);
         aggMeta.fieldMetaData.push_back(maxCellsPerMl_);
         aggMeta.fieldMetaData.push_back(minYield_);
         aggMeta.fieldMetaData.push_back(maxYield_);
      }
      // Simple computation rules
      {
         ComputeRule cr1("yieldId1", "yield", "1 1 ==", "cellsPerMl volumeMl *"); // TODO make $True - User Story 126600
         aggMeta.computeRules.push_back(cr1);
      }
      {
         ComputeRule cr1("yieldId2", "yield", "volumeMl yield $EnteredLater", "cellsPerMl volumeMl *");
         ComputeRule cr3("cellsPerMlId1", "cellsPerMl", "volumeMl cellsPerMl $EnteredLater yield cellsPerMl $EnteredLater &&", "yield volumeMl /");
         ComputeRule cr2("volumeMlId1", "volumeMl", "cellsPerMl volumeMl $EnteredLater yield volumeMl $EnteredLater &&", "yield cellsPerMl /");
         aggMeta.computeRules.push_back(cr1);
         aggMeta.computeRules.push_back(cr2);
         aggMeta.computeRules.push_back(cr3);
      }



      SyncCurrentVersion(); // determine ver for aggregate based on state of metadata

      volumeMl = FieldDouble("volumeMl", Ver(), aggMeta, agg);
      cellsPerMl = FieldDouble("cellsPerMl", Ver(), aggMeta, agg);
      yield = FieldDouble("yield", Ver(), aggMeta, agg);
      minVolumeMl = FieldDouble("minVolumeMl", Ver(), aggMeta, agg);
      maxVolumeMl = FieldDouble("maxVolumeMl", Ver(), aggMeta, agg);
      minCellsPerMl = FieldDouble("minCellsPerMl", Ver(), aggMeta, agg);
      maxCellsPerMl = FieldDouble("maxCellsPerMl", Ver(), aggMeta, agg);
      minYield = FieldDouble("minYield", Ver(), aggMeta, agg);
      maxYield = FieldDouble("maxYield", Ver(), aggMeta, agg);

      FieldList().push_back(&volumeMl);
      FieldList().push_back(&cellsPerMl);
      FieldList().push_back(&yield);
      FieldList().push_back(&minVolumeMl);
      FieldList().push_back(&maxVolumeMl);
      FieldList().push_back(&minCellsPerMl);
      FieldList().push_back(&maxCellsPerMl);
      FieldList().push_back(&minYield);
      FieldList().push_back(&maxYield);

   }

public:
   FieldDouble volumeMl;
   FieldDouble cellsPerMl;
   FieldDouble yield;
   FieldDouble minVolumeMl;
   FieldDouble maxVolumeMl;
   FieldDouble minCellsPerMl;
   FieldDouble maxCellsPerMl;
   FieldDouble minYield;
   FieldDouble maxYield;


   PlateletTemplateAggregrate(const std::string version) : BaseAggregate(version)
   {
      initMetaData();
   }

   virtual ~PlateletTemplateAggregrate() {};
};

class PlateletConfigAggregate : public BaseAggregate
{
private:
   void initMetaData()
   {
      VersionMetaData &aggMeta = AggregateMetaData();
      AbstractAggregate *agg = this;

      std::string vers[2] =
      {
         "1.0.0",
         "1.1.0"
      };

      FieldStateEnum::FieldState _postCellsPerMlStates[2] =
      {
         FieldStateEnum::NotSet,
         FieldStateEnum::Unavailable
      };

      std::string _postCellsPerMlDefaults[2] =
      {
         "100.0",
         "0.0"
      };

      FieldStateEnum::FieldState _minTemplateCountStates[2] =
      {
         FieldStateEnum::Constant,
         FieldStateEnum::Unavailable
      };

      std::string _minTemplateCountDefaults[2] =
      {
         "1",
         "0"
      };

      FieldStateEnum::FieldState _maxTemplateCountStates[2] =
      {
         FieldStateEnum::Constant,
         FieldStateEnum::Unavailable
      };

      std::string _maxTemplateCountDefaults[2] =
      {
         "10",
         "0"
      };

      FieldStateEnum::FieldState _minPostCellsPerMlStates[2] =
      {
         FieldStateEnum::Constant,
         FieldStateEnum::Constant
      };

      std::string _minPostCellsPerMlDefaults[2] =
      {
         "80.0",
         "80.0"
      };
      FieldStateEnum::FieldState _maxPostCellsPerMlStates[2] =
      {
         FieldStateEnum::Constant,
         FieldStateEnum::Constant
      };

      std::string _maxPostCellsPerMlDefaults[2] =
      {
         "200.0",
         "200.0"
      };

      FieldStateEnum::FieldState _malePostCellsPerMlStates[2] =
      {
         FieldStateEnum::Unavailable,
         FieldStateEnum::NotSet
      };

      std::string _malePostCellsPerMlDefaults[2] =
      {
         "0.0",
         "100.0"
      };

      FieldStateEnum::FieldState _femalePostCellsPerMlStates[2] =
      {
         FieldStateEnum::Unavailable,
         FieldStateEnum::NotSet
      };

      std::string _femalePostCellsPerMlDefaults[2] =
      {
         "0.0",
         "100.0"
      };


      for (int16_t i = 0; i < 2; i++)
      {
         aggMeta.versionInfo.push_back(VersionInfo(vers[i]));

         FieldMeta postCellsPerMl_("postCellsPerMl", _postCellsPerMlStates[i], _postCellsPerMlDefaults[i], i);
         FieldMeta minTemplateCount_("minTemplateCount", _minTemplateCountStates[i], _minTemplateCountDefaults[i], i);
         FieldMeta maxTemplateCount_("maxTemplateCount", _maxTemplateCountStates[i], _maxTemplateCountDefaults[i], i);
         FieldMeta minPostCellsPerMl_("minPostCellsPerMl", _minPostCellsPerMlStates[i], _minPostCellsPerMlDefaults[i], i);
         FieldMeta maxPostCellsPerMl_("maxPostCellsPerMl", _maxPostCellsPerMlStates[i], _maxPostCellsPerMlDefaults[i], i);
         FieldMeta malePostCellsPerMl_("malePostCellsPerMl", _malePostCellsPerMlStates[i], _malePostCellsPerMlDefaults[i], i);
         FieldMeta femalePostCellsPerMl_("femalePostCellsPerMl", _femalePostCellsPerMlStates[i], _femalePostCellsPerMlDefaults[i], i);

         aggMeta.fieldMetaData.push_back(postCellsPerMl_);
         aggMeta.fieldMetaData.push_back(minTemplateCount_);
         aggMeta.fieldMetaData.push_back(maxTemplateCount_);
         aggMeta.fieldMetaData.push_back(minPostCellsPerMl_);
         aggMeta.fieldMetaData.push_back(maxPostCellsPerMl_);
         aggMeta.fieldMetaData.push_back(malePostCellsPerMl_);
         aggMeta.fieldMetaData.push_back(femalePostCellsPerMl_);
      }

      SyncCurrentVersion(); // determine ver for aggregate based on state of metadata

      postCellsPerMl = FieldDouble("postCellsPerMl", Ver(), aggMeta, agg);
      minTemplateCount = FieldInt32("minTemplateCount", Ver(), aggMeta, agg);
      maxTemplateCount = FieldInt32("maxTemplateCount", Ver(), aggMeta, agg);
      minPostCellsPerMl = FieldDouble("minPostCellsPerMl", Ver(), aggMeta, agg);
      maxPostCellsPerMl = FieldDouble("maxPostCellsPerMl", Ver(), aggMeta, agg);
      malePostCellsPerMl = FieldDouble("malePostCellsPerMl", Ver(), aggMeta, agg);
      femalePostCellsPerMl = FieldDouble("femalePostCellsPerMl", Ver(), aggMeta, agg);

      FieldList().push_back(&postCellsPerMl);
      FieldList().push_back(&minTemplateCount);
      FieldList().push_back(&maxTemplateCount);
      FieldList().push_back(&minPostCellsPerMl);
      FieldList().push_back(&maxPostCellsPerMl);
      FieldList().push_back(&malePostCellsPerMl);
      FieldList().push_back(&femalePostCellsPerMl);

   }

public:
   FieldDouble postCellsPerMl;
   FieldInt32 minTemplateCount;
   FieldInt32 maxTemplateCount;
   FieldDouble minPostCellsPerMl;
   FieldDouble maxPostCellsPerMl;
   FieldDouble malePostCellsPerMl;
   FieldDouble femalePostCellsPerMl;

   PlateletConfigAggregate(const std::string version) : BaseAggregate(version)
   {
      initMetaData();
   }

   virtual ~PlateletConfigAggregate() {};
};

//*********** CODE GENERATION ENDS HERE **********************

//********** UNIT TESTS **************************************


TEST_CASE("PlateletTemplateAggregrate100", "[test]")
{
   // Design doc example version 1.0.0 ----------------------------

   //Create plateletAggregate with version 1.0.0
   PlateletTemplateAggregrate Platelet_100("1.0.0");

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

TEST_CASE("PlateletTemplateAggregrate110", "[test]")
{
   //Create new plateletAggregate with version 1.1.0
   PlateletTemplateAggregrate Platelet_110("1.1.0");

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
