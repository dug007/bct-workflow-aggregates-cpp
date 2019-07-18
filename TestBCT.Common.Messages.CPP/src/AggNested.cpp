#include "AggNested.h"

#include "AbstractAggregate.h"
#include "BaseAggregate.h"


namespace Bct
{
   namespace Workflow
   {
      namespace Aggregates
      {
         AggNested::AggNested(const std::string &version) :
            BaseAggregate(version, s_metaData),
            field1("field1", TypeEnum::Int32Type, MetaData(), this),
            field2("field2", TypeEnum::Int32Type, MetaData(), this)
         {
            FieldList().push_back(&field1);
            FieldList().push_back(&field2);
            SyncCurrentVersion();
         }

         AggNested::AggNested() :
            BaseAggregate(s_metaData),
            field1("field1", TypeEnum::Int32Type, MetaData(), this),
            field2("field2", TypeEnum::Int32Type, MetaData(), this)

         {
            FieldList().push_back(&field1);
            FieldList().push_back(&field2);
            SyncCurrentVersion();
         }

         void AggNested::initMetaData(AggregateMetaData  *metaData)
         {
            s_metaData = metaData;
            s_initialized = true;
         }

         bool AggNested::s_initialized = false;
         AggregateMetaData *AggNested::s_metaData;
      };
   }
}