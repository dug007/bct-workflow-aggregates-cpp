#include "Sample1Aggregate.h"
#include "ReferenceAggregate.h"
#include "AggregateMetaData.h"
#include "FluentMeta.h"
#include "FieldMeta.h"
#include "BaseAggregate.h"
#include "BaseField.h"
#include "VectorField.h"
#include "StringField.h"
#include "EnumField.h"
#include "TypeEnum.h"


#include "catch.hpp"

using namespace Bct::Workflow::Aggregates;
using namespace Bct::Workflow::Implementation;
using namespace Bct::Workflow;

class TestVectorFieldAggregate : public BaseAggregate
{

public:
   VectorField<int32_t> vectorInt32Field;
   VectorField<double> vectorDblField;
   VectorField<std::string> vectorStrField;
   VectorField<ReferenceAggregate> vectorAggField;
   VectorField<int64_t> vectorVersion0only;     // Added for vector unavailable unit tests
   VectorField<int64_t> vectorVersion1only;
   VectorField<bool> vectorVersion2only;

   TestVectorFieldAggregate(const std::string &version)
      :
      BaseAggregate(version),
      vectorInt32Field(0, this),
      vectorDblField(1, this),
      vectorStrField(2, this),
      vectorAggField(3, this),
      vectorVersion0only(4, this),
      vectorVersion1only(5, this),
      vectorVersion2only(6, this)
   {
      FieldList().push_back(&vectorInt32Field);
      FieldList().push_back(&vectorDblField);
      FieldList().push_back(&vectorStrField);
      FieldList().push_back(&vectorAggField);
      FieldList().push_back(&vectorVersion0only);
      FieldList().push_back(&vectorVersion1only);
      FieldList().push_back(&vectorVersion2only);

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
         initialized = true;
      }
      return tm;
   }
};


/// <summary>
/// This tests vector field.
/// </summary>
TEST_CASE("VectorFieldUnitTests", "[test]")
{
   // Arrange (initial)
   TestVectorFieldAggregate t0("1.0.0");
   TestVectorFieldAggregate t0a("1.0.0");
   TestVectorFieldAggregate t1("1.1.0");
   TestVectorFieldAggregate t2("1.2.0");

   // assert versions all checkout
   CHECK(t0.getVersion() == "1.0.0");
   CHECK(t1.getVersion() == "1.1.0");
   CHECK(t2.getVersion() == "1.2.0");

   // assert no values yet on vector fields
   CHECK(!t0.vectorInt32Field.hasValue());
   CHECK(!t0.vectorDblField.hasValue());
   CHECK(!t0.vectorStrField.hasValue());
   CHECK(!t0.vectorAggField.hasValue());

   // arrange some external vectors for testing
   std::vector<int32_t> fromInt;
   fromInt.push_back(1);
   fromInt.push_back(2);

   std::vector<double> fromDbl;
   fromDbl.push_back(1.0);
   fromDbl.push_back(2.0);

   std::vector<std::string> fromStr;
   fromStr.push_back("hi");
   fromStr.push_back("there");

   // arrange assignment fromInt external vectors
   t0.vectorInt32Field = fromInt;
   t0.vectorDblField = fromDbl;
   t0.vectorStrField = fromStr;

   // assert that vectors now have correct values and size
   CHECK(t0.vectorInt32Field.hasValue());
   CHECK(t0.vectorDblField.hasValue());
   CHECK(t0.vectorStrField.hasValue());
   CHECK(t0.vectorInt32Field.Value()[0] == 1);
   CHECK(t0.vectorDblField.Value()[0] == 1.0);
   CHECK(t0.vectorStrField.Value()[0] == "hi");
   CHECK(t0.vectorInt32Field.FieldSetCounter() == 1);
   CHECK(t0.vectorDblField.FieldSetCounter() == 2);
   CHECK(t0.vectorStrField.FieldSetCounter() == 3);
   CHECK(t0.vectorInt32Field.Value().size() == 2);
   CHECK(t0.vectorDblField.Value().size() == 2);
   CHECK(t0.vectorStrField.Value().size() == 2);

   // make sure fromInt and field vectors are independent
   fromInt.push_back(3);
   fromDbl.push_back(3.0);
   fromStr.push_back("again");
   CHECK(t0.vectorInt32Field.Value().size() == 2);
   CHECK(t0.vectorDblField.Value().size() == 2);
   CHECK(t0.vectorStrField.Value().size() == 2);
   CHECK(fromInt.size() == 3);
   CHECK(fromDbl.size() == 3);
   CHECK(fromStr.size() == 3);

   // check assignment (int)
   std::vector<int32_t> assignFromInt;
   assignFromInt.push_back(1);
   assignFromInt.push_back(2);
   t0.vectorInt32Field = assignFromInt;
   CHECK(t0.vectorInt32Field.Value() == assignFromInt);
   CHECK(t0.vectorInt32Field.Value().size() == assignFromInt.size());

   // check assignment (double)
   std::vector<double> assignFromDbl;
   assignFromDbl.push_back(1.0);
   assignFromDbl.push_back(2.0);
   t0.vectorDblField = assignFromDbl;
   CHECK(t0.vectorDblField.Value() == assignFromDbl);
   CHECK(t0.vectorDblField.Value().size() == assignFromDbl.size());

   // check assignment (string)

   std::vector<std::string> assignFromStr;
   assignFromStr.push_back("1");
   assignFromStr.push_back("2");
   t0.vectorStrField = assignFromStr;
   t0.vectorStrField.Value(assignFromStr);
   CHECK(t0.vectorStrField.Value() == assignFromStr);
   CHECK(t0.vectorStrField.Value().size() == assignFromStr.size());

   t0a = t0;
   CHECK(t0a.vectorDblField.Value().size() == t0a.vectorDblField.Value().size());
   CHECK(t0a.vectorDblField.Value() == t0a.vectorDblField.Value());
   // check != operation
   CHECK(!(t0.vectorInt32Field != t0a.vectorInt32Field));

   // check assignment (Aggregate)
   std::vector<ReferenceAggregate> assignFromAggVect;
   std::vector<ReferenceAggregate> assignToAggVect;
   ReferenceAggregate a("v1.0.0");
   CHECK(!a.vectorIntField.hasValue());
   a.int32Field = 100;
   a.vectorIntField = assignFromInt;
   assignFromAggVect.push_back(a);

   ReferenceAggregate b("v1.1.0");
   CHECK(!b.vectorIntField.hasValue());
   b.doubleField = 99.99;
   b.vectorIntField = assignFromInt;
   assignFromAggVect.push_back(b);

   assignToAggVect = assignFromAggVect;
   CHECK(assignToAggVect == assignFromAggVect);

   t0.vectorAggField = assignFromAggVect;
   t0a.vectorAggField = assignFromAggVect;
   CHECK(t0a.vectorAggField.Value().size() == t0.vectorAggField.Value().size());
   CHECK(t0a.vectorAggField.Value() == t0.vectorAggField.Value());
   CHECK(t0a.vectorAggField == t0.vectorAggField);

   const ReferenceAggregate &ra = t0.vectorAggField.Value()[0];
   const ReferenceAggregate &rb = t0.vectorAggField.Value()[1];
   CHECK(ra.getVersion() == "v1.0.0");
   CHECK(ra.vectorIntField.State() == a.vectorIntField.State());
   CHECK(rb.getVersion() == "v1.1.0");
   CHECK(rb.vectorIntField.State() == b.vectorIntField.State());
   CHECK(ra == a);
   CHECK(rb == b);
   CHECK(ra != rb);
}
/// <summary>
/// This tests vector field being unavailable in various versions of aggregate objects
/// </summary>
TEST_CASE("VectorFieldVersionUnitTests", "[test]")
{

   // Test for vector versions
   TestVectorFieldAggregate tv0("1.0.0");
   TestVectorFieldAggregate tv1("1.1.0");
   TestVectorFieldAggregate tv2("1.2.0");

   CHECK(tv0.vectorVersion0only.State() == FieldStateEnum::NotSet);
   CHECK(tv1.vectorVersion0only.State() == FieldStateEnum::Unavailable);
   CHECK(tv2.vectorVersion0only.State() == FieldStateEnum::Unavailable);

   std::vector<int64_t> fromInt64;
   fromInt64.push_back(111);
   fromInt64.push_back(222);
   std::vector<int64_t> fromInt64Extra;
   fromInt64Extra.push_back(777);
   fromInt64Extra.push_back(888);
   fromInt64Extra.push_back(999);

   //first, test Version0only field
   CHECK_THROWS_AS(tv0.vectorVersion0only.Value(), NotAbleToGet);    // version0only is not set
   tv0.vectorVersion0only = fromInt64;
   CHECK(tv0.vectorVersion0only.State() == FieldStateEnum::Set);
   CHECK(tv0.vectorVersion0only.Value()[0] == 111);
   CHECK(tv0.vectorVersion0only.Value()[1] == 222);
   CHECK_THROWS_AS(tv1.vectorVersion0only.Value(), NotAbleToGet);
   CHECK_THROWS_AS(tv2.vectorVersion0only.unset(), NotAbleToSet);
   CHECK_THROWS_AS(tv2.vectorVersion0only = fromInt64, NotAbleToSet);
   CHECK_THROWS_AS(tv2.vectorVersion0only.unset(), NotAbleToSet);

   // now look at version1only field
   CHECK(tv0.vectorVersion1only.State() == FieldStateEnum::Unavailable);
   CHECK(tv1.vectorVersion1only.State() == FieldStateEnum::NotSet);
   CHECK(tv2.vectorVersion1only.State() == FieldStateEnum::Unavailable);
   tv1.vectorVersion1only = fromInt64;
   CHECK(tv1.vectorVersion1only.State() == FieldStateEnum::Set);
   CHECK(tv1.vectorVersion1only.Value()[0] == 111);
   CHECK(tv1.vectorVersion1only.Value()[1] == 222);
   tv1.vectorVersion1only.Value(fromInt64Extra);
   CHECK(tv1.vectorVersion1only.Value()[0] == 777);
   CHECK(tv1.vectorVersion1only.Value()[1] == 888);
   CHECK(tv1.vectorVersion1only.Value()[2] == 999);
   tv1.vectorVersion1only.unset();
   CHECK(tv1.vectorVersion1only.State() == FieldStateEnum::NotSet);
   CHECK_THROWS_AS(tv0.vectorVersion1only.Value(), NotAbleToGet);
   CHECK_THROWS_AS(tv2.vectorVersion1only.Value(), NotAbleToGet);
   CHECK_THROWS_AS(tv0.vectorVersion1only.Value(fromInt64), NotAbleToSet);
   CHECK_THROWS_AS(tv2.vectorVersion1only.Value(fromInt64Extra), NotAbleToSet);
   CHECK_THROWS_AS(tv0.vectorVersion1only.unset(), NotAbleToSet);
   CHECK_THROWS_AS(tv2.vectorVersion1only.unset(), NotAbleToSet);
   CHECK_THROWS_AS(tv0.vectorVersion1only = fromInt64, NotAbleToSet);
   CHECK_THROWS_AS(tv2.vectorVersion1only = fromInt64, NotAbleToSet);

   // now look at version2only field
   CHECK(tv0.vectorVersion2only.State() == FieldStateEnum::Unavailable);
   CHECK(tv1.vectorVersion2only.State() == FieldStateEnum::Unavailable);
   CHECK(tv2.vectorVersion2only.State() == FieldStateEnum::NotSet);
   tv2.vectorVersion2only.unset();
   CHECK_THROWS_AS(tv0.vectorVersion2only.unset(), NotAbleToSet);
   CHECK_THROWS_AS(tv1.vectorVersion2only.unset(), NotAbleToSet);
}
