#include "ReferenceAggregate.h"
#include "AggregateMetaData.h"
#include "FluentMeta.h"
#include "FieldMeta.h"
#include "BaseAggregate.h"
#include "BaseField.h"
#include "VectorField.h"
#include "StringField.h"


#include "catch.hpp"

using namespace Bct::Workflow::Aggregates;
using namespace Bct::Workflow::Implementation;

class TestVectorFieldAggregate : public BaseAggregate
{
private:
   static AggregateMetaData *s_metaData;
   static bool s_initialized;

public:
   VectorField<int32_t> vectorInt32Field;
   VectorField<std::string> vectorStringField;

   TestVectorFieldAggregate(const std::string &version)
      :
      BaseAggregate(version),
      vectorInt32Field(0, this),
      vectorStringField(1, this)
   {
      FieldList().push_back(&vectorInt32Field);
      FieldList().push_back(&vectorStringField);

      // metadata TestVectorFieldAggregate------------------->
      static AggregateMetaData tm;
      tm.addField(0, "vectorInt32Field", Bct::Workflow::TypeEnum::ArrayType);
      tm.addField(1, "vectorStringField", Bct::Workflow::TypeEnum::ArrayType);

      tm.addVersion("1.0.0");
      tm.addVersion("1.1.0");
      tm.addVersion("1.2.0");

      tm.addFieldMetaToAllVersions(0, FieldStateEnum::NotSet, "notset");
      tm.addFieldMetaToAllVersions(1, FieldStateEnum::NotSet, "notset");

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

TEST_CASE("VectorFieldUnitTests", "[test]")
{
   
   TestVectorFieldAggregate t0("1.0.0");
   TestVectorFieldAggregate t1("1.1.0");
   TestVectorFieldAggregate t2("1.2.0");
   CHECK(t0.getVersion() == "1.0.0");
   CHECK(t1.getVersion() == "1.1.0");
   CHECK(t2.getVersion() == "1.2.0");
   CHECK(!t0.vectorInt32Field.hasValue());
   CHECK(!t0.vectorStringField.hasValue());

   std::vector<int32_t> from;
   from.push_back(1);
   from.push_back(2);

   std::vector<std::string> fromStr;
   fromStr.push_back("hi");
   fromStr.push_back("there");

   t0.vectorInt32Field = from;
   t0.vectorStringField = fromStr;

   CHECK(t0.vectorInt32Field.hasValue());
   CHECK(t0.vectorStringField.hasValue());
   CHECK(t0.vectorInt32Field.Value()[0] == 1);
   CHECK(t0.vectorInt32Field.FieldSetCounter() == 1);
   CHECK(t0.vectorStringField.FieldSetCounter() == 2);

   t0.

   from.push_back(3);
   fromStr.push_back("again");
}
