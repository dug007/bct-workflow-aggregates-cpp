#include "test/Test.hpp"
#include "BaseAggregate.h"
#include "BaseField.h"
#include "FieldInt32.h"
#include "FieldInt32Ro.h"
#include "FieldDouble.h"
#include "FieldDoubleRo.h"
#include "AbstractField.h"


//************ CODE GENERATION STARTS HERE ****************

using namespace Bct::Workflow::Aggregates;

class PlateletTemplateAggregrate : public BaseAggregate
{

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

         VersionInfo vi(vers[i]);

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

      // TODO TESTING
      ComputeRule cr("Field7com", "$True", "dummy");
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
   void convertVersion(int16_t major, int16_t minor, int16_t patch) 
   { 
      _major = major;
      _minor = minor;
      _patch = patch;
   };
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

   CHECK_EQUAL(a.getVersion(), "1.2.0");
   a.convertVersion(1,3,0);
   CHECK_EQUAL(a.getVersion(), "1.3.0");
   a.UpdateCalculatedFields();
   CHECK_EQUAL(a.Field7com.Value(), 999);
}
