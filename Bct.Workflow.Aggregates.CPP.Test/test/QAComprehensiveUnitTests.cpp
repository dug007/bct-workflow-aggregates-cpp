#include "ReferenceAggregate.h"
#include "ReferenceEnum.h"
#include "EnumField.h"
#include "Sample1Aggregate.h"
#include "PlateletTemplateAggregate.h"
#include "BaseAggregate.h"
#include "TestHelperBaseField.h"
#include "AbstractAggregate.h"

#include "catch.hpp"

using namespace Bct::Workflow::Aggregates;
using namespace Bct::Workflow::Implementation;
using namespace Bct::Workflow;

class VectorFieldAggregate : public BaseAggregate
{

public:
   VectorField<int32_t> vectorInt32Field;
   VectorField<double> vectorDblField;
   VectorField<std::string> vectorStrField;
   VectorField<ReferenceAggregate> vectorAggField;
   VectorField<uint32_t> vectorUint32Field;
   VectorField<int64_t> vectorInt64Field;
   VectorField<uint64_t> vectorUint64Field;
   VectorField<bool> vectorBoolField;
   VectorField<int64_t> vectorVersion0only;     // Added for vector unavailable unit tests
   VectorField<int64_t> vectorVersion1only;
   VectorField<bool> vectorVersion2only;

   VectorFieldAggregate(const std::string &version)
      :
      BaseAggregate(version),
      vectorInt32Field(0, this),
      vectorDblField(1, this),
      vectorStrField(2, this),
      vectorAggField(3, this),
      vectorVersion0only(4, this),
      vectorVersion1only(5, this),
      vectorVersion2only(6, this),
      vectorUint32Field(7, this),
      vectorInt64Field(8, this),
      vectorUint64Field(9, this),
      vectorBoolField(10, this)

   {
      FieldList().push_back(&vectorInt32Field);
      FieldList().push_back(&vectorDblField);
      FieldList().push_back(&vectorStrField);
      FieldList().push_back(&vectorAggField);
      FieldList().push_back(&vectorVersion0only);
      FieldList().push_back(&vectorVersion1only);
      FieldList().push_back(&vectorVersion2only);
      FieldList().push_back(&vectorUint32Field);
      FieldList().push_back(&vectorInt64Field);
      FieldList().push_back(&vectorUint64Field);
      FieldList().push_back(&vectorBoolField);

      syncVersion();
   }

   virtual AggregateMetaData &MetaData() const
   {
      return s_MetaData();
   };

   static AggregateMetaData & s_MetaData()
   {
      static AggregateMetaData tm;
      static bool initialized = false;

      if (!initialized)
      {
         tm.addField(0, "vectorInt32Field", Bct::Workflow::TypeEnum::ArrayType);
         tm.addField(1, "vectorDblField", Bct::Workflow::TypeEnum::ArrayType);
         tm.addField(2, "vectorStrField", Bct::Workflow::TypeEnum::ArrayType);
         tm.addField(3, "vectorAggField", Bct::Workflow::TypeEnum::ArrayType);
         tm.addField(4, "vectorVersion0only", Bct::Workflow::TypeEnum::ArrayType);
         tm.addField(5, "vectorVersion1only", Bct::Workflow::TypeEnum::ArrayType);
         tm.addField(6, "vectorVersion2only", Bct::Workflow::TypeEnum::ArrayType);
         tm.addField(7, "vectorUint32Field", Bct::Workflow::TypeEnum::ArrayType);
         tm.addField(8, "vectorInt64Field", Bct::Workflow::TypeEnum::ArrayType);
         tm.addField(9, "vectorUint64Field", Bct::Workflow::TypeEnum::ArrayType);

         tm.addVersion("1.0.0");
         tm.addVersion("1.1.0");
         tm.addVersion("1.2.0");

         tm.addFieldMetaToAllVersions(0, FieldStateEnum::NotSet, "notset");
         tm.addFieldMetaToAllVersions(1, FieldStateEnum::NotSet, "notset");
         tm.addFieldMetaToAllVersions(2, FieldStateEnum::NotSet, "notset");
         tm.addFieldMetaToAllVersions(3, FieldStateEnum::NotSet, "notset");
         tm.addFieldMeta(4, FieldStateEnum::NotSet, "notset").toVersion(0);
         tm.addFieldMeta(4, FieldStateEnum::Unavailable, "unavailable")
            .toVersion(1)
            .toVersion(2)
            ;
         tm.addFieldMeta(5, FieldStateEnum::Unavailable, "unavailable").toVersion(0);
         tm.addFieldMeta(5, FieldStateEnum::NotSet, "notset").toVersion(1);
         tm.addFieldMeta(5, FieldStateEnum::Unavailable, "unavailable").toVersion(2);

         tm.addFieldMeta(6, FieldStateEnum::Unavailable, "unavailable")
            .toVersion(0)
            .toVersion(1)
            ;
         tm.addFieldMeta(6, FieldStateEnum::NotSet, "notset").toVersion(2);
         tm.addFieldMetaToAllVersions(7, FieldStateEnum::NotSet, "notset");
         tm.addFieldMetaToAllVersions(8, FieldStateEnum::NotSet, "notset");
         tm.addFieldMetaToAllVersions(9, FieldStateEnum::NotSet, "notset");
         tm.addFieldMetaToAllVersions(10, FieldStateEnum::NotSet, "notset");
         initialized = true;
      }
      return tm;
   }
};

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
   ReferenceAggregate RefAgg1;

   CHECK(RefAgg1.boolField.Value() == true);
   CHECK(RefAgg1.int32Field.Value() == -1); 
   CHECK(RefAgg1.uint32Field.Value() == 1); 
   CHECK(RefAgg1.int64Field.Value() == -1); 
   CHECK(RefAgg1.uint64Field.Value() == 1); 
   CHECK(RefAgg1.doubleField.Value() == 1.0); 
   CHECK(RefAgg1.stringField.Value() == "hello world"); 
   CHECK(RefAgg1.enumField.Value() == 2);
   std::vector<int32_t> fromInt;
   fromInt.push_back(3);
   RefAgg1.vectorIntField = fromInt;
   CHECK(RefAgg1.vectorIntField.Value()[0] == 3);
}

// Tests get field value shall throw an exception if the field is not available in the current version of the aggregate.
TEST_CASE("ThrowsExceptionIfGetFieldNotAvailable", "[test]")
{
   Sample1Aggregate SamAgg1;

   CHECK(SamAgg1.FieldEnumRo.State() == FieldStateEnum::Unavailable);
   CHECK_THROWS_AS(SamAgg1.FieldEnumRo.Value(), NotAbleToGet);
}

// Tests get field value shall throw an exception if the field is not set in the current version of the aggregate.
TEST_CASE("ThrowsExceptionIfGetFieldNotSet", "[test]")
{
   Sample1Aggregate SamAgg2;

   CHECK(SamAgg2.Field7x.State() == FieldStateEnum::NotSet);
   CHECK_THROWS_AS(SamAgg2.Field7x.Value(), NotAbleToGet);
}

 //Tests get vector field value shall throw an exception if the vector field is not available in the current version of the aggregate.
TEST_CASE("ThrowsExceptionIfGetVecotrFieldNotAvailable", "[test]")
{
   VectorFieldAggregate VecAgg1 ("1.0.0");

   CHECK(VecAgg1.vectorVersion1only.State() == FieldStateEnum::Unavailable);
   CHECK_THROWS_AS(VecAgg1.vectorVersion1only.Value(), NotAbleToGet);
}

// Tests get vector field value shall throw an exception if the vector field is not set in the current version of the aggregate.
TEST_CASE("ThrowsExceptionIfGetVectorFieldNotSet", "[test]")
{
   ReferenceAggregate RefAgg2;

   CHECK(RefAgg2.vectorIntField.State() == FieldStateEnum::NotSet);
   CHECK_THROWS_AS(RefAgg2.vectorIntField.Value(), NotAbleToGet);
}

//This test ensure field assignment are correct
TEST_CASE("SetFieldCounterAssignCorrectly","[test]")
{
   ReferenceAggregate fromRefAgg;
   ReferenceAggregate toRefAgg;

   fromRefAgg.boolField = false; //set boolField twice to ensure FieldSetCounter increases twice
   fromRefAgg.boolField = false;
   toRefAgg.boolField = true;
   CHECK( toRefAgg.boolField.FieldSetCounter() != fromRefAgg.boolField.FieldSetCounter());
   toRefAgg.boolField = fromRefAgg.boolField;
   CHECK(toRefAgg.boolField == false);
   CHECK(toRefAgg.boolField.FieldSetCounter() == fromRefAgg.boolField.FieldSetCounter());

   fromRefAgg.int32Field = -200;
   fromRefAgg.int32Field = -200;
   toRefAgg.int32Field = -201;
   CHECK(toRefAgg.int32Field.FieldSetCounter() != fromRefAgg.int32Field.FieldSetCounter());
   toRefAgg.int32Field = fromRefAgg.int32Field;
   CHECK(toRefAgg.int32Field == -200);
   CHECK(toRefAgg.int32Field.FieldSetCounter() == fromRefAgg.int32Field.FieldSetCounter());

   fromRefAgg.uint32Field = -2000;
   fromRefAgg.uint32Field = -2000;
   toRefAgg.uint32Field = -2010;
   CHECK(toRefAgg.uint32Field.FieldSetCounter() != fromRefAgg.uint32Field.FieldSetCounter());
   toRefAgg.uint32Field = fromRefAgg.uint32Field;
   CHECK(toRefAgg.uint32Field == -2000);
   CHECK(toRefAgg.uint32Field.FieldSetCounter() == fromRefAgg.uint32Field.FieldSetCounter());

   fromRefAgg.int64Field = -300;
   fromRefAgg.int64Field = -300;
   toRefAgg.int64Field = -301;
   CHECK(toRefAgg.int64Field.FieldSetCounter() != fromRefAgg.int64Field.FieldSetCounter());
   toRefAgg.int64Field = fromRefAgg.int64Field;
   CHECK(toRefAgg.int64Field == -300);
   CHECK(toRefAgg.int64Field.FieldSetCounter() == fromRefAgg.int64Field.FieldSetCounter());

   fromRefAgg.uint64Field = 3000;
   fromRefAgg.uint64Field = 3000;
   toRefAgg.uint64Field = 3010;
   CHECK(toRefAgg.uint64Field.FieldSetCounter() != fromRefAgg.uint64Field.FieldSetCounter());
   toRefAgg.uint64Field = fromRefAgg.uint64Field;
   CHECK(toRefAgg.uint64Field == 3000.00);
   CHECK(toRefAgg.uint64Field.FieldSetCounter() == fromRefAgg.uint64Field.FieldSetCounter());

   fromRefAgg.doubleField = 3000.00;
   fromRefAgg.doubleField = 3000.00;
   toRefAgg.doubleField = 3010.00;
   CHECK(toRefAgg.doubleField.FieldSetCounter() != fromRefAgg.doubleField.FieldSetCounter());
   toRefAgg.doubleField = fromRefAgg.doubleField;
   CHECK(toRefAgg.doubleField == 3000.00);
   CHECK(toRefAgg.doubleField.FieldSetCounter() == fromRefAgg.doubleField.FieldSetCounter());

   fromRefAgg.enumField = ReferenceEnum::Poor;
   fromRefAgg.enumField = ReferenceEnum::Poor;
   toRefAgg.enumField = ReferenceEnum::VeryPoor;
   CHECK(toRefAgg.enumField.FieldSetCounter() != fromRefAgg.enumField.FieldSetCounter());
   toRefAgg.enumField = fromRefAgg.enumField;
   CHECK(toRefAgg.enumField == ReferenceEnum::Poor);
   CHECK(toRefAgg.enumField.FieldSetCounter() == fromRefAgg.enumField.FieldSetCounter());

   fromRefAgg.stringField = "happy";
   fromRefAgg.stringField = "happy";
   toRefAgg.stringField = "days";
   CHECK(toRefAgg.stringField.FieldSetCounter() != fromRefAgg.stringField.FieldSetCounter());
   toRefAgg.stringField = fromRefAgg.stringField;
   CHECK((std::string)toRefAgg.stringField == "happy");
   CHECK(toRefAgg.stringField.FieldSetCounter() == fromRefAgg.stringField.FieldSetCounter());
}

//This test ensure field assignment are correct
TEST_CASE("FieldAssigmentDoesNotThrowExceiption", "[test]")
{
   Sample1Aggregate fromSamAgg;
   Sample1Aggregate toSamAgg;

   // Just make sure assignment does not throw exception on read only fields.
   toSamAgg.FieldEnumRo = fromSamAgg.FieldEnumRo;
   toSamAgg.FieldStringro = fromSamAgg.FieldStringro;
   toSamAgg.Field7ro = fromSamAgg.Field7ro;
}

//Tests Set Field Value - sets the current value for a field by using assignment.
TEST_CASE("SetFieldCurrentValueUsingAssignment", "[test]")
{
   ReferenceAggregate RefAgg3 ("v1.0.0");

   RefAgg3.boolField = false; 
   CHECK(RefAgg3.boolField.Value() == false); 
   RefAgg3.int32Field = -2;
   CHECK(RefAgg3.int32Field.Value() == -2);
   RefAgg3.uint32Field = 5;
   CHECK(RefAgg3.uint32Field.Value() == 5);
   RefAgg3.int64Field = -10;
   CHECK(RefAgg3.int64Field.Value() == -10);
   RefAgg3.uint64Field = 11;
   CHECK(RefAgg3.uint64Field.Value() == 11);
   RefAgg3.doubleField = 20.0;
   CHECK(RefAgg3.doubleField.Value() == 20.0);
   RefAgg3.stringField = "hello team";
   CHECK(RefAgg3.stringField.Value() == "hello team");
   RefAgg3.enumField = ReferenceEnum::VeryGood;
   CHECK(RefAgg3.enumField.Value() == ReferenceEnum::VeryGood);
   RefAgg3.enumField = ReferenceEnum::Good;
   CHECK(RefAgg3.enumField.Value() == ReferenceEnum::Good);
   RefAgg3.enumField = ReferenceEnum::Average;
   CHECK(RefAgg3.enumField.Value() == ReferenceEnum::Average);
   RefAgg3.enumField = ReferenceEnum::BelowAverage;
   CHECK(RefAgg3.enumField.Value() == ReferenceEnum::BelowAverage);
   RefAgg3.enumField = ReferenceEnum::Poor;
   CHECK(RefAgg3.enumField.Value() == ReferenceEnum::Poor);
   RefAgg3.enumField = ReferenceEnum::VeryPoor;
   CHECK(RefAgg3.enumField.Value() == ReferenceEnum::VeryPoor);
   RefAgg3.enumField.ComputedValueString("0");
   CHECK(RefAgg3.enumField == ReferenceEnum::VeryGood);
   RefAgg3.enumField.ComputedValueString("1");
   CHECK(RefAgg3.enumField == ReferenceEnum::Good);
   RefAgg3.enumField.ComputedValueString("2");
   CHECK(RefAgg3.enumField == ReferenceEnum::Average);
   RefAgg3.enumField.ComputedValueString("4");
   CHECK(RefAgg3.enumField == ReferenceEnum::BelowAverage);
   RefAgg3.enumField.ComputedValueString("8");
   CHECK(RefAgg3.enumField == ReferenceEnum::Poor);
   RefAgg3.enumField.ComputedValueString("16");
   CHECK(RefAgg3.enumField == ReferenceEnum::VeryPoor);
}

//Tests Set Vector Field Value - sets the current value for a vector field by using assignment.
TEST_CASE("SetVectorFieldUsingAssignment", "[test]")
{
   VectorFieldAggregate VecAgg2("1.0.0");

   std::vector<int32_t> fromInt32;
   fromInt32.push_back(-100);
   fromInt32.push_back(-200);
   VecAgg2.vectorInt32Field = fromInt32;
   CHECK(VecAgg2.vectorInt32Field.Value()[0] == -100);
   CHECK(VecAgg2.vectorInt32Field.Value()[1] == -200);

   std::vector<uint32_t> fromUint32;
   fromUint32.push_back(100);
   fromUint32.push_back(200);
   VecAgg2.vectorUint32Field = fromUint32;
   CHECK(VecAgg2.vectorUint32Field.Value()[0] == 100);
   CHECK(VecAgg2.vectorUint32Field.Value()[1] == 200);

   std::vector<uint64_t> fromUint64;
   fromUint64.push_back(100);
   fromUint64.push_back(200);
   VecAgg2.vectorUint64Field = fromUint64;
   CHECK(VecAgg2.vectorUint64Field.Value()[0] == 100);
   CHECK(VecAgg2.vectorUint64Field.Value()[1] == 200);

   std::vector<int64_t> fromInt64;
   fromInt64.push_back(-1000);
   fromInt64.push_back(-2000);
   VecAgg2.vectorInt64Field = fromInt64;
   CHECK(VecAgg2.vectorInt64Field.Value()[0] == -1000);
   CHECK(VecAgg2.vectorInt64Field.Value()[1] == -2000);

   std::vector<double> fromDb;
   fromDb.push_back(99.00);
   fromDb.push_back(101.00);
   VecAgg2.vectorDblField = fromDb;
   CHECK(VecAgg2.vectorDblField.Value()[0] == 99.00);
   CHECK(VecAgg2.vectorDblField.Value()[1] == 101.00);

   std::vector<std::string> fromStr;
   fromStr.push_back("Hello Team");
   fromStr.push_back("Hello World!");
   VecAgg2.vectorStrField = fromStr;
   CHECK(VecAgg2.vectorStrField.Value()[0] == "Hello Team");
   CHECK(VecAgg2.vectorStrField.Value()[1] == "Hello World!");

   std::vector<bool> fromBo;
   fromBo.push_back(false);
   fromBo.push_back(true);
   VecAgg2.vectorBoolField = fromBo;
   CHECK(VecAgg2.vectorBoolField.Value()[0] == false);
   CHECK(VecAgg2.vectorBoolField.Value()[1] == true);
}

//Tests Set Field Value - sets the current value back to default value for a field by using assignment.
TEST_CASE("SetFieldBackToDefaultValueUsingAssignment", "[test]")
{
   ReferenceAggregate RefAgg4;

   RefAgg4.boolField = true;
   CHECK(RefAgg4.boolField.Value() == true);
   CHECK(RefAgg4.boolField.State() == FieldStateEnum::Default);
   RefAgg4.int32Field = -1;
   CHECK(RefAgg4.int32Field.Value() == -1);
   CHECK(RefAgg4.int32Field.State() == FieldStateEnum::Default);
   RefAgg4.uint32Field = 1;
   CHECK(RefAgg4.uint32Field.Value() == 1);
   CHECK(RefAgg4.uint32Field.State() == FieldStateEnum::Default);
   RefAgg4.int64Field = -1;
   CHECK(RefAgg4.int64Field.Value() == -1);
   CHECK(RefAgg4.int64Field.State() == FieldStateEnum::Default);
   RefAgg4.uint64Field = 1;
   CHECK(RefAgg4.uint64Field.Value() == 1);
   CHECK(RefAgg4.uint64Field.State() == FieldStateEnum::Default);
   RefAgg4.doubleField = 1.0;
   CHECK(RefAgg4.doubleField.Value() == 1.0);
   CHECK(RefAgg4.doubleField.State() == FieldStateEnum::Default);
   RefAgg4.stringField = "hello world";
   CHECK(RefAgg4.stringField.Value() == "hello world");
   CHECK(RefAgg4.stringField.State() == FieldStateEnum::Default);
   RefAgg4.enumField.ComputedValueString("2");
   CHECK(RefAgg4.enumField.Value() == 2);
   CHECK(RefAgg4.enumField.State() == FieldStateEnum::Default);
}

//Tests Set Field Value - sets the current value for a field by using function.
TEST_CASE("SetFieldCurrentValueUsingFunction", "[test]")
{
   ReferenceAggregate RefAgg5;

   RefAgg5.boolField.Value(false);
   CHECK(RefAgg5.boolField.Value() == false);
   RefAgg5.int32Field.Value(-10);
   CHECK(RefAgg5.int32Field.Value() == -10);
   RefAgg5.uint32Field.Value(150);
   CHECK(RefAgg5.uint32Field.Value() == 150);
   RefAgg5.int64Field.Value(-100);
   CHECK(RefAgg5.int64Field.Value() == -100);
   RefAgg5.uint64Field.Value(1500);
   CHECK(RefAgg5.uint64Field.Value() == 1500);
   RefAgg5.doubleField.Value(15.0);
   CHECK(RefAgg5.doubleField.Value() == 15.0);
   RefAgg5.stringField.Value("hello team");
   CHECK(RefAgg5.stringField.Value() == "hello team");
   RefAgg5.enumField.ComputedValueString("2");
   CHECK(RefAgg5.enumField.Value() == ReferenceEnum::Average);
}

//Tests Set Vector Field Value - sets the current value for a Vector field by using function.
TEST_CASE("SetVectorFieldCurrentValueUsingFunction", "[test]")
{
   VectorFieldAggregate VecAgg3("1.0.0");

   std::vector<int32_t> fromInt32;
   fromInt32.push_back(-100);
   VecAgg3.vectorInt32Field.Value(fromInt32);
   CHECK(VecAgg3.vectorInt32Field.Value()[0] == -100);

   std::vector<uint32_t> fromUint32;
   fromUint32.push_back(100);
   VecAgg3.vectorUint32Field.Value(fromUint32);
   CHECK(VecAgg3.vectorUint32Field.Value()[0] == 100);

   std::vector<int64_t> fromInt64;
   fromInt64.push_back(-10000);
   VecAgg3.vectorInt64Field.Value(fromInt64);
   CHECK(VecAgg3.vectorInt64Field.Value()[0] == -10000);

   std::vector<uint64_t> fromUint64;
   fromUint64.push_back(100);
   VecAgg3.vectorUint64Field.Value(fromUint64);
   CHECK(VecAgg3.vectorUint64Field.Value()[0] == 100);

   std::vector<double> fromDb;
   fromDb.push_back(89.00);
   VecAgg3.vectorDblField.Value(fromDb);
   CHECK(VecAgg3.vectorDblField.Value()[0] == 89.00);

   std::vector<std::string> fromStr;
   fromStr.push_back("Hello Team");
   VecAgg3.vectorStrField.Value(fromStr);
   CHECK(VecAgg3.vectorStrField.Value()[0] == "Hello Team");

   std::vector<bool> fromBo;
   fromBo.push_back(true);
   VecAgg3.vectorBoolField.Value(fromBo);
   CHECK(VecAgg3.vectorBoolField.Value()[0] == true);
}

//Tests Set Field Value - sets the current value back to default value for a field by using function.
TEST_CASE("SetFieldBackToDefaultValueUsingFunction", "[test]")
{
   ReferenceAggregate RefAgg6;

   RefAgg6.boolField.Value(true);
   CHECK(RefAgg6.boolField.Value() == true);
   CHECK(RefAgg6.boolField.State() == FieldStateEnum::Default);
   RefAgg6.int32Field.Value(-1);
   CHECK(RefAgg6.int32Field.Value() == -1);
   CHECK(RefAgg6.int32Field.State() == FieldStateEnum::Default);
   RefAgg6.uint32Field.Value(1);
   CHECK(RefAgg6.uint32Field.Value() == 1);
   CHECK(RefAgg6.uint32Field.State() == FieldStateEnum::Default);
   RefAgg6.int64Field.Value(-1);
   CHECK(RefAgg6.int64Field.Value() == -1);
   CHECK(RefAgg6.int64Field.State() == FieldStateEnum::Default);
   RefAgg6.uint64Field.Value(1);
   CHECK(RefAgg6.uint64Field.Value() == 1);
   CHECK(RefAgg6.uint64Field.State() == FieldStateEnum::Default);
   RefAgg6.doubleField.Value(1.0);
   CHECK(RefAgg6.doubleField.Value() == 1.0);
   CHECK(RefAgg6.doubleField.State() == FieldStateEnum::Default);
   RefAgg6.stringField.Value("hello world");
   CHECK(RefAgg6.stringField.Value() == "hello world");
   CHECK(RefAgg6.stringField.State() == FieldStateEnum::Default);
   RefAgg6.enumField.ComputedValueString("2");
   CHECK(RefAgg6.enumField.Value() == 2);
   CHECK(RefAgg6.enumField.State() == FieldStateEnum::Default);
}

//Tests boolfield Value - sets the bool value for a field by using function.
TEST_CASE("BoolStringFunctions", "[test]")
{
   TestBaseFieldSerialization TesBas1;

   //TesBas1.boolField.Value( true);
   //CHECK("true" == TesBas1.boolField.ComputedValueString());
   //TesBas1.boolField.Value(false);
   //CHECK("false" == TesBas1.boolField.ComputedValueString());

   //TesBas1.boolField.ComputedValueString("false");
   //CHECK(TesBas1.boolField == false);
   //TesBas1.boolField.ComputedValueString("true");
   //CHECK(TesBas1.boolField == true);
}

//Set field value shall throw an exception if the field is not available in the current version of the aggregate.
TEST_CASE("ThrowsExceptionIfEnumSetFieldNotAvailable", "[test]")
{
   Sample1Aggregate SamAgg3;

   CHECK(SamAgg3.FieldEnumRo.State() == FieldStateEnum::Unavailable);
   CHECK_THROWS_AS(SamAgg3.FieldEnumRo.ComputedValueString("1"), NotAbleToSet);
}

//Set field value shall throw an exception if the field is not available in the current version of the aggregate.
TEST_CASE("ThrowsExceptionIfSetFieldNotAvailable", "[test]")
{
   PlateletTemplateAggregate PltAgg1 ("1.0.0");

   CHECK(PltAgg1.minYield.State()== FieldStateEnum::Unavailable);
   CHECK_THROWS_AS(PltAgg1.minYield =2, NotAbleToSet);
}

//Set Vector field value shall throw an exception if the Vector field is not available in the current version of the aggregate.
TEST_CASE("ThrowsExceptionIfSetVectorFieldNotAvailable", "[test]")
{
   VectorFieldAggregate VecAgg4("1.0.0");

   std::vector<int64_t> fromInt64;
   fromInt64.push_back(100);
   fromInt64.push_back(200);
   CHECK(VecAgg4.vectorVersion1only.State() == FieldStateEnum::Unavailable);
   CHECK_THROWS_AS(VecAgg4.vectorVersion1only = fromInt64, NotAbleToSet);
}

//Tests set field value shall throw an exception if the field is marked as constant in the current version of the aggregate.
TEST_CASE("ThrowsExceptionIfFieldConstant", "[test]")
{
   Sample1Aggregate SamAgg4;

   CHECK(SamAgg4.Field7c.State() == FieldStateEnum::Constant);
   CHECK_THROWS_AS(SamAgg4.Field7c = 3, NotAbleToSet);  // throws on assignment
   CHECK_THROWS_AS(SamAgg4.Field7c.Value(3), NotAbleToSet);  // throws on set
   try //Trying to set a constant field
   {
      SamAgg4.Field7c.Value(5);
   }
   catch (NotAbleToSet &exc)
   {
      std::string expected = "Bct::Workflow::Aggregates::NotAbleToSet: aggregate=class Bct::Workflow::Implementation::Sample1Aggregate fieldName=Field7c fieldState=Constant";
      std::string actual = exc.what();
      CHECK(actual == expected);
   }
}

// Tests set field value shall throw and exception if the field is marked as computedOnly.
TEST_CASE("ThrowsExceptionIfFieldComputeOnly", "[test]")
{
   Sample1Aggregate SamAgg5("1.2.0");

   CHECK(SamAgg5.Field7com.State() == FieldStateEnum::NotSet);
   CHECK_THROWS_AS(SamAgg5.Field7com = 3, NotAbleToSet);  // throws on assignment since it is compute only
   try //Trying to set a computeOnly field
   {
      SamAgg5.Field7com.Value(5);
   }
   catch (NotAbleToSet &exc)
   {
      std::string expected = "Bct::Workflow::Aggregates::NotAbleToSet: aggregate=class Bct::Workflow::Implementation::Sample1Aggregate fieldName=Field7com fieldState=Computed";
      std::string actual = exc.what();
      CHECK(actual == expected);
   }
}

//Set vector field value shall allow changing a vector field to “nullable” which will set the state to “not set”..
TEST_CASE("NullableVectorField", "[test]")
{
   VectorFieldAggregate VecAgg5("1.0.0");

   VecAgg5.vectorAggField.unset();
   CHECK(VecAgg5.vectorAggField.State() == FieldStateEnum::NotSet);
   CHECK_THROWS_AS(VecAgg5.vectorAggField.Value(), NotAbleToGet);
}

//Set vector field value shall allow changing a field to “nullable” which will set the state to “not set”..
TEST_CASE("NullableField", "[test]")
{
   ReferenceAggregate RefAgg7;

   RefAgg7.int32Field.unset();
   CHECK(RefAgg7.int32Field.State() == FieldStateEnum::NotSet);
   CHECK_THROWS_AS(RefAgg7.int32Field.Value(), NotAbleToGet);
}

//Tests get Field state- gets the current state for a field.
TEST_CASE("GetCurrentFieldState", "[test]")
{
   ReferenceAggregate RefAgg8;

   CHECK(RefAgg8.boolField.Value() == true);
   CHECK(RefAgg8.boolField.State() == FieldStateEnum::Default);
   CHECK(RefAgg8.int32Field.Value() == -1);
   CHECK(RefAgg8.int32Field.State() == FieldStateEnum::Default);
   CHECK(RefAgg8.uint32Field.Value() == 1);
   CHECK(RefAgg8.uint32Field.State() == FieldStateEnum::Default);
   CHECK(RefAgg8.int64Field.Value() == -1);
   CHECK(RefAgg8.int64Field.State() == FieldStateEnum::Default);
   CHECK(RefAgg8.uint64Field.Value() == 1);
   CHECK(RefAgg8.uint64Field.State() == FieldStateEnum::Default);
   CHECK(RefAgg8.doubleField.Value() == 1.0);
   CHECK(RefAgg8.doubleField.State() == FieldStateEnum::Default);
   CHECK(RefAgg8.stringField.Value() == "hello world");
   CHECK(RefAgg8.stringField.State() == FieldStateEnum::Default);
   CHECK(RefAgg8.enumField.Value() == 2);
   CHECK(RefAgg8.enumField.State() == FieldStateEnum::Default);
}

//Tests get Vector field state- gets the current state for a Vector field.
TEST_CASE("GetCurrentVectorFieldState", "[test]")
{
   VectorFieldAggregate VecAgg6("1.0.0");

   CHECK(VecAgg6.vectorInt32Field.State() == FieldStateEnum::NotSet);
   CHECK(VecAgg6.vectorUint32Field.State() == FieldStateEnum::NotSet);
   CHECK(VecAgg6.vectorInt64Field.State() == FieldStateEnum::NotSet);
   CHECK(VecAgg6.vectorUint64Field.State() == FieldStateEnum::NotSet);
   CHECK(VecAgg6.vectorDblField.State() == FieldStateEnum::NotSet);
   CHECK(VecAgg6.vectorStrField.State() == FieldStateEnum::NotSet);
   CHECK(VecAgg6.vectorBoolField.State() == FieldStateEnum::NotSet);
}
//Tests set field value - sets the new value for a field.
TEST_CASE("SetCurrentFieldState", "[test]")
{
   ReferenceAggregate RefAgg9;

   RefAgg9.boolField = false;
   CHECK(RefAgg9.boolField.Value() == false);
   CHECK(RefAgg9.boolField.State() == FieldStateEnum::Set);
   RefAgg9.int32Field = -10;
   CHECK(RefAgg9.int32Field.State() == FieldStateEnum::Set);
   RefAgg9.uint32Field = 200;
   CHECK(RefAgg9.uint32Field.State() == FieldStateEnum::Set);
   RefAgg9.int64Field = -1000;
   CHECK(RefAgg9.int64Field.State() == FieldStateEnum::Set);
   RefAgg9.uint64Field = 200;
   CHECK(RefAgg9.uint64Field.State() == FieldStateEnum::Set);
   RefAgg9.doubleField = 200.0;
   CHECK(RefAgg9.doubleField.State() == FieldStateEnum::Set);
   RefAgg9.stringField = "Hi team";
   CHECK(RefAgg9.uint64Field.State() == FieldStateEnum::Set);
   RefAgg9.enumField.ComputedValueString("1");
   CHECK(RefAgg9.enumField.State() == FieldStateEnum::Set);
}

//Tests set Vector field value - sets the new value for a Vector field.
TEST_CASE("SetCurrentVectorFieldState", "[test]")
{
   VectorFieldAggregate VecAgg7("1.0.0");

   std::vector<int32_t> fromInt32;
   fromInt32.push_back(-100);
   VecAgg7.vectorInt32Field.Value(fromInt32);
   CHECK(VecAgg7.vectorInt32Field.State() == FieldStateEnum::Set);

   std::vector<uint32_t> fromUint32;
   fromUint32.push_back(100);
   VecAgg7.vectorUint32Field.Value(fromUint32);
   CHECK(VecAgg7.vectorUint32Field.State() == FieldStateEnum::Set);

   std::vector<int64_t> fromInt64;
   fromInt64.push_back(-100000);
   VecAgg7.vectorInt64Field.Value(fromInt64);
   CHECK(VecAgg7.vectorInt64Field.State() == FieldStateEnum::Set);

   std::vector<uint64_t> fromUint64;
   fromUint64.push_back(100);
   VecAgg7.vectorUint64Field.Value(fromUint64);
   CHECK(VecAgg7.vectorUint64Field.State() == FieldStateEnum::Set);

   std::vector<double> fromDb;
   fromDb.push_back(1000.89);
   VecAgg7.vectorDblField.Value(fromDb);
   CHECK(VecAgg7.vectorDblField.State() == FieldStateEnum::Set);

   std::vector<std::string> fromStr;
   fromStr.push_back("Hi Team");
   VecAgg7.vectorStrField.Value(fromStr);
   CHECK(VecAgg7.vectorStrField.State() == FieldStateEnum::Set);
}

//Tests get field state- gets the version 1.0.0 state for a field.
TEST_CASE("GetFieldStateVersion0", "[test]")
{
   Sample1Aggregate SamAgg6("1.0.0");

   CHECK(SamAgg6.Field1.State() == FieldStateEnum::NotSet);
   CHECK(SamAgg6.Field7.State() == FieldStateEnum::NotSet);
   CHECK(SamAgg6.Field7ro.State() == FieldStateEnum::NotSet);
   CHECK(SamAgg6.Field7c.State() == FieldStateEnum::NotSet);
   CHECK(SamAgg6.Field7d.State() == FieldStateEnum::NotSet);
   CHECK(SamAgg6.Field7x.State() == FieldStateEnum::NotSet);
   CHECK(SamAgg6.Field7com.State() == FieldStateEnum::NotSet);
   CHECK(SamAgg6.FieldEnum.State() == FieldStateEnum::Default);
   CHECK(SamAgg6.FieldEnumRo.State() == FieldStateEnum::Unavailable);
}

//Tests get field state- gets the version 1.1.0 state for a field.
TEST_CASE("GetFieldStateVersion1", "[test]")
{
   Sample1Aggregate SamAgg7("1.1.0");

   CHECK(SamAgg7.Field1.State() == FieldStateEnum::NotSet);
   CHECK(SamAgg7.Field7.State() == FieldStateEnum::NotSet);
   CHECK(SamAgg7.Field7ro.State() == FieldStateEnum::NotSet);
   CHECK(SamAgg7.Field7c.State() == FieldStateEnum::NotSet);
   CHECK(SamAgg7.Field7d.State() == FieldStateEnum::NotSet);
   CHECK(SamAgg7.Field7x.State() == FieldStateEnum::NotSet);
   CHECK(SamAgg7.Field7com.State() == FieldStateEnum::NotSet);
   CHECK(SamAgg7.FieldEnum.State() == FieldStateEnum::Default);
   CHECK(SamAgg7.FieldEnumRo.State() == FieldStateEnum::Unavailable);
}

//Tests get field state- gets the version 1.1.0 state for a field.
TEST_CASE("GetFieldStateVersion2", "[test]")
{
   Sample1Aggregate SamAgg8("1.2.0");

   CHECK(SamAgg8.Field1.State() == FieldStateEnum::NotSet);
   CHECK(SamAgg8.Field7.State() == FieldStateEnum::NotSet);
   CHECK(SamAgg8.Field7ro.State() == FieldStateEnum::Constant);
   CHECK(SamAgg8.Field7c.State() == FieldStateEnum::Constant);
   CHECK(SamAgg8.Field7d.State() == FieldStateEnum::Default);
   CHECK(SamAgg8.Field7x.State() == FieldStateEnum::NotSet);
   CHECK(SamAgg8.Field7com.State() == FieldStateEnum::NotSet);
   CHECK(SamAgg8.FieldEnum.State() == FieldStateEnum::Default);
   CHECK(SamAgg8.FieldEnumRo.State() == FieldStateEnum::Unavailable);
}

//Tests GetVersion – Returns the current version of an aggregate.
TEST_CASE("GetVersion", "[test]")
{
   Sample1Aggregate SamAgg9;

   CHECK(SamAgg9.getVersion() == "1.2.0");
}

// Tests Convert Version – Converts the aggregate to the specified version.
TEST_CASE("ConvertVersion", "[test]")
{
   Sample1Aggregate SamAgg10;

   SamAgg10.convertToVersion("1.1.0");
   CHECK(SamAgg10.getVersion() == "1.1.0");
}

// Test the method shall throw an exception if the specified version is not defined
TEST_CASE("ThrowExceptionNoSuchVersion", "[test]")
{
   try
   {
      Sample1Aggregate SamAgg11("1.0.0.0");
   }
   catch (NoSuchVersion &ex)
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
   Sample1Aggregate SamAgg12;

   SamAgg12.Field1 = 50.0;
   AssessmentResult res = SamAgg12.Assess();
   CHECK(res.isSuccess());
   SamAgg12.Field1 = 51.0;
   res = SamAgg12.Assess();
   CHECK(res.isFailure());
   CHECK(res.getErrorIds().size() == 1);
   CHECK(res.getErrorIds()[0] == "aRuleStringId");
}

// Tests updates the values of any computed fields, as specified in the aggregate definition. 
TEST_CASE("UpdateComputedField", "[test]")
{
   Sample1Aggregate SamAgg13;

   SamAgg13.Field1 = 10;
   CHECK(SamAgg13.Field1.Value() == 10);
   SamAgg13.updateCalculatedFields();
   CHECK(SamAgg13.Field1.Value() == 30.0);
   CHECK(SamAgg13.Field1.State() == FieldStateEnum::Computed);
}
