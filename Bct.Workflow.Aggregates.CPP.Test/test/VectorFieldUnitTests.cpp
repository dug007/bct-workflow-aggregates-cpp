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
private:
   static AggregateMetaData *s_metaData;
   static bool s_initialized;

public:
   VectorField<int32_t> vectorInt32Field;
   VectorField<double> vectorDblField;
   VectorField<std::string> vectorStrField;
   VectorField<ReferenceAggregate> vectorAggField;

   TestVectorFieldAggregate(const std::string &version)
      :
      BaseAggregate(version),
      vectorInt32Field(0, this),
      vectorDblField(1, this),
      vectorStrField(2, this),
      vectorAggField(3, this)
   {
      FieldList().push_back(&vectorInt32Field);
      FieldList().push_back(&vectorDblField);
      FieldList().push_back(&vectorStrField);
      FieldList().push_back(&vectorAggField);

      // metadata TestVectorFieldAggregate------------------->
      static AggregateMetaData tm;
      tm.addField(0, "vectorInt32Field", Bct::Workflow::TypeEnum::ArrayType);
      tm.addField(1, "vectorDblField", Bct::Workflow::TypeEnum::ArrayType);
      tm.addField(2, "vectorStrField", Bct::Workflow::TypeEnum::ArrayType);
      tm.addField(3, "vectorAggField", Bct::Workflow::TypeEnum::ArrayType);

      tm.addVersion("1.0.0");
      tm.addVersion("1.1.0");
      tm.addVersion("1.2.0");

      tm.addFieldMetaToAllVersions(0, FieldStateEnum::NotSet, "notset");
      tm.addFieldMetaToAllVersions(1, FieldStateEnum::NotSet, "notset");
      tm.addFieldMetaToAllVersions(2, FieldStateEnum::NotSet, "notset");
      tm.addFieldMetaToAllVersions(3, FieldStateEnum::NotSet, "notset");
      

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

bool TestVectorFieldAggregate::s_initialized = false;
AggregateMetaData *TestVectorFieldAggregate::s_metaData;

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
   CHECK(!t0.vectorStrField.hasValue());

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

   
   // check assignment (Aggregate)
   std::vector<ReferenceAggregate> assignFromAggVect;
   std::vector<ReferenceAggregate> assignToAggVect;
   ReferenceAggregate a;
   ReferenceAggregate b;
   assignFromAggVect.push_back(a);
   assignFromAggVect.push_back(b);

   assignToAggVect = assignFromAggVect;
   CHECK(assignToAggVect == assignFromAggVect);
   t0.vectorAggField = assignFromAggVect;
   t0a.vectorAggField = assignFromAggVect;
   CHECK(t0a.vectorAggField == t0.vectorAggField);
   const ReferenceAggregate &x = t0.vectorAggField.Value()[0];
}
