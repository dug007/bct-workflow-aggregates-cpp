#include "AggregateMetaData.h"
#include "FluentMeta.h"
#include "FieldMeta.h"
#include "BaseAggregate.h"
#include "BaseField.h"
#include "AggComputeField.h"
#include "StringField.h"

#include "catch.hpp"

using namespace Bct::Workflow::Aggregates;
using namespace Bct::Workflow::Implementation;

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
      intField(0, this),
      strField(1, this),
      aggField(2, this)
   {
      FieldList().push_back(&intField);
      FieldList().push_back(&strField);
      AggList().push_back(&aggField);

      // metadata AggForFluentTest------------------->
      static AggregateMetaData tm;
      tm.addField(0, "intField", Bct::Workflow::TypeEnum::Int32Type);
      tm.addField(1, "strField", Bct::Workflow::TypeEnum::StringType);
      tm.addAggField(2, "aggField");

      tm.addVersion("1.0.0");
      tm.addVersion("1.1.0");
      tm.addVersion("1.2.0");

      tm.addFieldMeta(0, FieldStateEnum::Default, "0") .toVersion(0);
      tm.addFieldMeta(0, FieldStateEnum::Default, "1") .toVersion(1) .toVersion(2);
      tm.addFieldMetaToAllVersions(1, FieldStateEnum::Default, "hello world");
      tm.addAggMeta(2, FieldStateEnum::Unavailable, 0)   .toVersion(0);
      tm.addAggMeta(2, FieldStateEnum::Set, 1)           .toVersion(1);
      tm.addAggMeta(2, FieldStateEnum::Set, 2)           .toVersion(2);
      bindMetaData(&tm);
      // <----------------- metadata AggForFluentTest 

      // metadata AggComputeField ------------------->
      static AggregateMetaData cf;
      cf.addField(0, "field1", Bct::Workflow::TypeEnum::Int32Type);
      cf.addField(1, "field2", Bct::Workflow::TypeEnum::Int32Type);
      cf.addField(2, "stringField", Bct::Workflow::TypeEnum::StringType);

      cf.addVersion("1.0.0");
      cf.addVersion("1.1.0");
      cf.addVersion("1.2.0");

      cf.addFieldMetaToAllVersions(0, FieldStateEnum::Default, "99");
      cf.addFieldMeta(1, FieldStateEnum::Default, "100")  .toVersion(0);
      cf.addFieldMeta(1, FieldStateEnum::Default, "101")  .toVersion(1);
      cf.addFieldMeta(1, FieldStateEnum::Default, "102")  .toVersion(2);
      cf.addFieldMetaToAllVersions(2, FieldStateEnum::Default, "");
      aggField.bindMetaData(&cf);
      // <----------------- metadata AggComputeField 

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

   CHECK("hello world" == t0.strField.value()) ;

   CHECK(99 == t1.aggField.field1);
   CHECK(99 == t2.aggField.field1);

   CHECK(101 == t1.aggField.field2);
   CHECK(102 == t2.aggField.field2);
 }
