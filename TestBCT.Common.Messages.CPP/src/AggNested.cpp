#include "AggNested.h"

#include "AbstractAggregate.h"
#include "BaseAggregate.h"
#include "AggNested.h"


namespace Bct
{
   namespace Workflow
   {
      namespace Aggregates
      {
         bool AggNested::s_initialized = false;
         AggregateMetaData *AggNested::s_metaData;

         AggNested::AggNested(const std::string &version) :
            BaseAggregate(version),
            intField1("intField1", TypeEnum::Int32Type, this),
            intField2("intField2", TypeEnum::Int32Type, this),
            aggField("aggField", this),
            aggFieldV2("aggFieldV2", this),
            enumField("enumField", TypeEnum::Int32Type, "TypeEnum::Type",
               "0 1 2 3 4 5 6 7 8 9 10 11",
               "TypeEnum::EmptyType TypeEnum::ObjectType TypeEnum::BoolType TypeEnum::Int32Type TypeEnum::UInt32Type TypeEnum::Int64Type TypeEnum::UInt64Type TypeEnum::DoubleType TypeEnum::StringType TypeEnum::EnumType TypeEnum::VariableType",
               this)

         {
            FieldList().push_back(&intField1);
            FieldList().push_back(&intField2);
            AggList().push_back(&aggField);
            AggList().push_back(&aggFieldV2);
            FieldList().push_back(&enumField);
            syncVersion();
         }

         AggNested::AggNested() :
            BaseAggregate(),
            intField1("intField1", TypeEnum::Int32Type, this),
            intField2("intField2", TypeEnum::Int32Type, this),
            aggField("aggField", this),
            aggFieldV2("aggFieldV2", this),
            enumField("enumField", TypeEnum::Int32Type, "TypeEnum::Type",
               "0 1 2 3 4 5 6 7 8 9 10 11",
               "TypeEnum::EmptyType TypeEnum::ObjectType TypeEnum::BoolType TypeEnum::Int32Type TypeEnum::UInt32Type TypeEnum::Int64Type TypeEnum::UInt64Type TypeEnum::DoubleType TypeEnum::StringType TypeEnum::EnumType TypeEnum::VariableType",
               this)

         {
            FieldList().push_back(&intField1);
            FieldList().push_back(&intField2);
            AggList().push_back(&aggField);
            AggList().push_back(&aggFieldV2);
            FieldList().push_back(&enumField);
            syncVersion();
         }

         void AggNested::bindMetaData(AggregateMetaData  *metaData, AggregateMetaData *aggFieldMetaData)
         {
            s_metaData = metaData;
            s_initialized = true;
            AggComputeField::bindMetaData(aggFieldMetaData);
         }

         AggregateMetaData &AggNested::MetaData() const
         {
            return *s_metaData;
         }

      };
   }
}