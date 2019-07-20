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
         AggNested::AggNested(const std::string &version) :
            BaseAggregate(version, s_metaData),
            intField1("intField1", TypeEnum::Int32Type, MetaData(), this),
            intField2("intField2", TypeEnum::Int32Type, MetaData(), this),
            aggField("aggField", this)

         {
            FieldList().push_back(&intField1);
            FieldList().push_back(&intField2);
            AggList().push_back(&aggField);
            SyncVersion();
         }

         AggNested::AggNested() :
            BaseAggregate(s_metaData),
            intField1("intField1", TypeEnum::Int32Type, MetaData(), this),
            intField2("intField2", TypeEnum::Int32Type, MetaData(), this),
            aggField("aggField", this)

         {
            FieldList().push_back(&intField1);
            FieldList().push_back(&intField2);
            AggList().push_back(&aggField);
            SyncVersion();
         }

         void AggNested::initMetaData(AggregateMetaData  *metaData, AggregateMetaData *aggFieldMetaData)
         {
            s_metaData = metaData;
            s_initialized = true;
            AggComputeField::initMetaData(aggFieldMetaData);
         }

         bool AggNested::s_initialized = false;
         AggregateMetaData *AggNested::s_metaData;
      };
   }
}