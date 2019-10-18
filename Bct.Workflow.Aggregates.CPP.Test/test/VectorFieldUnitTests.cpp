#include "Sample1Aggregate.h"
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
   VectorField<Sample1Aggregate> vectorAggField;

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

TEST_CASE("VectorFieldUnitTests", "[test]")
{
   // check version 
   TestVectorFieldAggregate t0("1.0.0");
   TestVectorFieldAggregate t1("1.1.0");
   TestVectorFieldAggregate t2("1.2.0");  

   CHECK(t0.getVersion() == "1.0.0");
   CHECK(t1.getVersion() == "1.1.0");
   CHECK(t2.getVersion() == "1.2.0");

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
   //t0.vectorStrField.Value(assignFromStr);
   CHECK(t0.vectorStrField.Value() == assignFromStr);
   CHECK(t0.vectorStrField.Value().size() == assignFromStr.size());
   
   // check assignment (Aggregate)
   //std::vector<Sample1Aggregate> assignFromAgg;
   //Sample1Aggregate a;
   //Sample1Aggregate b;
   //assignFromAgg.push_back(a);
   //assignFromAgg.push_back(b);
   ////t0.vectorAggField = assignFromAgg;
   ////t0.vectorAggField.Value(assignFromAgg);
   //CHECK(t0.vectorAggField.Value() == assignFromAgg);
   //CHECK(t0.vectorAggField.Value().size() == assignFromAgg.size());
 
   
}
