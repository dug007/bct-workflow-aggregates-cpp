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
            field1("field1", TypeEnum::Int32Type, MetaData(), this),
            field2("field2", TypeEnum::Int32Type, MetaData(), this),
            field3("field3", this)

         {
            FieldList().push_back(&field1);
            FieldList().push_back(&field2);
            AggList().push_back(&field3);
            SyncVersion();
         }

         AggNested::AggNested() :
            BaseAggregate(s_metaData),
            field1("field1", TypeEnum::Int32Type, MetaData(), this),
            field2("field2", TypeEnum::Int32Type, MetaData(), this),
            field3("field3", this)

         {
            FieldList().push_back(&field1);
            FieldList().push_back(&field2);
            AggList().push_back(&field3);
            SyncVersion();
         }

         void AggNested::initMetaData(AggregateMetaData  *metaData, AggregateMetaData *field3MetaData)
         {
            s_metaData = metaData;
            s_initialized = true;
            AggComputeField::initMetaData(field3MetaData);
         }

         bool AggNested::s_initialized = false;
         AggregateMetaData *AggNested::s_metaData;
      };
   }
}