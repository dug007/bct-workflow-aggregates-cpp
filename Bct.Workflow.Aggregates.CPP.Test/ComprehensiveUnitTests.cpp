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
   //CHECK(a.boolField.Value() == true); 
   CHECK(a.int32Field.Value() == -1); 
   CHECK(a.uint32Field.Value() == 1); 
   CHECK(a.int64Field.Value() == -1); 
   CHECK(a.uint64Field.Value() == 1); 
   CHECK(a.doubleField.Value() == 1.0); 
   CHECK(a.stringField.Value() == "hello world"); 
   CHECK(a.enumField.Value() == 2); 
  }

// Test get field value shall throw an exception if the field is not available in the current version of the aggregate.
TEST_CASE("ThrowsExceptionFieldNot", "[test]")
{
   Sample1Aggregate a;
   CHECK(a.FieldEnumRo.State() == FieldStateEnum::Unavailable);
   CHECK_THROWS_AS(a.FieldEnumRo.Value(), NotAbleToGet);
}

//Tests set field value - sets the current value for a field.
TEST_CASE("SetFieldCurrentValueUsingAssignment", "[test]")
{
   ReferenceAggregate a;
   a.boolField = true; 
   CHECK(a.boolField.Value() == true); 
   a.int32Field = -1; 
   CHECK(a.int32Field.Value() == -1);
   a.uint32Field = 1;
   CHECK(a.uint32Field.Value() == 1);
   a.int64Field = -1;
   CHECK(a.int64Field.Value() == -1);
   a.uint64Field = 1;
   CHECK(a.uint64Field.Value() == 1);
   a.doubleField = 1.0;
   CHECK(a.doubleField.Value() == 1.0);
   a.stringField = "hello world";
   CHECK(a.stringField.Value() == "hello world");
   /*a.enumField = 2;
   CHECK(a.enumField.Value() == 2);*/

}
//Tests set field value - sets the new value for a field.
TEST_CASE("SetFieldNewValueUsingAssignment", "[test]")
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
}
//Tests set field value - sets the current value for a field.
TEST_CASE("SetFieldDefaultValueUsingAssignment", "[test]")
{
   ReferenceAggregate a;
   a.boolField = true;
   CHECK(a.boolField.Value() == true);
  // CHECK(a.boolField.State() == FieldStateEnum::Default);
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
   /*a.enumField = 2;
   CHECK(a.enumField.Value() == 2);*/
   //CHECK(a.enumField.State(), FieldStateEnum::FieldState::Default);

}
//Tests set field value - sets the current value for a field.
TEST_CASE("SetFieldCurrentValueUsingFunction", "[test]")
{
   ReferenceAggregate a;
   a.boolField.Value(true);
   CHECK(a.boolField.Value() == true);
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
  /* a.enumField.Value(200);
   CHECK(a.enumField.Value() == 200);*/
}
//Tests set field value - sets the new value for a field.
TEST_CASE("SetFieldNewValueUsingFunction", "[test]")
{
   ReferenceAggregate a;
   a.boolField.Value(false);
   CHECK(a.boolField.Value() == false);
   a.int32Field.Value(-1);
   CHECK(a.int32Field.Value() == -1);
   a.uint32Field.Value(1);
   CHECK(a.uint32Field.Value() == 1);
   a.int64Field.Value(-1);
   CHECK(a.int64Field.Value() == -1);
   a.uint64Field.Value(1);
   CHECK(a.uint64Field.Value() == 1);
   a.doubleField.Value(1.0);
   CHECK(a.doubleField.Value() == 1.0);
   a.stringField.Value("hello world");
   CHECK(a.stringField.Value() == "hello world");
   /* a.enumField.Value(2);
    CHECK(a.enumField.Value() == 2);*/
}
//Tests Set field value shall throw an exception if the field is marked as constant in the current version of the aggregate.
TEST_CASE("ThrowsExceptionFieldConstant", "[test]")
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
//Set field value shall throw an exception if the field is not available in the current version of the aggregate.
TEST_CASE("ThrowsExceptionFieldNotAvailable", "[test]")
{
   Sample1Aggregate a;
   CHECK(a.Field7.State() == FieldStateEnum::FieldState::NotSet);
   CHECK_THROWS_AS(a.Field7.Value(), NotAbleToGet);
}
//Set field value shall throw an exception if the field is not available in the current version of the aggregate.
TEST_CASE("NullableField", "[test]")
{
   Sample1Aggregate a;
   a.Field7.unset();
   CHECK(a.Field7.State() == FieldStateEnum::NotSet);
   CHECK_THROWS_AS(a.Field7.Value(), NotAbleToGet);
}
  


//Tests get Field state- gets the current value for a field.
//TEST_CASE("GetFieldState", "[test]")
//{
//   ReferenceAggregate a;
//   CHECK(a.boolField.Value() == true);
//   CHECK(a.boolField.State() == FieldStateEnum::Default); //Checks that we can get the current value for int32Field
//   a.boolField = false;
//   CHECK(a.boolField.Value() == false); //Checks that we can get the current value for int32Field
//
//
//}
//Tests set field value - sets the new value for a field.
TEST_CASE("SetFieldState", "[test]")
{
   ReferenceAggregate a;
   a.int32Field = -2;
   CHECK(a.int32Field.Value() == -2);
   CHECK(a.int32Field.State() == FieldStateEnum::Set);
}

//Set field value shall throw an exception if the field is not available in the current version of the aggregate.
TEST_CASE("GetVersion", "[test]")
{
   Sample1Aggregate a;
   CHECK(a.getVersion() == "1.2.0");
   
}
//Set field value shall throw an exception if the field is not available in the current version of the aggregate.
//TEST_CASE("ConvertVersion", "[test]")
//{
//   Sample1Aggregate a;
//   a.convertVersion("1.0.0");
//   CHECK(a.getVersion() == "1.0.0");
//
//}
//Tests set field value - sets the new value for a field.

//Set field value shall throw an exception if the field is not available in the current version of the aggregate.
//TEST_CASE("Assess", "[test]")
//{
//   Sample1Aggregate a;
//   CHECK(a.Assess.);
//  

//}
//Set field value shall throw an exception if the field is not available in the current version of the aggregate.
TEST_CASE("UpdateComputedField", "[test]")
{
   Sample1Aggregate a;
   a.Field1 = 10;
   CHECK(a.Field1.Value() == 10);
   a.updateCalculatedFields();
   CHECK(a.Field1.Value() == 30.0);

}
TEST_CASE("GetFieldState", "[test]")
{
   Sample1Aggregate a ("1.2.0");
   CHECK(a.Field1.State() == FieldStateEnum::NotSet);
   CHECK(a.Field7.State() == FieldStateEnum::NotSet);
   CHECK(a.Field7ro.State() == FieldStateEnum::Constant);
  /* CHECK(a.Field7c.State() == FieldStateEnum::FieldState::Constant);
   CHECK(a.Field7.State() == FieldStateEnum::FieldState::Set);
   CHECK(a.Field7d.State() == FieldStateEnum::FieldState::Set);*/
}
