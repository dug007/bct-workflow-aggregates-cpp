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
         FieldStateEnum::Computed
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

         vmd.fieldMetaData.push_back(volumeMl_);
         vmd.fieldMetaData.push_back(cellsPerMl_);
         vmd.fieldMetaData.push_back(yield_);
         vmd.fieldMetaData.push_back(minVolumeMl_);
         vmd.fieldMetaData.push_back(maxVolumeMl_);
         vmd.fieldMetaData.push_back(minCellsPerMl_);
         vmd.fieldMetaData.push_back(maxCellsPerMl_);


         aggMeta.push_back(vmd);
      }

      UpdateVer(); // determine ver for aggregate based on state of metadata

      volumeMl = FieldDouble("volumeMl", _ver, aggMeta);
      cellsPerMl = FieldDouble("cellsPerMl", _ver, aggMeta);
      yield = FieldDouble("yield", _ver, aggMeta);
      minVolumeMl = FieldDouble("minVolumeMl", _ver, aggMeta);
      maxVolumeMl = FieldDouble("maxVolumeMl", _ver, aggMeta);
      minCellsPerMl = FieldDouble("minCellsPerMl", _ver, aggMeta);
      maxCellsPerMl = FieldDouble("maxCellsPerMl", _ver, aggMeta);

      _fieldList.push_back(&volumeMl);
      _fieldList.push_back(&cellsPerMl);
      _fieldList.push_back(&yield);
      _fieldList.push_back(&minVolumeMl);
      _fieldList.push_back(&maxVolumeMl);
      _fieldList.push_back(&minCellsPerMl);
      _fieldList.push_back(&maxCellsPerMl);


      // Simple computation rules
      ComputeRule cr1("yield", "$True", "cellsPerMl volumeMl *");
      ComputeRule cr2("volumeMl", "$True", "yield cellsPerMl /");

      aggMeta[_ver].computeRules.push_back(cr1);
      aggMeta[_ver].computeRules.push_back(cr2);

   }

public:
   FieldDouble volumeMl;
   FieldDouble cellsPerMl;
   FieldDouble yield;
   FieldDouble minVolumeMl;
   FieldDouble maxVolumeMl;
   FieldDouble minCellsPerMl;
   FieldDouble maxCellsPerMl;


   PlateletTemplateAggregrate(int16_t major, int16_t minor, int16_t patch) : BaseAggregate(major, minor, patch)
   {
      initMetaData();
   }

   virtual ~PlateletTemplateAggregrate() {};
};

class PlateletConfigAggregate : public BaseAggregate
{

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
 PlateletTemplateAggregrate Platelet1(1, 0, 0);
 CHECK_EQUAL(Platelet1.volumeMl.State(), FieldStateEnum::FieldState::NotSet);
 CHECK_EQUAL(Platelet1.cellsPerMl.State(), FieldStateEnum::FieldState::NotSet);
 CHECK_EQUAL(Platelet1.yield.State(), FieldStateEnum::FieldState::Computed);

 Platelet1.volumeMl = 500.0;
 Platelet1.cellsPerMl = 5.0e6;
 CHECK_EQUAL(Platelet1.volumeMl.State(), FieldStateEnum::FieldState::Set);
 CHECK_EQUAL(Platelet1.cellsPerMl.State(), FieldStateEnum::FieldState::Set);

 Platelet1.UpdateCalculatedFields();
 CHECK_EQUAL(Platelet1.yield.Value(), 2.5e9);
 CHECK_EQUAL(Platelet1.yield.State(), FieldStateEnum::FieldState::Computed);

 PlateletTemplateAggregrate Platelet2(1, 1, 0);
 CHECK_EQUAL(Platelet2.volumeMl.State(), FieldStateEnum::FieldState::Computed);
 CHECK_EQUAL(Platelet2.cellsPerMl.State(), FieldStateEnum::FieldState::NotSet);
 CHECK_EQUAL(Platelet2.yield.State(), FieldStateEnum::FieldState::NotSet);

 Platelet2.yield = 2.5e9;
 Platelet2.cellsPerMl = 5.0e6;

 CHECK_EQUAL(Platelet2.yield.State(), FieldStateEnum::FieldState::Set);
 CHECK_EQUAL(Platelet2.cellsPerMl.State(), FieldStateEnum::FieldState::Set);

 Platelet2.UpdateCalculatedFields();
 CHECK_EQUAL(Platelet2.volumeMl.Value(), 500.0);
 CHECK_EQUAL(Platelet2.volumeMl.State(), FieldStateEnum::FieldState::Computed);
}
