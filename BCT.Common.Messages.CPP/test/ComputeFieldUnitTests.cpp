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
      AbstractAggregate *agg = this;

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

      volumeMl = FieldDouble("volumeMl", _ver, aggMeta, agg);
      cellsPerMl = FieldDouble("cellsPerMl", _ver, aggMeta, agg);
      yield = FieldDouble("yield", _ver, aggMeta, agg);
      minVolumeMl = FieldDouble("minVolumeMl", _ver, aggMeta, agg);
      maxVolumeMl = FieldDouble("maxVolumeMl", _ver, aggMeta, agg);
      minCellsPerMl = FieldDouble("minCellsPerMl", _ver, aggMeta, agg);
      maxCellsPerMl = FieldDouble("maxCellsPerMl", _ver, aggMeta, agg);

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


   PlateletTemplateAggregrate(const std::string version) : BaseAggregate(version)
   {
      initMetaData();
   }

   virtual ~PlateletTemplateAggregrate() {};
};

class PlateletConfigAggregate : public BaseAggregate
{

};



//*********** CODE GENERATION ENDS HERE **********************

//********** UNIT TESTS **************************************

//
//TEST_MEMBER_FUNCTION(ComputeFieldsUnitTests, ComputeField, int)
//{
//   PlateletTemplateAggregrate Platelet1(1, 0, 0);
//   CHECK_EQUAL(Platelet1.volumeMl.State(), FieldStateEnum::FieldState::NotSet);
//   CHECK_EQUAL(Platelet1.cellsPerMl.State(), FieldStateEnum::FieldState::NotSet);
//   CHECK_EQUAL(Platelet1.yield.State(), FieldStateEnum::FieldState::Computed);
//
//   Platelet1.volumeMl = 500.0;
//   Platelet1.cellsPerMl = 5.0e6;
//   CHECK_EQUAL(Platelet1.volumeMl.State(), FieldStateEnum::FieldState::Set);
//   CHECK_EQUAL(Platelet1.cellsPerMl.State(), FieldStateEnum::FieldState::Set);
//
//   Platelet1.UpdateCalculatedFields();
//   CHECK_EQUAL(Platelet1.yield.Value(), 2.5e9);
//   CHECK_EQUAL(Platelet1.yield.State(), FieldStateEnum::FieldState::Computed);
//
//   PlateletTemplateAggregrate Platelet2(1, 1, 0);
//   CHECK_EQUAL(Platelet2.volumeMl.State(), FieldStateEnum::FieldState::Computed);
//   CHECK_EQUAL(Platelet2.cellsPerMl.State(), FieldStateEnum::FieldState::NotSet);
//   CHECK_EQUAL(Platelet2.yield.State(), FieldStateEnum::FieldState::NotSet);
//
//   Platelet2.yield = 2.5e9;
//   Platelet2.cellsPerMl = 5.0e6;
//   
//   CHECK_EQUAL(Platelet2.yield.State(), FieldStateEnum::FieldState::Set);
//   CHECK_EQUAL(Platelet2.cellsPerMl.State(), FieldStateEnum::FieldState::Set);
//
//   Platelet2.UpdateCalculatedFields();
//   CHECK_EQUAL(Platelet2.volumeMl.Value(), 500.0);
//   CHECK_EQUAL(Platelet2.volumeMl.State(), FieldStateEnum::FieldState::Computed);
//
//
//}

