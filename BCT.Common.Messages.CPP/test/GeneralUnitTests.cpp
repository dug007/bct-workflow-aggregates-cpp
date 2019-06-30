#include "gtest/gtest.h"
#include "BaseAggregate.h"
#include "BaseField.h"
#include "FieldInt32.h"
#include "FieldInt32Ro.h"
#include "FieldDouble.h"
#include "FieldDoubleRo.h"
#include "AbstractField.h"
#include "AbstractAggregate.h"
#include "RPNEvaluator.h"


//************ CODE GENERATION STARTS HERE ****************

using namespace Bct::Workflow::Aggregates;

class PlateletTemplateAggregrate : public BaseAggregate
{
private:
   void initMetaData()
   {
      std::vector<VersionMetaData> &aggMeta = _aggregateMetaData; // ref to metadata
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
         VersionMetaData vmd;

         vmd.versionInfo = VersionInfo(vers[i]);

         FieldMeta volumeMl_("volumeMl", _volumeMlStates[i], _volumeMlDefaults[i]);
         FieldMeta cellsPerMl_("cellsPerMl", _cellsPerMlStates[i], _cellsPerMlDefaults[i]);
         FieldMeta yield_("yield", _yieldStates[i], _yieldDefaults[i]);
         FieldMeta minVolumeMl_("minVolumeMl", _minVolumeMlStates[i], _minVolumeMlDefaults[i]);
         FieldMeta maxVolumeMl_("maxVolumeMl", _maxVolumeMlStates[i], _maxVolumeMlDefaults[i]);
         FieldMeta minCellsPerMl_("minCellsPerMl", _minCellsPerMlStates[i], _minCellsPerMlDefaults[i]);
         FieldMeta maxCellsPerMl_("maxCellsPerMl", _maxCellsPerMlStates[i], _maxCellsPerMlDefaults[i]);
         FieldMeta minYield_("minYield", _minYieldStates[i], _minYieldDefaults[i]);
         FieldMeta maxYield_("maxYield", _maxYieldStates[i], _maxYieldDefaults[i]);

         vmd.fieldMetaData.push_back(volumeMl_);
         vmd.fieldMetaData.push_back(cellsPerMl_);
         vmd.fieldMetaData.push_back(yield_);
         vmd.fieldMetaData.push_back(minVolumeMl_);
         vmd.fieldMetaData.push_back(maxVolumeMl_);
         vmd.fieldMetaData.push_back(minCellsPerMl_);
         vmd.fieldMetaData.push_back(maxCellsPerMl_);
         vmd.fieldMetaData.push_back(minYield_);
         vmd.fieldMetaData.push_back(maxYield_);


         aggMeta.push_back(vmd);
      }
      // Simple computation rules
      {
         ComputeRule cr1("yield", "1 1 ==", "cellsPerMl volumeMl *"); // TODO make $True
         aggMeta[0].computeRules.push_back(cr1);
      }
      {
         ComputeRule cr1("yield", "volumeMl yield $EnteredLater", "cellsPerMl volumeMl *");
         ComputeRule cr3("cellsPerMl", "volumeMl cellsPerMl $EnteredLater yield cellsPerMl $EnteredLater &&", "yield volumeMl /");
         ComputeRule cr2("volumeMl", "cellsPerMl volumeMl $EnteredLater yield volumeMl $EnteredLater &&", "yield cellsPerMl /");
         aggMeta[1].computeRules.push_back(cr1);
         aggMeta[1].computeRules.push_back(cr2);
         aggMeta[1].computeRules.push_back(cr3);
      }



      UpdateVer(); // determine ver for aggregate based on state of metadata

      volumeMl = FieldDouble("volumeMl", _ver, aggMeta, agg);
      cellsPerMl = FieldDouble("cellsPerMl", _ver, aggMeta, agg);
      yield = FieldDouble("yield", _ver, aggMeta, agg);
      minVolumeMl = FieldDouble("minVolumeMl", _ver, aggMeta, agg);
      maxVolumeMl = FieldDouble("maxVolumeMl", _ver, aggMeta, agg);
      minCellsPerMl = FieldDouble("minCellsPerMl", _ver, aggMeta, agg);
      maxCellsPerMl = FieldDouble("maxCellsPerMl", _ver, aggMeta, agg);
      minYield = FieldDouble("minYield", _ver, aggMeta, agg);
      maxYield = FieldDouble("maxYield", _ver, aggMeta, agg);

      _fieldList.push_back(&volumeMl);
      _fieldList.push_back(&cellsPerMl);
      _fieldList.push_back(&yield);
      _fieldList.push_back(&minVolumeMl);
      _fieldList.push_back(&maxVolumeMl);
      _fieldList.push_back(&minCellsPerMl);
      _fieldList.push_back(&maxCellsPerMl);
      _fieldList.push_back(&minYield);
      _fieldList.push_back(&maxYield);

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


   PlateletTemplateAggregrate(const std::string version) : BaseAggregate (version)
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
      std::vector<VersionMetaData> &aggMeta = _aggregateMetaData; // ref to metadata
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
         VersionMetaData vmd;

         vmd.versionInfo = VersionInfo(vers[i]);

         FieldMeta postCellsPerMl_("postCellsPerMl", _postCellsPerMlStates[i], _postCellsPerMlDefaults[i]);
         FieldMeta minTemplateCount_("minTemplateCount", _minTemplateCountStates[i], _minTemplateCountDefaults[i]);
         FieldMeta maxTemplateCount_("maxTemplateCount", _maxTemplateCountStates[i], _maxTemplateCountDefaults[i]);
         FieldMeta minPostCellsPerMl_("minPostCellsPerMl", _minPostCellsPerMlStates[i], _minPostCellsPerMlDefaults[i]);
         FieldMeta maxPostCellsPerMl_("maxPostCellsPerMl", _maxPostCellsPerMlStates[i], _maxPostCellsPerMlDefaults[i]);
         FieldMeta malePostCellsPerMl_("malePostCellsPerMl", _malePostCellsPerMlStates[i], _malePostCellsPerMlDefaults[i]);
         FieldMeta femalePostCellsPerMl_("femalePostCellsPerMl", _femalePostCellsPerMlStates[i], _femalePostCellsPerMlDefaults[i]);

         vmd.fieldMetaData.push_back(postCellsPerMl_);
         vmd.fieldMetaData.push_back(minTemplateCount_);
         vmd.fieldMetaData.push_back(maxTemplateCount_);
         vmd.fieldMetaData.push_back(minPostCellsPerMl_);
         vmd.fieldMetaData.push_back(maxPostCellsPerMl_);
         vmd.fieldMetaData.push_back(malePostCellsPerMl_);
         vmd.fieldMetaData.push_back(femalePostCellsPerMl_);


         aggMeta.push_back(vmd);
      }

      UpdateVer(); // determine ver for aggregate based on state of metadata

      postCellsPerMl = FieldDouble("postCellsPerMl", _ver, aggMeta, agg);
      minTemplateCount = FieldInt32("minTemplateCount", _ver, aggMeta, agg);
      maxTemplateCount = FieldInt32("maxTemplateCount", _ver, aggMeta, agg);
      minPostCellsPerMl = FieldDouble("minPostCellsPerMl", _ver, aggMeta, agg);
      maxPostCellsPerMl = FieldDouble("maxPostCellsPerMl", _ver, aggMeta, agg);
      malePostCellsPerMl = FieldDouble("malePostCellsPerMl", _ver, aggMeta, agg);
      femalePostCellsPerMl = FieldDouble("femalePostCellsPerMl", _ver, aggMeta, agg);

      _fieldList.push_back(&postCellsPerMl);
      _fieldList.push_back(&minTemplateCount);
      _fieldList.push_back(&maxTemplateCount);
      _fieldList.push_back(&minPostCellsPerMl);
      _fieldList.push_back(&maxPostCellsPerMl);
      _fieldList.push_back(&malePostCellsPerMl);
      _fieldList.push_back(&femalePostCellsPerMl);

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


//*****************************************************************

class Sample1Aggregate : public BaseAggregate
{
private:
   void initMetaData()
   {
      std::vector<VersionMetaData> &aggMeta = _aggregateMetaData; // ref to metadata
      AbstractAggregate *agg = this;

      std::string vers[3] =
      {
         "1.0.0",
         "1.1.0",
         "1.2.0"
      };

      FieldStateEnum::FieldState _Field1states[3] =
      {
         FieldStateEnum::NotSet,
         FieldStateEnum::NotSet,
         FieldStateEnum::NotSet
      };

      std::string _Field1defaults[3] =
      {
         "0.0",
         "0.0",
         "0.0"
      };

      FieldStateEnum::FieldState _Field7states[3] =
      {
         FieldStateEnum::NotSet,
         FieldStateEnum::NotSet,
         FieldStateEnum::NotSet,
      };

      std::string _Field7defaults[3] =
      {
         "0",
         "0",
         "0"
      };

      FieldStateEnum::FieldState _Field7rostates[3] =
      {
         FieldStateEnum::NotSet,
         FieldStateEnum::NotSet,
         FieldStateEnum::Constant
      };

      std::string _Field7rodefaults[3] =
      {
         "1",
         "2",
         "5"
      };

      FieldStateEnum::FieldState _Field7cstates[3] =
      {
         FieldStateEnum::NotSet,
         FieldStateEnum::NotSet,
         FieldStateEnum::Constant
      };

      std::string _Field7cdefaults[3] =
      {
         "1",
         "2",
         "6"
      };

      FieldStateEnum::FieldState _Field7dstates[3] =
      {
         FieldStateEnum::NotSet,
         FieldStateEnum::NotSet,
         FieldStateEnum::Default
      };

      std::string _Field7ddefaults[3] =
      {
         "0",
         "0",
         "-1"
      };

      FieldStateEnum::FieldState _Field7comstates[3] =
      {
         FieldStateEnum::NotSet,
         FieldStateEnum::NotSet,
         FieldStateEnum::Computed
      };

      std::string _Field7comdefaults[3] =
      {
         "0",
         "0",
         "-1"
      };

      FieldStateEnum::FieldState _Field7xstates[3] =
      {
         FieldStateEnum::NotSet,
         FieldStateEnum::NotSet,
         FieldStateEnum::NotSet
      };

      std::string _Field7xdefaults[3] =
      {
         "0",
         "0",
         "0"
      };


      for (int16_t i=0; i < 3; i++)
      {
         VersionMetaData vmd;

         vmd.versionInfo = VersionInfo(vers[i]);

         FieldMeta Field1_("Field1", _Field1states[i], _Field1defaults[i]);
         FieldMeta Field7_("Field7", _Field7states[i], _Field7defaults[i]);
         FieldMeta Field7d_("Field7d", _Field7dstates[i], _Field7ddefaults[i]);
         FieldMeta Field7c_("Field7c", _Field7cstates[i], _Field7cdefaults[i]);
         FieldMeta Field7ro_("Field7ro", _Field7rostates[i], _Field7rodefaults[i]);
         FieldMeta Field7com_("Field7com", _Field7comstates[i], _Field7comdefaults[i]);
         FieldMeta Field7x_("Field7x", _Field7xstates[i], _Field7xdefaults[i]);

         vmd.fieldMetaData.push_back(Field1_);
         vmd.fieldMetaData.push_back(Field7_);
         vmd.fieldMetaData.push_back(Field7d_);
         vmd.fieldMetaData.push_back(Field7c_);
         vmd.fieldMetaData.push_back(Field7ro_);
         vmd.fieldMetaData.push_back(Field7com_);
         vmd.fieldMetaData.push_back(Field7x_);

         aggMeta.push_back(vmd);
      }

      UpdateVer(); // determine ver for aggregate based on state of metadata

      Field1 = FieldDouble("Field1", _ver, aggMeta, agg);
      Field7 = FieldInt32("Field7", _ver, aggMeta, agg);
      Field7d = FieldInt32("Field7d", _ver, aggMeta, agg);
      Field7c = FieldInt32("Field7c", _ver, aggMeta, agg);
      Field7ro = FieldInt32Ro("Field7ro", _ver, aggMeta, agg);
      Field7com = FieldInt32("Field7com", _ver, aggMeta, agg);
      Field7x = FieldInt32("Field7x", _ver, aggMeta, agg);

      _fieldList.push_back(&Field1);
      _fieldList.push_back(&Field7);
      _fieldList.push_back(&Field7d);
      _fieldList.push_back(&Field7c);
      _fieldList.push_back(&Field7ro);
      _fieldList.push_back(&Field7com);
      _fieldList.push_back(&Field7x);

      // Simple computation rules
      ComputeRule cr1("Field1", "1 1 ==", "Field1 20.0 +");
      ComputeRule cr2("Field7", "Field7x Field7d $EnteredLater", "Field7x");
      ComputeRule cr3("Field7", "Field7d Field7x $EnteredLater", "Field7d");

      aggMeta[_ver].computeRules.push_back(cr1);
      aggMeta[_ver].computeRules.push_back(cr2);
      aggMeta[_ver].computeRules.push_back(cr3);

   }
 
public:

   FieldDouble Field1;
   FieldInt32 Field7;
   FieldInt32Ro Field7ro;  // readonly - no setter
   FieldInt32 Field7c;     // constant - setter throws
   FieldInt32 Field7d;     // defaulted
   FieldInt32 Field7com;   // computed
   FieldInt32 Field7x;     // extra field for tests

   Sample1Aggregate(const std::string version) : BaseAggregate(version)
   {
      initMetaData();
   }

   virtual ~Sample1Aggregate() {};
 
 };

//*********** CODE GENERATION ENDS HERE **********************

//********** UNIT TESTS **************************************


TEST(GeneralUnitTests, General)
{
   // General unit tests ----------------------------------------------
   Sample1Aggregate a("1.2.0");
   EXPECT_EQ(a.Field1.State(), FieldStateEnum::FieldState::NotSet);
   EXPECT_EQ(a.Field7.State(), FieldStateEnum::FieldState::NotSet);
   EXPECT_EQ(a.Field7d.State(), FieldStateEnum::FieldState::Default);
   EXPECT_EQ(a.Field7c.State(), FieldStateEnum::FieldState::Constant);
   EXPECT_EQ(a.Field1.FieldSetCounter(), 0);
   a.Field1 = 2.0;
   a.Field7 = 3;          // via assignment operator
   a.Field7d.Value(4);    // via function
   EXPECT_EQ(a.Field7d.FieldSetCounter(), 3);
   double f1 = a.Field1;  // via conversion operator
   //a.Field7ro = 3;      //cannot compile - no assignment operator
   //a.Field7ro.Value(3); //connot compile - setter is private
   EXPECT_THROW(a.Field7c=3, char*);  // throws on assignment
   EXPECT_THROW(a.Field7c.Value(3), char*);  // throws on set
   EXPECT_EQ(f1, 2.0);
   EXPECT_EQ(a.Field1.State(), FieldStateEnum::FieldState::Set);
   EXPECT_EQ(a.Field7.Value(), 3);
   EXPECT_EQ((int32_t)a.Field7, 3);
   EXPECT_EQ(a.Field7ro.Value(), 5);  // readable but not writeable
   EXPECT_EQ((int32_t)a.Field7ro, 5); // readable but not writeable
   EXPECT_EQ(a.Field7ro.State(), FieldStateEnum::FieldState::Constant);
   EXPECT_EQ(a.Field7c.Value(), 6);  // readable but not writeable
   EXPECT_EQ((int32_t)a.Field7c, 6); // readable but not writeable
   EXPECT_EQ(a.Field7c.State(), FieldStateEnum::FieldState::Constant);
   EXPECT_EQ(a.Field7.State(), FieldStateEnum::FieldState::Set);
   EXPECT_EQ(a.Field7d.Value(), 4);
   EXPECT_EQ((int32_t)a.Field7d, 4);
   EXPECT_EQ(a.Field7d.State(), FieldStateEnum::FieldState::Set);

   // set back to default
   a.Field7d = -1;
   EXPECT_EQ(a.Field7d.Value(), -1);
   EXPECT_EQ(a.Field7d.State(), FieldStateEnum::FieldState::Default);

   a.UpdateCalculatedFields();
   EXPECT_EQ(a.Field1.Value(), 22.0);

   // Testing $EnteredLater
   a.Field7x = 98;
   a.Field7d = 99;
   a.UpdateCalculatedFields();    // "Field7d Field7x $EnteredLater", "Field7d")
   EXPECT_EQ(a.Field7.Value(), a.Field7d.Value());
   a.Field7x = a.Field7x.Value();
   a.UpdateCalculatedFields();    // "Field7x Field7d $EnteredLater", "Field7x")
   EXPECT_EQ(a.Field7.Value(), a.Field7x.Value());


   // Design doc example ----------------------------

   //Create plateletAggregate with version 1.0.0
   PlateletTemplateAggregrate Platelet_100("1.0.0");

   //Test for field that is Unavailable
   EXPECT_EQ(Platelet_100.minYield.State(), FieldStateEnum::FieldState::Unavailable);
   EXPECT_EQ(Platelet_100.maxYield.State(), FieldStateEnum::FieldState::Unavailable);
   EXPECT_THROW(Platelet_100.minYield.Value(), char*);
   EXPECT_THROW(Platelet_100.maxYield.Value(), char*);

   //Check initial state of fields used in calculation
   EXPECT_EQ(Platelet_100.volumeMl.State(), FieldStateEnum::FieldState::NotSet);
   EXPECT_EQ(Platelet_100.cellsPerMl.State(), FieldStateEnum::FieldState::NotSet);
   EXPECT_EQ(Platelet_100.yield.State(), FieldStateEnum::FieldState::NotSet);

   //Test compute function for 1.0.0
   //Field: Yield
   //   Condition : true
   //   Expression :  VolumeMl * CellsPerMl
   Platelet_100.yield = 0.0;
   Platelet_100.volumeMl = 500.0;
   Platelet_100.cellsPerMl = 5.0e6;
   double expectedYield100 = Platelet_100.volumeMl.Value() * Platelet_100.cellsPerMl.Value();
   EXPECT_EQ(Platelet_100.volumeMl.State(), FieldStateEnum::FieldState::Set);
   EXPECT_EQ(Platelet_100.cellsPerMl.State(), FieldStateEnum::FieldState::Set);
   Platelet_100.UpdateCalculatedFields();
   EXPECT_EQ(Platelet_100.yield.Value(), expectedYield100);
   EXPECT_EQ(Platelet_100.yield.State(), FieldStateEnum::FieldState::Computed);


   //Create new plateletAggregate with version 1.1.0
   PlateletTemplateAggregrate Platelet_110("1.1.0");

   //Check new fields that were added to vers[1] that were unavailable in vers[0]
   EXPECT_EQ(Platelet_110.minYield.State(), FieldStateEnum::FieldState::Constant);
   EXPECT_EQ(Platelet_110.maxYield.State(), FieldStateEnum::FieldState::Constant);

   //Check initial state for values used in calculations
   EXPECT_EQ(Platelet_110.volumeMl.State(), FieldStateEnum::FieldState::NotSet);
   EXPECT_EQ(Platelet_110.cellsPerMl.State(), FieldStateEnum::FieldState::NotSet);
   EXPECT_EQ(Platelet_110.yield.State(), FieldStateEnum::FieldState::NotSet);

   //Test the 3 compute rules given for version 1.1.0 which includes condition expression
   //ComputeRule 1. Compute yield using volumeMl and cellsPerMl
   //Field: Yield
   //   Condition : $EnteredLater(VolumeMl, Yield) && $EnteredLater(CellsPerMl, Yield)
   //   Expression :  VolumeMl * CellsPerMl
   Platelet_110.yield = 0.0;
   Platelet_110.volumeMl = 500.0;
   Platelet_110.cellsPerMl = 5.0e6;
   double expectedYield110 = Platelet_110.volumeMl.Value() * Platelet_110.cellsPerMl.Value();
   EXPECT_EQ(Platelet_110.volumeMl.State(), FieldStateEnum::FieldState::Set);
   EXPECT_EQ(Platelet_110.cellsPerMl.State(), FieldStateEnum::FieldState::Set);
   Platelet_110.UpdateCalculatedFields();
   EXPECT_EQ(Platelet_110.yield.Value(), expectedYield110);
   EXPECT_EQ(Platelet_110.yield.State(), FieldStateEnum::FieldState::Computed); //check to make sure calculated field updates to computed

   // ComputeRule 2. Compute volumeMl using yield and cellsPerMl
   //Field: VolumeMl
   //   Condition : $EnteredLater(CellsPerMl, VolumeMl) && $EnteredLater(Yield, VolumeMl)
   //   Expression : Yield / CellsPerMl
   Platelet_110.volumeMl = 0.0;
   Platelet_110.yield = 1.0e8;
   Platelet_110.cellsPerMl = 0.5e6;
   double expectedVolumeMl = Platelet_110.yield.Value() / Platelet_110.cellsPerMl.Value();
   EXPECT_EQ(Platelet_110.yield.State(), FieldStateEnum::FieldState::Set);
   EXPECT_EQ(Platelet_110.cellsPerMl.State(), FieldStateEnum::FieldState::Set);
   Platelet_110.UpdateCalculatedFields();
   EXPECT_EQ(Platelet_110.volumeMl.Value(), expectedVolumeMl);
   EXPECT_EQ(Platelet_110.volumeMl.State(), FieldStateEnum::FieldState::Computed); //check to make sure calculated field updates to computed

   //ComputeRule 3. Compute cellsPerMl using yield and volumeMl
   //Field: CellsPerMl
   //   Condition : $EnteredLater(VolumeMl, CellsPerMl) && $EnteredLater(Yield, CellsPerMl)
   //   Expression :   Yield / VolumeMl
   Platelet_110.cellsPerMl = 0.0;
   Platelet_110.yield = 1.0e9;
   Platelet_110.volumeMl = 250.0;
   double expectedCellsPerMl = Platelet_110.yield.Value() / Platelet_110.volumeMl.Value();
   EXPECT_EQ(Platelet_110.yield.State(), FieldStateEnum::FieldState::Set);
   EXPECT_EQ(Platelet_110.volumeMl.State(), FieldStateEnum::FieldState::Set);
   Platelet_110.UpdateCalculatedFields();
   EXPECT_EQ(Platelet_110.cellsPerMl.Value(), expectedCellsPerMl);
   EXPECT_EQ(Platelet_110.cellsPerMl.State(), FieldStateEnum::FieldState::Computed); //check to make sure calculated field updates to computed
}
