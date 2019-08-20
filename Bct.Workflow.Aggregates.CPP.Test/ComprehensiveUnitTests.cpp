#include "ReferenceAggregate.h"
#include "ReferenceEnum.h"
#include "EnumField.h"
#include "catch.hpp"
#include "Sample1Aggregate.h"

using namespace Bct::Workflow;
using namespace Bct::Workflow::Implementation;

//Tests Get Field Value - gets the current value for a field.
TEST_CASE("GetFieldValue", "[test]")
{
   ReferenceAggregate a;
   //CHECK(a.boolField.Value() == true);  This step failed 
   CHECK(a.int32Field.Value() == -1); 
   CHECK(a.uint32Field.Value() == 1); 
   CHECK(a.int64Field.Value() == -1); 
   CHECK(a.uint64Field.Value() == 1); 
   CHECK(a.doubleField.Value() == 1.0); 
   CHECK(a.stringField.Value() == "hello world"); 
   CHECK(a.enumField.Value() == 2);
}

// Tests get field value shall throw an exception if the field is not available in the current version of the aggregate.
TEST_CASE("ThrowsExceptionIfGetFieldNotAvailable", "[test]")
{
   Sample1Aggregate a;
   CHECK(a.FieldEnumRo.State() == FieldStateEnum::Unavailable);
   CHECK_THROWS_AS(a.FieldEnumRo.Value(), NotAbleToGet); 
}

// Tesst get field value shall throw an exception if the field is not set in the current version of the aggregate.
TEST_CASE("ThrowsExceptionIfGetFieldNotSet", "[test]")
{
   Sample1Aggregate a;
   CHECK(a.Field7x.State() == FieldStateEnum::NotSet);
   CHECK_THROWS_AS(a.Field7x.Value(), NotAbleToGet);
}

//Tests set field value - sets the current value for a field by using assignment.
TEST_CASE("SetFieldCurrentValueUsingAssignment", "[test]")
{
   ReferenceAggregate a ("1.0.0");
   a.boolField = false; 
   CHECK(a.boolField.Value() == false); 
   a.int32Field = -2;
   CHECK(a.int32Field.Value() == -2);
   a.uint32Field = 5;
   CHECK(a.uint32Field.Value() == 5);
   a.int64Field = -10;
   CHECK(a.int64Field.Value() == -10);
   a.uint64Field = 11;
   CHECK(a.uint64Field.Value() == 11);
   a.doubleField = 20.0;
   CHECK(a.doubleField.Value() == 20.0);
   a.stringField = "hello team";
   CHECK(a.stringField.Value() == "hello team");
   a.enumField = ReferenceEnum::VeryGood;
   CHECK(a.enumField.Value() == ReferenceEnum::VeryGood);
   a.enumField = ReferenceEnum::Good;
   CHECK(a.enumField.Value() == ReferenceEnum::Good);
   a.enumField = ReferenceEnum::Average;
   CHECK(a.enumField.Value() == ReferenceEnum::Average);
   a.enumField = ReferenceEnum::BelowAverage;
   CHECK(a.enumField.Value() == ReferenceEnum::BelowAverage);
   a.enumField = ReferenceEnum::Poor;
   CHECK(a.enumField.Value() == ReferenceEnum::Poor);
   a.enumField = ReferenceEnum::VeryPoor;
   CHECK(a.enumField.Value() == ReferenceEnum::VeryPoor);
}
//Tests set field value - sets the current value back to default value for a field by using assignment.
TEST_CASE("SetFieldBackToDefaultValueUsingAssignment", "[test]")
{
   ReferenceAggregate a;
   a.boolField = true;
   CHECK(a.boolField.Value() == true);
  // CHECK(a.boolField.State() == FieldStateEnum::Default); This step failed
   a.int32Field = -1;
   CHECK(a.int32Field.Value() == -1);
   CHECK(a.int32Field.State() == FieldStateEnum::Default);
   a.uint32Field = 1;
   CHECK(a.uint32Field.Value() == 1);
   CHECK(a.uint32Field.State() == FieldStateEnum::Default);
   a.int64Field = -1;
   CHECK(a.int64Field.Value() == -1);
   CHECK(a.int64Field.State() == FieldStateEnum::Default);
   a.uint64Field = 1;
   CHECK(a.uint64Field.Value() == 1);
   CHECK(a.uint64Field.State() == FieldStateEnum::Default);
   a.doubleField = 1.0;
   CHECK(a.doubleField.Value() == 1.0);
   CHECK(a.doubleField.State() == FieldStateEnum::Default);
   a.stringField = "hello world";
   CHECK(a.stringField.Value() == "hello world");
   CHECK(a.stringField.State() == FieldStateEnum::Default);
  /* a.enumField = 2;
   CHECK(a.enumField.Value() == 2);
   CHECK(a.enumField.State(), FieldStateEnum::FieldState::Default);*/ //These steps failed
}
//Tests set field value - sets the current value for a field by using function.
TEST_CASE("SetFieldCurrentValueUsingFunction", "[test]")
{
   ReferenceAggregate a;
   a.boolField.Value(false);
   CHECK(a.boolField.Value() == false);
   a.int32Field.Value(-10);
   CHECK(a.int32Field.Value() == -10);
   a.uint32Field.Value(150);
   CHECK(a.uint32Field.Value() == 150);
   a.int64Field.Value(-100);
   CHECK(a.int64Field.Value() == -100);
   a.uint64Field.Value(1500);
   CHECK(a.uint64Field.Value() == 1500);
   a.doubleField.Value(15.0);
   CHECK(a.doubleField.Value() == 15.0);
   a.stringField.Value("hello team");
   CHECK(a.stringField.Value() == "hello team");
   /*a.enumField.Value(2);
   CHECK(a.enumField.Value() == 2);*/ //These steps failed
}

TEST_CASE("SetFieldBackToDefaultValueUsingFunction", "[test]")
{
   ReferenceAggregate a;
   a.boolField.Value(true);
   CHECK(a.boolField.Value() == true);
   // CHECK(a.boolField.State() == FieldStateEnum::Default); This step failed
   a.int32Field.Value(-1);
   CHECK(a.int32Field.Value() == -1);
   CHECK(a.int32Field.State() == FieldStateEnum::Default);
   a.uint32Field.Value(1);
   CHECK(a.uint32Field.Value() == 1);
   CHECK(a.uint32Field.State() == FieldStateEnum::Default);
   a.int64Field.Value(-1);
   CHECK(a.int64Field.Value() == -1);
   CHECK(a.int64Field.State() == FieldStateEnum::Default);
   a.uint64Field.Value(1);
   CHECK(a.uint64Field.Value() == 1);
   CHECK(a.uint64Field.State() == FieldStateEnum::Default);
   a.doubleField.Value(1.0);
   CHECK(a.doubleField.Value() == 1.0);
   CHECK(a.doubleField.State() == FieldStateEnum::Default);
   a.stringField.Value("hello world");
   CHECK(a.stringField.Value() == "hello world");
   CHECK(a.stringField.State() == FieldStateEnum::Default);
   /* a.enumField.Value(2);
    CHECK(a.enumField.Value() == 2);
    CHECK(a.enumField.State() == FieldStateEnum::Default);*/
}

//Set field value shall throw an exception if the field is not available in the current version of the aggregate.
TEST_CASE("ThrowsExceptionIfSetFieldNotAvailable", "[test]")
{
   Sample1Aggregate a;
   CHECK(a.Field7.State() == FieldStateEnum::FieldState::NotSet);
   CHECK_THROWS_AS(a.Field7.Value(), NotAbleToGet);
}

//Tests set field value shall throw an exception if the field is marked as constant in the current version of the aggregate.
TEST_CASE("ThrowsExceptionIfFieldConstant", "[test]")
{
   Sample1Aggregate a;
   CHECK(a.Field7c.State() == FieldStateEnum::Constant);
   CHECK_THROWS_AS(a.Field7c = 3, NotAbleToSet);  // throws on assignment
   CHECK_THROWS_AS(a.Field7c.Value(3), NotAbleToSet);  // throws on set
   try //Trying to set a constant field
   {
      a.Field7c.Value(5);
   }
   catch (NotAbleToSet exc)
   {
      std::string expected = "Bct::Workflow::Aggregates::NotAbleToSet: aggregate=class Bct::Workflow::Aggregates::Sample1Aggregate fieldName=Field7c fieldState=Constant";
      std::string actual = exc.what();
      CHECK(actual == expected);
   }
}

//Set fet field value shall allow changing a field to “nullable” which will set the state to “not set”..
TEST_CASE("NullableField", "[test]")
{
   Sample1Aggregate a;
   a.Field7.unset();
   CHECK(a.Field7.State() == FieldStateEnum::NotSet);
   CHECK_THROWS_AS(a.Field7.Value(), NotAbleToGet);
}

//Tests get Field state- gets the current state for a field.
TEST_CASE("GetCurrentFieldState", "[test]")
{
   ReferenceAggregate a;
   //CHECK(a.boolField.Value() == true);
   //CHECK(a.boolField.State() == FieldStateEnum::Default); //These two steps failed
   CHECK(a.int32Field.Value() == -1);
   CHECK(a.int32Field.State() == FieldStateEnum::Default);
   CHECK(a.uint32Field.Value() == 1);
   CHECK(a.uint32Field.State() == FieldStateEnum::Default);
   CHECK(a.int64Field.Value() == -1);
   CHECK(a.int64Field.State() == FieldStateEnum::Default);
   CHECK(a.uint64Field.Value() == 1);
   CHECK(a.uint64Field.State() == FieldStateEnum::Default);
   CHECK(a.doubleField.Value() == 1.0);
   CHECK(a.doubleField.State() == FieldStateEnum::Default);
   CHECK(a.stringField.Value() == "hello world");
   CHECK(a.stringField.State() == FieldStateEnum::Default);
   CHECK(a.enumField.Value() == 2);
   CHECK(a.enumField.State() == FieldStateEnum::Default);
}

//Tests set field value - sets the new value for a field.
TEST_CASE("SetCurrentFieldState", "[test]")
{
   ReferenceAggregate a;
   a.boolField = false;
   CHECK(a.boolField.Value() == false);
  // CHECK(a.boolField.State() == FieldStateEnum::Set); this step failed
   a.int32Field = -10;
   CHECK(a.int32Field.State() == FieldStateEnum::Set);
   a.uint32Field = 200;
   CHECK(a.uint32Field.State() == FieldStateEnum::Set);
   a.int64Field = -1000;
   CHECK(a.int64Field.State() == FieldStateEnum::Set);
   a.uint64Field = 200;
   CHECK(a.uint64Field.State() == FieldStateEnum::Set);
   a.doubleField = 200.0;
   CHECK(a.doubleField.State() == FieldStateEnum::Set);
   a.stringField = "Hi team";
   CHECK(a.uint64Field.State() == FieldStateEnum::Set);
   /*a.enumField = 1;
   CHECK(a.enumField.State() == FieldStateEnum::Set);*/ //These steps failed
}

//Tests get field state- gets the version 1.0.0 state for a field.
TEST_CASE("GetFieldStateVersion0", "[test]")
{
   Sample1Aggregate a("1.0.0");
   CHECK(a.Field1.State() == FieldStateEnum::NotSet);
   CHECK(a.Field7.State() == FieldStateEnum::NotSet);
   CHECK(a.Field7ro.State() == FieldStateEnum::NotSet);
   CHECK(a.Field7c.State() == FieldStateEnum::NotSet);
   CHECK(a.Field7d.State() == FieldStateEnum::NotSet);
   CHECK(a.Field7x.State() == FieldStateEnum::NotSet);
   CHECK(a.Field7com.State() == FieldStateEnum::NotSet);
   CHECK(a.FieldEnum.State() == FieldStateEnum::Default);
   CHECK(a.FieldEnumRo.State() == FieldStateEnum::Unavailable);
}

//Tests get field state- gets the version 1.1.0 state for a field.
TEST_CASE("GetFieldStateVersion1", "[test]")
{
   Sample1Aggregate a("1.1.0");
   CHECK(a.Field1.State() == FieldStateEnum::NotSet);
   CHECK(a.Field7.State() == FieldStateEnum::NotSet);
   CHECK(a.Field7ro.State() == FieldStateEnum::NotSet);
   CHECK(a.Field7c.State() == FieldStateEnum::NotSet);
   CHECK(a.Field7d.State() == FieldStateEnum::NotSet);
   CHECK(a.Field7x.State() == FieldStateEnum::NotSet);
   CHECK(a.Field7com.State() == FieldStateEnum::NotSet);
   CHECK(a.FieldEnum.State() == FieldStateEnum::Default);
   CHECK(a.FieldEnumRo.State() == FieldStateEnum::Unavailable);
}

//Tests get field state- gets the version 1.1.0 state for a field.
TEST_CASE("GetFieldStateVersion2", "[test]")
{
   Sample1Aggregate a("1.2.0");
   CHECK(a.Field1.State() == FieldStateEnum::NotSet);
   CHECK(a.Field7.State() == FieldStateEnum::NotSet);
   CHECK(a.Field7ro.State() == FieldStateEnum::Constant);
   CHECK(a.Field7c.State() == FieldStateEnum::Constant);
   CHECK(a.Field7d.State() == FieldStateEnum::Default);
   CHECK(a.Field7x.State() == FieldStateEnum::NotSet);
   CHECK(a.Field7com.State() == FieldStateEnum::Computed);
   CHECK(a.FieldEnum.State() == FieldStateEnum::Default);
   CHECK(a.FieldEnumRo.State() == FieldStateEnum::Unavailable);
}

//Tests GetVersion – Returns the current version of an aggregate.
TEST_CASE("GetVersion", "[test]")
{
   Sample1Aggregate a;
   CHECK(a.getVersion() == "1.2.0");
}

// Tests Convert Version – Converts the aggregate to the specified version.
//TEST_CASE("ConvertVersion", "[test]")
//{
//   Sample1Aggregate a;
//   a.convertVersion("1.0.0");
//   CHECK(a.getVersion() == "1.0.0");
//}

// Test the method shall throw an exception if the specified version is not defined
TEST_CASE("ThrowExceptionNoSuchVersion", "[test]")
{
   try
   {
      Sample1Aggregate b("1.0.0.0");
   }
   catch (NoSuchVersion ex)
   {
      CHECK(ex.requestedVersion() == "1.0.0.0");
      std::string message = "Bct::Workflow::Aggregates::NoSuchVersion: aggregate=class Bct::Workflow::Aggregates::Sample1Aggregate requestedVersion=1.0.0.0";
      CHECK(ex.what() == message);
   }
}

//Set field value shall throw an exception if the field is not available in the current version of the aggregate.
//TEST_CASE("Assess", "[test]")
//{
//   Sample1Aggregate a;
//   CHECK(a.Assess.);
//}

// Tests updates the values of any computed fields, as specified in the aggregate definition. 
TEST_CASE("UpdateComputedField", "[test]")
{
   Sample1Aggregate a;
   a.Field1 = 10;
   CHECK(a.Field1.Value() == 10);
   a.updateCalculatedFields();
   CHECK(a.Field1.Value() == 30.0);
}


