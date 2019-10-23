#include "ReferenceAggregate.h"
#include "ReferenceEnum.h"
#include "EnumField.h"
#include "Sample1Aggregate.h"
#include "PlateletTemplateAggregate.h"
#include "BaseAggregate.h"
#include "TestHelperBaseField.h"
#include "AbstractAggregate.h"

#include "catch.hpp"


using namespace Bct::Workflow;
using namespace Bct::Workflow::Implementation;
using namespace Bct::Workflow::Aggregates;

class VectorFieldUnitTest : public BaseAggregate
{
private:
   static AggregateMetaData *s_metaData;
   static bool s_initialized;

public:
   VectorField<int32_t> vectorInt32Field;
   VectorField<double> vectorDblField;
   VectorField<std::string> vectorStrField;
   VectorField<ReferenceAggregate> vectorAggField;
   VectorField<uint32_t> vectorUint32Field;
   VectorField<int64_t> vectorInt64Field;
   VectorField<uint64_t> vectorUint64Field;
   VectorField<bool> vectorBoolField;
   VectorField<int64_t> vectorVersion0only;
   VectorField<int64_t> vectorVersion1only;
   VectorField<bool> vectorVersion2only;



   VectorFieldUnitTest(const std::string &version)
      :
      BaseAggregate(version),
      vectorInt32Field(0, this),
      vectorDblField(1, this),
      vectorStrField(2, this),
      vectorAggField(3, this),
      vectorUint32Field(4, this),
      vectorInt64Field(5, this),
      vectorUint64Field(6, this),
      vectorBoolField(7, this),
      vectorVersion0only(8, this),
      vectorVersion1only(9, this),
      vectorVersion2only(10, this)

   {
      FieldList().push_back(&vectorInt32Field);
      FieldList().push_back(&vectorDblField);
      FieldList().push_back(&vectorStrField);
      FieldList().push_back(&vectorAggField);
      FieldList().push_back(&vectorUint32Field);
      FieldList().push_back(&vectorInt64Field);
      FieldList().push_back(&vectorUint64Field);
      FieldList().push_back(&vectorBoolField);
      FieldList().push_back(&vectorVersion0only);
      FieldList().push_back(&vectorVersion1only);
      FieldList().push_back(&vectorVersion2only);

      // metadata TestVectorFieldAggregate------------------->
      static AggregateMetaData tm;
      tm.addField(0, "vectorInt32Field", Bct::Workflow::TypeEnum::ArrayType);
      tm.addField(1, "vectorDblField", Bct::Workflow::TypeEnum::ArrayType);
      tm.addField(2, "vectorStrField", Bct::Workflow::TypeEnum::ArrayType);
      tm.addField(3, "vectorAggField", Bct::Workflow::TypeEnum::ArrayType);
      tm.addField(4, "vectorUint32Field", Bct::Workflow::TypeEnum::ArrayType);
      tm.addField(5, "vectorInt64Field", Bct::Workflow::TypeEnum::ArrayType);
      tm.addField(6, "vectorUint64Field", Bct::Workflow::TypeEnum::ArrayType);
      tm.addField(7, "vectorBoolField", Bct::Workflow::TypeEnum::ArrayType);
      tm.addField(8, "vectorVersion0only", Bct::Workflow::TypeEnum::ArrayType);
      tm.addField(9, "vectorVersion1only", Bct::Workflow::TypeEnum::ArrayType);
      tm.addField(10, "vectorVersion2only", Bct::Workflow::TypeEnum::ArrayType);

      tm.addVersion("1.0.0");
      tm.addVersion("1.1.0");
      tm.addVersion("1.2.0");

      tm.addFieldMetaToAllVersions(0, FieldStateEnum::NotSet, "notset");
      tm.addFieldMetaToAllVersions(1, FieldStateEnum::NotSet, "notset");
      tm.addFieldMetaToAllVersions(2, FieldStateEnum::NotSet, "notset");
      tm.addFieldMetaToAllVersions(3, FieldStateEnum::NotSet, "notset");
      tm.addFieldMetaToAllVersions(4, FieldStateEnum::NotSet, "notset");
      tm.addFieldMetaToAllVersions(5, FieldStateEnum::NotSet, "notset");
      tm.addFieldMetaToAllVersions(6, FieldStateEnum::NotSet, "notset");
      tm.addFieldMetaToAllVersions(7, FieldStateEnum::NotSet, "notset");
      tm.addFieldMeta(8, FieldStateEnum::NotSet, "notset").toVersion(0);
      tm.addFieldMeta(8, FieldStateEnum::Unavailable, "unavailable")
         .toVersion(1)
         .toVersion(2)
         ;
      tm.addFieldMeta(9, FieldStateEnum::Unavailable, "unavailable").toVersion(0);
      tm.addFieldMeta(9, FieldStateEnum::NotSet, "notset").toVersion(1);
      tm.addFieldMeta(9, FieldStateEnum::Unavailable, "unavailable").toVersion(2);
      tm.addFieldMeta(10, FieldStateEnum::Unavailable, "unavailable")
         .toVersion(0)
         .toVersion(1)
         ;
    /*  tm.addFieldMeta(11, FieldStateEnum::NotSet, "notset").toVersion(2);
      initialized = true;*/
  
      


      bindMetaData(&tm);
      // <----------------- metadata TestVectorFieldAggregate 

      syncVersion();
   }

   static void bindMetaData(AggregateMetaData  *metaData)
   {
      s_metaData = metaData;
      s_initialized = true;
   }

   virtual AggregateMetaData &MetaData() const
   {
      return *s_metaData;
   };
};

bool VectorFieldUnitTest::s_initialized = false;
AggregateMetaData *VectorFieldUnitTest::s_metaData;


namespace Bct
{
   namespace Workflow
   {
      namespace Implementation
      {
         class TestBaseFieldSerialization : public BaseAggregate
         {
         private:
            void pushFields()
            {
               FieldList().push_back(&boolField);
            }
         public:
            TestHelperBaseField<bool>                     boolField;
            virtual ~TestBaseFieldSerialization()
            {
            }

            TestBaseFieldSerialization() :
               BaseAggregate(BaseAggregate::UseMostRecentVersionStr),
               boolField(0, this)
            {
               pushFields();
               syncVersion();
            }

            static AggregateMetaData & s_MetaData()
            {
               static AggregateMetaData tm;
               static bool initialized = false;

               if (!initialized)
               {
                  tm.addVersion("1.0.0");
                  tm.addField(0, "boolField", Bct::Workflow::TypeEnum::BoolType);
                  tm.addFieldMetaToAllVersions(0, FieldStateEnum::Default, "true");
                  initialized = true;
               }
               return tm;
            };

            AggregateMetaData & MetaData() const
            {
               return s_MetaData();
            };
         };
      }
   }
}

//Tests Get Field Value - gets the current value for a field.
TEST_CASE("GetFieldValue", "[test]")
{
   ReferenceAggregate a;
   CHECK(a.boolField.Value() == true);
   CHECK(a.int32Field.Value() == -1); 
   CHECK(a.uint32Field.Value() == 1); 
   CHECK(a.int64Field.Value() == -1); 
   CHECK(a.uint64Field.Value() == 1); 
   CHECK(a.doubleField.Value() == 1.0); 
   CHECK(a.stringField.Value() == "hello world"); 
   CHECK(a.enumField.Value() == 2);
   std::vector<int32_t> fromInt;
   fromInt.push_back(3);
   a.vectorIntField = fromInt;
   CHECK(a.vectorIntField.Value()[0] == 3);
}

// Tests get field value shall throw an exception if the field is not available in the current version of the aggregate.
TEST_CASE("ThrowsExceptionIfGetFieldNotAvailable", "[test]")
{
   Sample1Aggregate a;
   CHECK(a.FieldEnumRo.State() == FieldStateEnum::Unavailable);
   CHECK_THROWS_AS(a.FieldEnumRo.Value(), NotAbleToGet); 
}

// Tests get field value shall throw an exception if the field is not set in the current version of the aggregate.
TEST_CASE("ThrowsExceptionIfGetFieldNotSet", "[test]")
{
   Sample1Aggregate a;
   CHECK(a.Field7x.State() == FieldStateEnum::NotSet);
   CHECK_THROWS_AS(a.Field7x.Value(), NotAbleToGet);
}

 //Tests get vector field value shall throw an exception if the vector field is not available in the current version of the aggregate.
TEST_CASE("ThrowsExceptionIfGetVecotrFieldNotAvailable", "[test]")
{
   VectorFieldUnitTest a ("1.0.0");
   CHECK(a.vectorVersion1only.State() == FieldStateEnum::Unavailable);
   CHECK_THROWS_AS(a.vectorVersion1only.Value(), NotAbleToGet);
}

// Tests get vector field value shall throw an exception if the vector field is not set in the current version of the aggregate.
TEST_CASE("ThrowsExceptionIfGetVectorFieldNotSet", "[test]")
{
   ReferenceAggregate a;
   CHECK(a.vectorIntField.State() == FieldStateEnum::NotSet);
   CHECK_THROWS_AS(a.vectorIntField.Value(), NotAbleToGet);
}

/*TEST_CASE("SetFieldUsingAssignment","[test]")
{
   ReferenceAggregate from;
   ReferenceAggregate to;

   from.boolField = false;
   from.boolField = false;
   to.boolField = true;
   CHECK( to.boolField.FieldSetCounter() != from.boolField.FieldSetCounter());
   to.boolField = from.boolField;
   CHECK(to.boolField == false);
   CHECK(to.boolField.FieldSetCounter() == from.boolField.FieldSetCounter());

   from.int32Field = 200;
   from.int32Field = 200;
   to.int32Field = 201;
   CHECK(to.int32Field.FieldSetCounter() != from.int32Field.FieldSetCounter());
   to.int32Field = from.int32Field;
   CHECK(to.int32Field == 200);
   CHECK(to.int32Field.FieldSetCounter() == from.int32Field.FieldSetCounter());

   from.enumField = ReferenceEnum::Poor;
   from.enumField = ReferenceEnum::Poor;
   to.enumField = ReferenceEnum::VeryPoor;
   CHECK(to.enumField.FieldSetCounter() != from.enumField.FieldSetCounter());
   to.enumField = from.enumField;
   CHECK(to.enumField == ReferenceEnum::Poor);
   CHECK(to.enumField.FieldSetCounter() == from.enumField.FieldSetCounter());

   from.stringField = "happy";
   from.stringField = "happy";
   to.stringField = "days";
   CHECK(to.stringField.FieldSetCounter() != from.stringField.FieldSetCounter());
   to.stringField = from.stringField;
   CHECK((std::string)to.stringField == "happy");
   CHECK(to.stringField.FieldSetCounter() == from.stringField.FieldSetCounter());

   Sample1Aggregate fromS;
   Sample1Aggregate toS;

   // Just make sure assignment does not throw exception on ro fields.
   toS.FieldEnumRo = fromS.FieldEnumRo;
   toS.FieldStringro = fromS.FieldStringro;
}*/

//Tests Set Field Value - sets the current value for a field by using assignment.
TEST_CASE("SetFieldCurrentValueUsingAssignment", "[test]")
{
   ReferenceAggregate a ("v1.0.0");
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
   a.enumField.ComputedValueString("0");
   CHECK(a.enumField == ReferenceEnum::VeryGood);
   a.enumField.ComputedValueString("1");
   CHECK(a.enumField == ReferenceEnum::Good);
   a.enumField.ComputedValueString("2");
   CHECK(a.enumField == ReferenceEnum::Average);
   a.enumField.ComputedValueString("4");
   CHECK(a.enumField == ReferenceEnum::BelowAverage);
   a.enumField.ComputedValueString("8");
   CHECK(a.enumField == ReferenceEnum::Poor);
   a.enumField.ComputedValueString("16");
   CHECK(a.enumField == ReferenceEnum::VeryPoor);
}

//Tests Set Vector Field Value - sets the current value for a vector field by using assignment.
TEST_CASE("SetVectorFieldUsingAssignment", "[test]")
{

   VectorFieldUnitTest fromAgg("1.0.0");

   std::vector<int32_t> fromInt32;
   fromInt32.push_back(-100);
   fromInt32.push_back(-200);
   fromAgg.vectorInt32Field = fromInt32;
   CHECK(fromAgg.vectorInt32Field.Value()[0] == -100);
   CHECK(fromAgg.vectorInt32Field.Value()[1] == -200);

   std::vector<uint32_t> fromUint32;
   fromUint32.push_back(100);
   fromUint32.push_back(200);
   fromAgg.vectorUint32Field = fromUint32;
   CHECK(fromAgg.vectorUint32Field.Value()[0] == 100);
   CHECK(fromAgg.vectorUint32Field.Value()[1] == 200);

   std::vector<uint64_t> fromUint64;
   fromUint64.push_back(100);
   fromUint64.push_back(200);
   fromAgg.vectorUint64Field = fromUint64;
   CHECK(fromAgg.vectorUint64Field.Value()[0] == 100);
   CHECK(fromAgg.vectorUint64Field.Value()[1] == 200);

   std::vector<int64_t> fromInt64;
   fromInt64.push_back(-1000);
   fromInt64.push_back(-2000);
   fromAgg.vectorInt64Field = fromInt64;
   CHECK(fromAgg.vectorInt64Field.Value()[0] == -1000);
   CHECK(fromAgg.vectorInt64Field.Value()[1] == -2000);

   std::vector<double> fromDb;
   fromDb.push_back(99.00);
   fromDb.push_back(101.00);
   fromAgg.vectorDblField = fromDb;
   CHECK(fromAgg.vectorDblField.Value()[0] == 99.00);
   CHECK(fromAgg.vectorDblField.Value()[1] == 101.00);

   std::vector<std::string> fromStr;
   fromStr.push_back("Hello Team");
   fromStr.push_back("Hello World!");
   fromAgg.vectorStrField = fromStr;
   CHECK(fromAgg.vectorStrField.Value()[0] == "Hello Team");
   CHECK(fromAgg.vectorStrField.Value()[1] == "Hello World!");

   std::vector<bool> fromBo;
   fromBo.push_back(false);
   fromBo.push_back(true);
   fromAgg.vectorBoolField = fromBo;
   CHECK(fromAgg.vectorBoolField.Value()[0] == false);
   CHECK(fromAgg.vectorBoolField.Value()[1] == true);

}
//Tests Set Field Value - sets the current value back to default value for a field by using assignment.
TEST_CASE("SetFieldBackToDefaultValueUsingAssignment", "[test]")
{
   ReferenceAggregate a;
   a.boolField = true;
   CHECK(a.boolField.Value() == true);
   CHECK(a.boolField.State() == FieldStateEnum::Default);
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
   a.enumField.ComputedValueString("2");
   CHECK(a.enumField.Value() == 2);
   CHECK(a.enumField.State() == FieldStateEnum::Default);
}

//Tests Set Field Value - sets the current value for a field by using function.
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
   a.enumField.ComputedValueString("2");
   CHECK(a.enumField.Value() == ReferenceEnum::Average);
}

//Tests Set Vector Field Value - sets the current value for a Vector field by using function.
TEST_CASE("SetVectorFieldCurrentValueUsingFunction", "[test]")
{
   VectorFieldUnitTest fromAgg("1.0.0");
   std::vector<int32_t> fromInt32;
   fromInt32.push_back(-100);
   fromAgg.vectorInt32Field.Value(fromInt32);
   CHECK(fromAgg.vectorInt32Field.Value()[0] == -100);

   std::vector<uint32_t> fromUint32;
   fromUint32.push_back(100);
   fromAgg.vectorUint32Field.Value(fromUint32);
   CHECK(fromAgg.vectorUint32Field.Value()[0] == 100);

   std::vector<int64_t> fromInt64;
   fromInt64.push_back(-10000);
   fromAgg.vectorInt64Field.Value(fromInt64);
   CHECK(fromAgg.vectorInt64Field.Value()[0] == -10000);

   std::vector<uint64_t> fromUint64;
   fromUint64.push_back(100);
   fromAgg.vectorUint64Field.Value(fromUint64);
   CHECK(fromAgg.vectorUint64Field.Value()[0] == 100);

   std::vector<double_t> fromDb;
   fromDb.push_back(89.00);
   fromAgg.vectorDblField.Value(fromDb);
   CHECK(fromAgg.vectorDblField.Value()[0] == 89.00);

   std::vector<std::string> fromStr;
   fromStr.push_back("Hello Team");
   fromAgg.vectorStrField.Value(fromStr);
   CHECK(fromAgg.vectorStrField.Value()[0] == "Hello Team");

   std::vector<bool> fromBo;
   fromBo.push_back(true);
   fromAgg.vectorBoolField.Value(fromBo);
   CHECK(fromAgg.vectorBoolField.Value()[0] == true);


}

//Tests Set Field Value - sets the current value back to default value for a field by using function.
TEST_CASE("SetFieldBackToDefaultValueUsingFunction", "[test]")
{
   ReferenceAggregate a;
   a.boolField.Value(true);
   CHECK(a.boolField.Value() == true);
   CHECK(a.boolField.State() == FieldStateEnum::Default);
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
   a.enumField.ComputedValueString("2");
   CHECK(a.enumField.Value() == 2);
   CHECK(a.enumField.State() == FieldStateEnum::Default);
}

//Tests boolfield Value - sets the bool value for a field by using function.
TEST_CASE("BoolStringFunctions", "[test]")
{
   TestBaseFieldSerialization a;
   a.boolField.Value( true);
   CHECK("true" == a.boolField.ComputedValueString());
   a.boolField.Value(false);
   CHECK("false" == a.boolField.ComputedValueString());

   a.boolField.ComputedValueString("false");
   CHECK(a.boolField == false);
   a.boolField.ComputedValueString("true");
   CHECK(a.boolField == true);
}

//Set field value shall throw an exception if the field is not available in the current version of the aggregate.
TEST_CASE("ThrowsExceptionIfEnumSetFieldNotAvailable", "[test]")
{
   Sample1Aggregate a;
   CHECK(a.FieldEnumRo.State() == FieldStateEnum::Unavailable);
   CHECK_THROWS_AS(a.FieldEnumRo.ComputedValueString("1"), NotAbleToSet);
}

//Set field value shall throw an exception if the field is not available in the current version of the aggregate.
TEST_CASE("ThrowsExceptionIfSetFieldNotAvailable", "[test]")
{
   PlateletTemplateAggregate a ("1.0.0");
   CHECK(a.minYield.State()== FieldStateEnum::Unavailable);
   CHECK_THROWS_AS(a.minYield =2, NotAbleToSet);
}

//Set Vector field value shall throw an exception if the Vector field is not available in the current version of the aggregate.
TEST_CASE("ThrowsExceptionIfSetVectorFieldNotAvailable", "[test]")
{
   VectorFieldUnitTest a("1.0.0");
   std::vector<std::string> fromStr;
   fromStr.push_back("Hi");
   fromStr.push_back("Hello");

   CHECK(a.vectorVersion1only.State() == FieldStateEnum::Unavailable);
   CHECK_THROWS_AS(a.vectorStrField = fromStr, NotAbleToSet);
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
      std::string expected = "Bct::Workflow::Aggregates::NotAbleToSet: aggregate=class Bct::Workflow::Implementation::Sample1Aggregate fieldName=Field7c fieldState=Constant";
      std::string actual = exc.what();
      CHECK(actual == expected);
   }
}

// Tests set field value shall throw and exception if the field is marked as computedOnly.
TEST_CASE("ThrowsExceptionIfFieldComputeOnly", "[test]")
{
   Sample1Aggregate a("1.2.0");
   CHECK(a.Field7com.State() == FieldStateEnum::NotSet);
   CHECK_THROWS_AS(a.Field7com = 3, NotAbleToSet);  // throws on assignment since it is compute only
   try //Trying to set a computeOnly field
   {
      a.Field7com.Value(5);
   }
   catch (NotAbleToSet exc)
   {
      std::string expected = "Bct::Workflow::Aggregates::NotAbleToSet: aggregate=class Bct::Workflow::Implementation::Sample1Aggregate fieldName=Field7com fieldState=Computed";
      std::string actual = exc.what();
      CHECK(actual == expected);
   }
}


//Set vector field value shall allow changing a vector field to “nullable” which will set the state to “not set”..
TEST_CASE("NullableVectorField", "[test]")
{
   VectorFieldUnitTest a("1.0.0");
   a.vectorAggField.unset();
   CHECK(a.vectorAggField.State() == FieldStateEnum::NotSet);
   CHECK_THROWS_AS(a.vectorAggField.Value(), NotAbleToGet);
}

//Set vector field value shall allow changing a field to “nullable” which will set the state to “not set”..
TEST_CASE("NullableField", "[test]")
{
   Sample1Aggregate a;
   a.Field1.unset();
   CHECK(a.Field7.State() == FieldStateEnum::NotSet);
   CHECK_THROWS_AS(a.Field7.Value(), NotAbleToGet);
}

//Tests get Field state- gets the current state for a field.
TEST_CASE("GetCurrentFieldState", "[test]")
{
   ReferenceAggregate a;
   CHECK(a.boolField.Value() == true);
   CHECK(a.boolField.State() == FieldStateEnum::Default);
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

//Tests get Vector field state- gets the current state for a Vector field.
TEST_CASE("GetCurrentVectorFieldState", "[test]")
{
   VectorFieldUnitTest fromAgg("1.0.0");

   CHECK(fromAgg.vectorInt32Field.State() == FieldStateEnum::NotSet);
   CHECK(fromAgg.vectorUint32Field.State() == FieldStateEnum::NotSet);
   CHECK(fromAgg.vectorInt64Field.State() == FieldStateEnum::NotSet);
   CHECK(fromAgg.vectorUint64Field.State() == FieldStateEnum::NotSet);
   CHECK(fromAgg.vectorDblField.State() == FieldStateEnum::NotSet);
   CHECK(fromAgg.vectorStrField.State() == FieldStateEnum::NotSet);
   CHECK(fromAgg.vectorBoolField.State() == FieldStateEnum::NotSet);
  
   //CHECK(fromAgg.vectorEnumField.State() == FieldStateEnum::NotSet);
   //CHECK(fromAgg.vectorAggField.State() == FieldStateEnum::NotSet);


}
//Tests set field value - sets the new value for a field.
TEST_CASE("SetCurrentFieldState", "[test]")
{
   ReferenceAggregate a;
   a.boolField = false;
   CHECK(a.boolField.Value() == false);
   CHECK(a.boolField.State() == FieldStateEnum::Set);
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
   a.enumField.ComputedValueString("1");
   CHECK(a.enumField.State() == FieldStateEnum::Set);
}

//Tests set Vector field value - sets the new value for a Vector field.
TEST_CASE("SetCurrentVectorFieldState", "[test]")
{
   VectorFieldUnitTest fromAgg("1.0.0");
   std::vector<int32_t> fromInt32;
   fromInt32.push_back(-100);
   fromAgg.vectorInt32Field.Value(fromInt32);
   CHECK(fromAgg.vectorInt32Field.State() == FieldStateEnum::Set);

   std::vector<uint32_t> fromUint32;
   fromUint32.push_back(100);
   fromAgg.vectorUint32Field.Value(fromUint32);
   CHECK(fromAgg.vectorUint32Field.State() == FieldStateEnum::Set);

   std::vector<int64_t> fromInt64;
   fromInt64.push_back(-100000);
   fromAgg.vectorInt64Field.Value(fromInt64);
   CHECK(fromAgg.vectorInt64Field.State() == FieldStateEnum::Set);

   std::vector<uint64_t> fromUint64;
   fromUint64.push_back(100);
   fromAgg.vectorUint64Field.Value(fromUint64);
   CHECK(fromAgg.vectorUint64Field.State() == FieldStateEnum::Set);

   std::vector<double> fromDb;
   fromDb.push_back(1000.89);
   fromAgg.vectorDblField.Value(fromDb);
   CHECK(fromAgg.vectorDblField.State() == FieldStateEnum::Set);

   std::vector<std::string> fromStr;
   fromStr.push_back("Hi Team");
   fromAgg.vectorStrField.Value(fromStr);
   CHECK(fromAgg.vectorStrField.State() == FieldStateEnum::Set);

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
   CHECK(a.Field7com.State() == FieldStateEnum::NotSet);
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
TEST_CASE("ConvertVersion", "[test]")
{
   Sample1Aggregate a;
   a.convertToVersion("1.1.0");
   CHECK(a.getVersion() == "1.1.0");
}

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
      std::string message = "Bct::Workflow::Aggregates::NoSuchVersion: aggregate=class Bct::Workflow::Implementation::Sample1Aggregate requestedVersion=1.0.0.0";
      CHECK(ex.what() == message);

   }
}

// Tests the system shall include assess functions to determine if specified data is valid.
// Tests the system shall return a list of string ID values of failed rules if the data is not valid.
TEST_CASE("Assess", "[test]")
{
   Sample1Aggregate a;
   a.Field1 = 50.0;
   AssessmentResult res = a.Assess();
   CHECK(res.isSuccess());
   a.Field1 = 51.0;
   res = a.Assess();
   CHECK(res.isFailure());
   CHECK(res.getErrorIds().size() == 1);
   CHECK(res.getErrorIds()[0] == "aRuleStringId");
}

// Tests updates the values of any computed fields, as specified in the aggregate definition. 
TEST_CASE("UpdateComputedField", "[test]")
{
   Sample1Aggregate a;
   a.Field1 = 10;
   CHECK(a.Field1.Value() == 10);
   a.updateCalculatedFields();
   CHECK(a.Field1.Value() == 30.0);
   CHECK(a.Field1.State() == FieldStateEnum::Computed);
}
