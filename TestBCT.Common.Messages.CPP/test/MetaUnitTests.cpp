#include "AggregateMetaData.h"
#include "FluentMeta.h"
#include "FieldMeta.h"
#include "BaseAggregate.h"
#include "BaseField.h"
#include "AggComputeField.h"
#include "StringField.h"

#include "catch.hpp"

using namespace Bct::Workflow::Aggregates;

class AggForFluentTest : public BaseAggregate
{
private:
   static AggregateMetaData *s_metaData;
   static bool s_initialized;

public:
   BaseField<int32_t> intField;
   StringField        strField;
   AggComputeField    aggField;

   AggForFluentTest(const std::string &version)
      :
      BaseAggregate(version),
      intField("intField", Bct::Workflow::TypeEnum::Int32Type, this),
      strField("strField", this),
      aggField("aggField", this)
   {
      FieldList().push_back(&intField);
      FieldList().push_back(&strField);
      AggList().push_back(&aggField);

      // metadata AggForFluentTest------------------->
      static AggregateMetaData tm;
      tm.addVersion("1.0.0");
      tm.addVersion("1.1.0");
      tm.addVersion("1.2.0");
      tm.addFieldMeta("intField", FieldStateEnum::Default, "0") .toVersion(0);
      tm.addFieldMeta("intField", FieldStateEnum::Default, "1") .toVersion(1) .toVersion(2);
      tm.addFieldMetaToAllVersions("strField", FieldStateEnum::Default, "hello world");
      tm.addAggMeta("aggField", FieldStateEnum::Unavailable, 0)   .toVersion(0);
      tm.addAggMeta("aggField", FieldStateEnum::Set, 1)           .toVersion(1);
      tm.addAggMeta("aggField", FieldStateEnum::Set, 2)           .toVersion(2);
      initMetaData(&tm);
      // <----------------- metadata AggForFluentTest 

         // metadata AggComputeField ------------------->
      static AggregateMetaData cf;
      cf.addVersion("1.0.0");
      cf.addVersion("1.1.0");
      cf.addVersion("1.2.0");
      cf.addFieldMetaToAllVersions("field1", FieldStateEnum::Default, "99");
      cf.addFieldMeta("field2", FieldStateEnum::Default, "1")  .toVersion(0);
      cf.addFieldMeta("field2", FieldStateEnum::Default, "2")  .toVersion(1);
      cf.addFieldMeta("field2", FieldStateEnum::Default, "3")  .toVersion(2);
      aggField.initMetaData(&cf);
      // <----------------- metadata AggComputeField 

      syncVersion();
   }

   static void initMetaData(AggregateMetaData  *metaData)
   {
      s_metaData = metaData;
      s_initialized = true;
   }

   virtual AggregateMetaData &MetaData() const
   {
      return *s_metaData;
   };
};

bool AggForFluentTest::s_initialized = false;
AggregateMetaData *AggForFluentTest::s_metaData;

TEST_CASE("FluentMetaTests", "[test]")
{
   AggForFluentTest t0("1.0.0");
   AggForFluentTest t1("1.1.0");
   AggForFluentTest t2("1.2.0");

   CHECK(t0.getVersion() == "1.0.0");
   CHECK(t1.getVersion() == "1.1.0");
   CHECK(t2.getVersion() == "1.2.0");

   CHECK(0 == t0.intField);
   CHECK(1 == t1.intField);
   CHECK(1 == t2.intField);

   CHECK("hello world" == (std::string)t0.strField) ;

   CHECK(99 == t1.aggField.field1);
   CHECK(99 == t2.aggField.field1);

   CHECK(2 == t1.aggField.field2);
   CHECK(3 == t2.aggField.field2);

}
