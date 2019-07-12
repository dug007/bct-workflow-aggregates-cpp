#include "BaseAggregate.h"
#include "BaseField.h"
#include "FieldInt32.h"
#include "FieldInt32Ro.h"
#include "FieldDouble.h"
#include "FieldDoubleRo.h"
#include "AbstractField.h"
#include "AbstractAggregate.h"
#define CATCH_CONFIG_MAIN
#include "catch.hpp"



//************ CODE GENERATION STARTS HERE ****************

using namespace Bct::Workflow::Aggregates;

//*****************************************************************

class Sample1Aggregate : public BaseAggregate
{
private:
   void initMetaData()
   {
      std::vector<VersionMetaData> &aggMeta = AggregateMetaData();
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

      SyncCurrentVersion(); // determine ver for aggregate based on state of metadata

      Field1 = FieldDouble("Field1", Ver(), aggMeta, agg);
      Field7 = FieldInt32("Field7", Ver(), aggMeta, agg);
      Field7d = FieldInt32("Field7d", Ver(), aggMeta, agg);
      Field7c = FieldInt32("Field7c", Ver(), aggMeta, agg);
      Field7ro = FieldInt32Ro("Field7ro", Ver(), aggMeta, agg);
      Field7com = FieldInt32("Field7com", Ver(), aggMeta, agg);
      Field7x = FieldInt32("Field7x", Ver(), aggMeta, agg);

      FieldList().push_back(&Field1);
      FieldList().push_back(&Field7);
      FieldList().push_back(&Field7d);
      FieldList().push_back(&Field7c);
      FieldList().push_back(&Field7ro);
      FieldList().push_back(&Field7com);
      FieldList().push_back(&Field7x);

      // Simple computation rules
      ComputeRule cr1("Field1Id1", "Field1", "1 1 ==", "Field1 20.0 +");
      ComputeRule cr2("Field7Id1", "Field7", "Field7x Field7d $EnteredLater", "Field7x");
      ComputeRule cr3("Field7Id2", "Field7", "Field7d Field7x $EnteredLater", "Field7d");

      aggMeta[Ver()].computeRules.push_back(cr1);
      aggMeta[Ver()].computeRules.push_back(cr2);
      aggMeta[Ver()].computeRules.push_back(cr3);

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


TEST_CASE("General", "[test]")
{
   // General unit tests ----------------------------------------------
   Sample1Aggregate a("1.2.0");
   CHECK(a.Field1.State() == FieldStateEnum::FieldState::NotSet);
   CHECK(a.Field7.State() == FieldStateEnum::FieldState::NotSet);
   CHECK(a.Field7d.State() == FieldStateEnum::FieldState::Default);
   CHECK(a.Field7c.State() == FieldStateEnum::FieldState::Constant);
   CHECK(a.Field1.FieldSetCounter() == 0);
   a.Field1 = 2.0;
   a.Field7 = 3;          // via assignment operator
   a.Field7d.Value(4);    // via function
   CHECK(a.Field7d.FieldSetCounter() == 3);
   double f1 = a.Field1;  // via conversion operator
   //a.Field7ro = 3;      //cannot compile - no assignment operator
   //a.Field7ro.Value(3); //connot compile - setter is private
   CHECK_THROWS_AS(a.Field7c=3, char*);  // throws on assignment
   CHECK_THROWS_AS(a.Field7c.Value(3), char*);  // throws on set
   CHECK(f1 == 2.0);
   CHECK(a.Field1.State() == FieldStateEnum::FieldState::Set);
   CHECK(a.Field7.Value() == 3);
   CHECK((int32_t)a.Field7 == 3);
   CHECK(a.Field7ro.Value() == 5);  // readable but not writeable
   CHECK((int32_t)a.Field7ro == 5); // readable but not writeable
   CHECK(a.Field7ro.State() == FieldStateEnum::FieldState::Constant);
   CHECK(a.Field7c.Value() == 6);  // readable but not writeable
   CHECK((int32_t)a.Field7c == 6); // readable but not writeable
   CHECK(a.Field7c.State() == FieldStateEnum::FieldState::Constant);
   CHECK(a.Field7.State() == FieldStateEnum::FieldState::Set);
   CHECK(a.Field7d.Value() == 4);
   CHECK((int32_t)a.Field7d == 4);
   CHECK(a.Field7d.State() == FieldStateEnum::FieldState::Set);

   // set back to default
   a.Field7d = -1;
   CHECK(a.Field7d.Value() == -1);
   CHECK(a.Field7d.State() == FieldStateEnum::FieldState::Default);

   a.UpdateCalculatedFields();
   CHECK(a.Field1.Value() == 22.0);

   // Testing $EnteredLater
   a.Field7x = 98;
   a.Field7d = 99;
   a.UpdateCalculatedFields();    // "Field7d Field7x $EnteredLater", "Field7d")
   CHECK(a.Field7.Value() == a.Field7d.Value());
   a.Field7x = a.Field7x.Value();
   a.UpdateCalculatedFields();    // "Field7x Field7d $EnteredLater", "Field7x")
   CHECK(a.Field7.Value() == a.Field7x.Value());
}
