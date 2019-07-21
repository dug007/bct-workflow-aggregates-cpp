#include "AggAssess.h"
#include "AbstractAggregate.h"
#include "BaseAggregate.h"
#include "AggAssess.h"
#include "AssessMetaData.h"


namespace Bct
{
   namespace Workflow
   {
      namespace Aggregates
      {
         AggAssess::AggAssess(const std::string &version) :
            BaseAggregate(version),
            field1("field1", TypeEnum::Int32Type, this),
            field2("field2", TypeEnum::Int32Type, this)
         {
            FieldList().push_back(&field1);
            FieldList().push_back(&field2);
            initMetaData(&s_meta.metaData);
            SyncVersion();
         }

         AggAssess::AggAssess() :
            BaseAggregate(),
            field1("field1", TypeEnum::Int32Type, this),
            field2("field2", TypeEnum::Int32Type, this)

         {
            FieldList().push_back(&field1);
            FieldList().push_back(&field2);
            SyncVersion();
         }

         void AggAssess::initMetaData(AggregateMetaData  *metaData)
         {
            s_metaData = metaData;
            s_initialized = true;
         }

         AggregateMetaData &AggAssess::MetaData()
         {
            return *s_metaData;
         }

         bool AggAssess::s_initialized = false;
         AggregateMetaData *AggAssess::s_metaData;

         // embeded metadata
         AssessMetaData AggAssess::s_meta;
      };
   }
}