#include "Sample1Aggregate.h"
#include "BaseAggregate.h"
#include "BaseField.h"

#include "AbstractField.h"
#include "AbstractAggregate.h"
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

using namespace Bct::Workflow::Aggregates;
using namespace Bct::Workflow::Implementation;

TEST_CASE("General", "[test]")
{
   // General unit tests ----------------------------------------------
   Sample1Aggregate a;
   CHECK(a.Field1.state() == FieldStateEnum::NotSet);
   CHECK(a.Field7.state() == FieldStateEnum::NotSet);
   CHECK_THROWS_AS(a.Field7.value(), NotAbleToGet);
   CHECK(a.Field7d.state() == FieldStateEnum::Default);
   CHECK(a.Field7c.state() == FieldStateEnum::Constant);
   CHECK(a.Field1.fieldSetCounter() == 0);
   a.Field1 = 2.0;
   a.Field7 = 3;          // via assignment operator
   a.Field7d.value(4);    // via function
   CHECK(a.Field7d.fieldSetCounter() == 3);
   double f1 = a.Field1;  // via conversion operator
   //a.Field7ro = 3;      //cannot compile - no assignment operator
   //a.Field7ro.value(3); //connot compile - setter is private
   CHECK_THROWS_AS(a.Field7c = 3, NotAbleToSet);  // throws on assignment
   CHECK_THROWS_AS(a.Field7c.value(3), NotAbleToSet);  // throws on set
   
   try //Trying to set a constant field
   {
      a.Field7c.value(5);
   }
   catch (NotAbleToSet &exc)
   {
      std::string actual = exc.what();
      std::string exception_str = "Bct::Workflow::Aggregates::NotAbleToSet:";
      std::string field_str = "fieldName=Field7c fieldState=Constant";
      std::string agg_str = "Sample1Aggregate";
      CHECK(actual.find(exception_str) != std::string::npos);
      CHECK(actual.find(field_str) != std::string::npos);
      CHECK(actual.find(agg_str) != std::string::npos);
   }
   CHECK(f1 == 2.0);
   CHECK(a.Field1.state() == FieldStateEnum::Set);
   CHECK(a.Field7.value() == 3);
   CHECK((int32_t)a.Field7 == 3);
   CHECK(a.Field7ro.value() == 5);  // readable but not writeable
   CHECK((int32_t)a.Field7ro == 5); // readable but not writeable
   CHECK(a.Field7ro.state() == FieldStateEnum::Constant);
   CHECK(a.Field7c.value() == 6);  // readable but not writeable
   CHECK((int32_t)a.Field7c == 6); // readable but not writeable
   CHECK(a.Field7c.state() == FieldStateEnum::Constant);
   CHECK(a.Field7.state() == FieldStateEnum::Set);
   CHECK(a.Field7d.value() == 4);
   CHECK((int32_t)a.Field7d == 4);
   CHECK(a.Field7d.state() == FieldStateEnum::Set);

   // set back to default
   a.Field7d = -1;
   CHECK(a.Field7d.value() == -1);
   CHECK(a.Field7d.state() != FieldStateEnum::Default);

   a.updateCalculatedFields();
   CHECK(a.Field1.value() == 22.0);

   // Testing $EnteredLater
   a.Field7x = 98;
   a.Field7d = 99;
   a.updateCalculatedFields();    // "Field7d Field7x $EnteredLater", "Field7d")
   CHECK(a.Field7.value() == a.Field7d.value());
   a.Field7x = a.Field7x.value();
   a.updateCalculatedFields();    // "Field7x Field7d $EnteredLater", "Field7x")
   CHECK(a.Field7.value() == a.Field7x.value());

   // Testing Enum fields
   CHECK(a.FieldEnum.value() == FieldStateEnum::NotSet);
   a.FieldEnum.value(FieldStateEnum::Set);
   a.FieldEnum = FieldStateEnum::Default;
   CHECK(a.FieldEnum.value() == FieldStateEnum::Default);

   CHECK(a.FieldEnumRo.state() == FieldStateEnum::Unavailable);
   //   a.FieldEnumRo.value(FieldStateEnum::Set);
   //   a.FieldEnumRo = FieldStateEnum::Default;

   CHECK(a.FieldString.value() == "sam");
   a.FieldString = "joe";
   CHECK((std::string)a.FieldString == "joe");

   CHECK(a.FieldStringro.value() == "samro");
   // compile error as expected a.FieldStringro = "joe";
   CHECK((std::string)a.FieldStringro == "samro");

}

TEST_CASE("NoSuchVersion", "[test]")
{
   try
   {
      Sample1Aggregate b("1.3.0");
   }
   catch (NoSuchVersion &ex)
   {
      CHECK(ex.requestedVersion() == "1.3.0");
      std::string actual = ex.what();
      std::string exception_str = "Bct::Workflow::Aggregates::NoSuchVersion:";
      std::string version_str = "requestedVersion=1.3.0";
      std::string agg_str = "Sample1Aggregate";
      CHECK(actual.find(exception_str) != std::string::npos);
      CHECK(actual.find(version_str) != std::string::npos);
      CHECK(actual.find(agg_str) != std::string::npos);
   }
}
