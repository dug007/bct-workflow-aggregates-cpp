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

      std::string vers[1] =
      {
         "1.0.0"
      };

      FieldStateEnum::FieldState _volumeMlStates[1] =
      {
         FieldStateEnum::NotSet
      };

      std::string _volumeMlDefaults[1] =
      {
         "0.0"
      };

      FieldStateEnum::FieldState _cellsPerMlStates[1] =
      {
         FieldStateEnum::NotSet
      };

      std::string _cellsPerMlDefaults[1] =
      {
         "0.0"
      };

      FieldStateEnum::FieldState _yieldStates[1] =
      {
         FieldStateEnum::Computed
      };

      std::string _yieldDefaults[1] =
      {
         "0.0"
      };

      for (int16_t i = 0; i < 1; i++)
      {
         VersionMetaData vmd;

         vmd.versionInfo = VersionInfo(vers[i]);

         FieldMeta volumeMl_("volumeMl", _volumeMlStates[i], _volumeMlDefaults[i]);
         FieldMeta cellsPerMl_("cellsPerMl", _cellsPerMlStates[i], _cellsPerMlDefaults[i]);
         FieldMeta yield_("yield", _yieldStates[i], _yieldDefaults[i]);

         vmd.fieldMetaData.push_back(volumeMl_);
         vmd.fieldMetaData.push_back(cellsPerMl_);
         vmd.fieldMetaData.push_back(yield_);

         aggMeta.push_back(vmd);
      }

      UpdateVer(); // determine ver for aggregate based on state of metadata

      volumeMl = FieldDouble("volumeMl", _ver, aggMeta);
      cellsPerMl = FieldDouble("cellsPerMl", _ver, aggMeta);
      yield = FieldDouble("yield", _ver, aggMeta);

      _fieldList.push_back(&volumeMl);
      _fieldList.push_back(&cellsPerMl);
      _fieldList.push_back(&yield);


      // Simple computation rules
      ComputeRule cr("yield", "$True", "volumeMl cellsPerMl *");
      aggMeta[_ver].computeRules.push_back(cr);

   }

public:
   FieldDouble volumeMl;
   FieldDouble cellsPerMl;
   FieldDouble yield;

   PlateletTemplateAggregrate(int16_t major, int16_t minor, int16_t patch) : BaseAggregate(major, minor, patch)
   {
      initMetaData();
   }

   virtual ~PlateletTemplateAggregrate() {};
   //void convertVersion(int16_t major, int16_t minor, int16_t patch)
   //{
   //   _major = major;
   //   _minor = minor;
   //   _patch = patch;
   //};
};

class PlateletConfigAggregate : public BaseAggregate
{

};



//*********** CODE GENERATION ENDS HERE **********************

//********** UNIT TESTS **************************************


TEST_MEMBER_FUNCTION(ComputeFieldsUnitTests, ComputeField, int)
{
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
   CHECK_EQUAL(Platelet1.yield.State(), FieldStateEnum::FieldState::Set);
}

