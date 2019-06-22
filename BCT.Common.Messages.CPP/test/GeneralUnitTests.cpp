#include "test/Test.hpp"
#include "BaseAggregate.h"
#include "BaseField.h"
#include "FieldInt32.h"
#include "FieldInt32Ro.h"
#include "FieldDouble.h"
#include "FieldDoubleRo.h"


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

public:
   FieldDouble Field1;
   FieldInt32 Field7;
   FieldInt32Ro Field7ro;  // readonly - no setter
   FieldInt32 Field7c;     // constant - setter throws
   FieldInt32 Field7d;     // defaulted
private:
   int16_t GetVer(int16_t major, int16_t minor, int16_t patch)
   {

      for (size_t i = 0; i < _majors.size(); i++)
      {
         if (major == _majors[i] && minor == _minors[i] && patch == _patchs[i])
         {
            return (int16_t)i;
         }
      }
      throw "error: invalid version"; // TODO localize
   }

   std::vector<VersionMetaData> init(int16_t ver)
   {
      std::vector<VersionMetaData> md;

      for (int16_t i=0; i < 3; i++)
      {
          FieldMeta Field1_("Field1", _Field1states[i], _Field1defaults[i]);
          FieldMeta Field7_("Field7", _Field7states[i], _Field7defaults[i]);
          FieldMeta Field7d_("Field7d", _Field7dstates[i], _Field7ddefaults[i]);
          FieldMeta Field7c_("Field7c", _Field7cstates[i], _Field7cdefaults[i]);
          FieldMeta Field7ro_("Field7ro", _Field7rostates[i], _Field7rodefaults[i]);

          std::vector<FieldMeta> fieldMetaData;
          std::vector<AssessmentRule> assessmentRules;
          std::vector<ComputeRule> computeRules;

          fieldMetaData.push_back(Field1_);
          fieldMetaData.push_back(Field7_);
          fieldMetaData.push_back(Field7d_);
          fieldMetaData.push_back(Field7c_);
          fieldMetaData.push_back(Field7ro_);

          VersionMetaData vmd;
          vmd.fieldMetaData = fieldMetaData;
          md.push_back(vmd);
      }

      Field1 = FieldDouble(_Field1states[ver], std::atof(_Field1defaults[ver].c_str()));
      Field7 = FieldInt32(_Field7states[ver], std::atoi(_Field7defaults[ver].c_str()));
      Field7d = FieldInt32(_Field7dstates[ver], std::atoi(_Field7ddefaults[ver].c_str()));
      Field7c = FieldInt32(_Field7cstates[ver], std::atoi(_Field7cdefaults[ver].c_str()));
      Field7ro = FieldInt32Ro(_Field7rostates[ver], std::atoi(_Field7rodefaults[ver].c_str()));
      return md;
   }
      //Sample1Aggregate(int16_t ver) : BaseAggregate(_majors[ver], _minors[ver], _patchs[ver]),
      //Field1(ver, _Field1states, _Field1defaults),
      //Field7(ver, _Field7states, _Field7defaults),
      //Field7ro(ver, _Field7rostates, _Field7rodefaults),
      //Field7c(ver, _Field7cstates, _Field7cdefaults),
      //Field7d(ver, _Field7dstates, _Field7ddefaults) 
      //{
      //};

public:
  // Sample1Aggregate(int16_t major, int16_t minor, int16_t patch) : Sample1Aggregate(GetVer(major, minor, patch)) { }
   
   Sample1Aggregate(int16_t major, int16_t minor, int16_t patch) : BaseAggregate(GetVer(major, minor, patch), init(GetVer(major, minor, patch)))
   {
   }

   virtual ~Sample1Aggregate() {};
   void convertVersion(int16_t major, int16_t minor, int16_t patch) 
   { 
      _major = major;
      _minor = minor;
      _patch = patch;
   };

private: 
   static std::vector<int16_t> _majors;
   static std::vector<int16_t> _minors;
   static std::vector<int16_t> _patchs;
 };

std::vector<int16_t> Sample1Aggregate::_majors = { 1,1,1 };
std::vector<int16_t> Sample1Aggregate::_minors = { 0,1,2 };
std::vector<int16_t> Sample1Aggregate::_patchs = { 0,0,0 };

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
//   CHECK_EQUAL(a.Field7ro.Value(), 5);  // readable but not writeable
//   CHECK_EQUAL((int32_t)a.Field7ro, 5); // readable but not writeable
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
}
