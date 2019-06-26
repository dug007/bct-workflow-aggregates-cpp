#include "test/Test.hpp"
#include "BaseAggregate.h"
#include "BaseField.h"
#include "FieldInt32.h"
#include "FieldInt32Ro.h"
#include "FieldDouble.h"
#include "FieldDoubleRo.h"
#include "AbstractField.h"
#include "RPNEvaluator.h"


//************ CODE GENERATION STARTS HERE ****************

using namespace Bct::Workflow::Aggregates;

class PlateletTemplateAggregrate : public BaseAggregate
{
private:
   void initMetaData()
   {
      std::vector<VersionMetaData> &aggMeta = _aggregateMetaData; // ref to metadata

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
         FieldStateEnum::Computed,
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
         ComputeRule cr1("yield", "$True", "cellsPerMl volumeMl *");
         aggMeta[0].computeRules.push_back(cr1);
      }
      {
         ComputeRule cr1("yield", "$Checkrange", "cellsPerMl volumeMl *");
         ComputeRule cr2("volumeMl", "$True", "yield cellsPerMl /");
         ComputeRule cr3("cellsPerMl", "$True", "yield volumeMl /");
         aggMeta[1].computeRules.push_back(cr1);
         aggMeta[1].computeRules.push_back(cr2);
         aggMeta[1].computeRules.push_back(cr3);
      }



      UpdateVer(); // determine ver for aggregate based on state of metadata

      volumeMl = FieldDouble("volumeMl", _ver, aggMeta);
      cellsPerMl = FieldDouble("cellsPerMl", _ver, aggMeta);
      yield = FieldDouble("yield", _ver, aggMeta);
      minVolumeMl = FieldDouble("minVolumeMl", _ver, aggMeta);
      maxVolumeMl = FieldDouble("maxVolumeMl", _ver, aggMeta);
      minCellsPerMl = FieldDouble("minCellsPerMl", _ver, aggMeta);
      maxCellsPerMl = FieldDouble("maxCellsPerMl", _ver, aggMeta);
      minYield = FieldDouble("minYield", _ver, aggMeta);
      maxYield = FieldDouble("maxYield", _ver, aggMeta);

      _fieldList.push_back(&volumeMl);
      _fieldList.push_back(&cellsPerMl);
      _fieldList.push_back(&yield);
      _fieldList.push_back(&minVolumeMl);
      _fieldList.push_back(&maxVolumeMl);
      _fieldList.push_back(&minCellsPerMl);
      _fieldList.push_back(&maxCellsPerMl);
      _fieldList.push_back(&minYield);
      _fieldList.push_back(&maxYield);

      
      //aggMeta[_ver].computeRules.push_back(cr1);
      //aggMeta[_ver].computeRules.push_back(cr2);
      //aggMeta[_ver].computeRules.push_back(cr3);

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


   PlateletTemplateAggregrate(int16_t major, int16_t minor, int16_t patch) : BaseAggregate(major, minor, patch)
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

      postCellsPerMl = FieldDouble("postCellsPerMl", _ver, aggMeta);
      minTemplateCount = FieldInt32("minTemplateCount", _ver, aggMeta);
      maxTemplateCount = FieldInt32("maxTemplateCount", _ver, aggMeta);
      minPostCellsPerMl = FieldDouble("minPostCellsPerMl", _ver, aggMeta);
      maxPostCellsPerMl = FieldDouble("maxPostCellsPerMl", _ver, aggMeta);
      malePostCellsPerMl = FieldDouble("malePostCellsPerMl", _ver, aggMeta);
      femalePostCellsPerMl = FieldDouble("femalePostCellsPerMl", _ver, aggMeta);

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

   PlateletConfigAggregate(int16_t major, int16_t minor, int16_t patch) : BaseAggregate(major, minor, patch)
   {
      initMetaData();
   }

   virtual ~PlateletConfigAggregate() {};
};

class Sample1Aggregate : public BaseAggregate
{
private:
   void initMetaData()
   {
      std::vector<VersionMetaData> &aggMeta = _aggregateMetaData; // ref to metadata

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

         vmd.fieldMetaData.push_back(Field1_);
         vmd.fieldMetaData.push_back(Field7_);
         vmd.fieldMetaData.push_back(Field7d_);
         vmd.fieldMetaData.push_back(Field7c_);
         vmd.fieldMetaData.push_back(Field7ro_);
         vmd.fieldMetaData.push_back(Field7com_);

         aggMeta.push_back(vmd);
      }

      UpdateVer(); // determine ver for aggregate based on state of metadata

      Field1 = FieldDouble("Field1", _ver, aggMeta);
      Field7 = FieldInt32("Field7", _ver, aggMeta);
      Field7d = FieldInt32("Field7d", _ver, aggMeta);
      Field7c = FieldInt32("Field7c", _ver, aggMeta);
      Field7ro = FieldInt32Ro("Field7ro", _ver, aggMeta);
      Field7com = FieldInt32("Field7com", _ver, aggMeta);

      _fieldList.push_back(&Field1);
      _fieldList.push_back(&Field7);
      _fieldList.push_back(&Field7d);
      _fieldList.push_back(&Field7c);
      _fieldList.push_back(&Field7ro);
      _fieldList.push_back(&Field7com);

      // Simple computation rules
      ComputeRule cr("Field7com", "$True", "Field7 20 +");
      aggMeta[_ver].computeRules.push_back(cr);

   }
 
public:

   FieldDouble Field1;
   FieldInt32 Field7;
   FieldInt32Ro Field7ro;  // readonly - no setter
   FieldInt32 Field7c;     // constant - setter throws
   FieldInt32 Field7d;     // defaulted
   FieldInt32 Field7com;   // computed

   Sample1Aggregate(int16_t major, int16_t minor, int16_t patch) : BaseAggregate(major, minor, patch)
   {
      initMetaData();
   }

   virtual ~Sample1Aggregate() {};
 
 };

//*********** CODE GENERATION ENDS HERE **********************

//********** UNIT TESTS **************************************


TEST_MEMBER_FUNCTION(GeneralUnitTests, General, int)
{
   // General unit tests ----------------------------------------------
   Sample1Aggregate a(1, 2, 0);
   CHECK_EQUAL(a.Field1.State(), FieldStateEnum::FieldState::NotSet);
   CHECK_EQUAL(a.Field7.State(), FieldStateEnum::FieldState::NotSet);
   CHECK_EQUAL(a.Field7d.State(), FieldStateEnum::FieldState::Default);
   CHECK_EQUAL(a.Field7c.State(), FieldStateEnum::FieldState::Constant);
   a.Field1 = 2.0;
   a.Field7 = 3;          // via assignment operator
   a.Field7d.Value(4);    // via function
   double f1 = a.Field1;  // via conversion operator
   //a.Field7ro = 3;      //cannot compile - no assignment operator
   //a.Field7ro.Value(3); //connot compile - setter is private
   CHECK_ALL_EXCEPTIONS(a.Field7c=3, true);  // throws on assignment
   CHECK_ALL_EXCEPTIONS(a.Field7c.Value(3), true);  // throws on set
   CHECK_EQUAL(f1, 2.0);
   CHECK_EQUAL(a.Field1.State(), FieldStateEnum::FieldState::Set);
   CHECK_EQUAL(a.Field7.Value(), 3);
   CHECK_EQUAL((int32_t)a.Field7, 3);
   CHECK_EQUAL(a.Field7ro.Value(), 5);  // readable but not writeable
   CHECK_EQUAL((int32_t)a.Field7ro, 5); // readable but not writeable
   CHECK_EQUAL(a.Field7ro.State(), FieldStateEnum::FieldState::Constant);
   CHECK_EQUAL(a.Field7c.Value(), 6);  // readable but not writeable
   CHECK_EQUAL((int32_t)a.Field7c, 6); // readable but not writeable
   CHECK_EQUAL(a.Field7c.State(), FieldStateEnum::FieldState::Constant);
   CHECK_EQUAL(a.Field7.State(), FieldStateEnum::FieldState::Set);
   CHECK_EQUAL(a.Field7d.Value(), 4);
   CHECK_EQUAL((int32_t)a.Field7d, 4);
   CHECK_EQUAL(a.Field7d.State(), FieldStateEnum::FieldState::Set);

   // set back to default
   a.Field7d = -1;
   CHECK_EQUAL(a.Field7d.Value(), -1);
   CHECK_EQUAL(a.Field7d.State(), FieldStateEnum::FieldState::Default);

   a.UpdateCalculatedFields();
   CHECK_EQUAL(a.Field7com.Value(), 23);

   // Design doc example ----------------------------

   //Create plateletAggregate with version 1.0.0
   PlateletTemplateAggregrate Platelet1(1, 0, 0);

   //Test for field that is Unavailable
   CHECK_EQUAL(Platelet1.minYield.State(), FieldStateEnum::FieldState::Unavailable);
   CHECK_EQUAL(Platelet1.maxYield.State(), FieldStateEnum::FieldState::Unavailable);
   CHECK_ALL_EXCEPTIONS(Platelet1.minYield.Value(), true);
   CHECK_ALL_EXCEPTIONS(Platelet1.maxYield.Value(), true);

   //Check initial state of fields used in calculation
   CHECK_EQUAL(Platelet1.volumeMl.State(), FieldStateEnum::FieldState::NotSet);
   CHECK_EQUAL(Platelet1.cellsPerMl.State(), FieldStateEnum::FieldState::NotSet);
   CHECK_EQUAL(Platelet1.yield.State(), FieldStateEnum::FieldState::Computed);

   //Test compute function
   Platelet1.volumeMl = 500.0;
   Platelet1.cellsPerMl = 5.0e6;
   CHECK_EQUAL(Platelet1.volumeMl.State(), FieldStateEnum::FieldState::Set);
   CHECK_EQUAL(Platelet1.cellsPerMl.State(), FieldStateEnum::FieldState::Set);
   Platelet1.UpdateCalculatedFields();
   CHECK_EQUAL(Platelet1.yield.Value(), 2.5e9);
   CHECK_EQUAL(Platelet1.yield.State(), FieldStateEnum::FieldState::Computed);
   CHECK_ALL_EXCEPTIONS(Platelet1.yield = 3, true); //Tests that computed field cannot be set

   //Create new plateletAggregate with version 1.1.0
   PlateletTemplateAggregrate Platelet2(1, 1, 0);

   //Check new fields that were added to vers[1] that were unavailable in vers[0]
   CHECK_EQUAL(Platelet2.minYield.State(), FieldStateEnum::FieldState::Constant);
   CHECK_EQUAL(Platelet2.maxYield.State(), FieldStateEnum::FieldState::Constant);

   //Check initial state for values used in calculations
   CHECK_EQUAL(Platelet2.volumeMl.State(), FieldStateEnum::FieldState::NotSet);
   CHECK_EQUAL(Platelet2.cellsPerMl.State(), FieldStateEnum::FieldState::NotSet);
   CHECK_EQUAL(Platelet2.yield.State(), FieldStateEnum::FieldState::NotSet);

   ////Test the 3 compute rules given for vers[1]
   ////ComputeRule 1. Compute yield using volumeMl and cellsPerMl
   //Platelet2.volumeMl = 500.0;
   //Platelet2.cellsPerMl = 5.0e6;
   //CHECK_EQUAL(Platelet2.volumeMl.State(), FieldStateEnum::FieldState::Set);
   //CHECK_EQUAL(Platelet2.cellsPerMl.State(), FieldStateEnum::FieldState::Set);
   //Platelet2.UpdateCalculatedFields();
   //CHECK_EQUAL(Platelet2.yield.Value(), 2.5e9);
   //CHECK_EQUAL(Platelet2.yield.State(), FieldStateEnum::FieldState::Computed); //check to make sure calculated field updates to computed

   ////ComputeRule 2. Compute volumeMl using yield and cellsPerMl
   //Platelet2.yield = 1.0e8;
   //Platelet2.cellsPerMl = 0.5e6;
   //CHECK_EQUAL(Platelet2.yield.State(), FieldStateEnum::FieldState::Set);
   //CHECK_EQUAL(Platelet2.cellsPerMl.State(), FieldStateEnum::FieldState::Set);
   //Platelet2.UpdateCalculatedFields();
   //CHECK_EQUAL(Platelet2.volumeMl.Value(), 200.0);
   //CHECK_EQUAL(Platelet2.volumeMl.State(), FieldStateEnum::FieldState::Computed); //check to make sure calculated field updates to computed

   ////ComputeRule 3. Compute cellsPerMl using yield and volumeMl
   //Platelet2.yield = 1.0e9;
   //Platelet2.volumeMl = 250.0;
   //CHECK_EQUAL(Platelet2.yield.State(), FieldStateEnum::FieldState::Set);
   //CHECK_EQUAL(Platelet2.volumeMl.State(), FieldStateEnum::FieldState::Set);
   //Platelet2.UpdateCalculatedFields();
   //CHECK_EQUAL(Platelet2.cellsPerMl.Value(), 4.0e6);
   //CHECK_EQUAL(Platelet2.cellsPerMl.State(), FieldStateEnum::FieldState::Computed); //check to make sure calculated field updates to computed
}
