#include "AggComputeField.h"

#include "AbstractAggregate.h"
#include "BaseAggregate.h"


namespace Bct
{
   namespace Workflow
   {
      namespace Aggregates
      {
         AggComputeField::AggComputeField(const std::string &version) :
            BaseAggregate(version, s_metaData),
            field1("field1", TypeEnum::Int32Type, MetaData(), this),
            field2("field2", TypeEnum::Int32Type, MetaData(), this)
         {

            FieldList().push_back(&field1);
            FieldList().push_back(&field2);
            SyncRootVersion();
         }

         AggComputeField::AggComputeField() :
            BaseAggregate(s_metaData),
            field1("field1", TypeEnum::Int32Type, MetaData(), this),
            field2("field2", TypeEnum::Int32Type, MetaData(), this)

         {
            FieldList().push_back(&field1);
            FieldList().push_back(&field2);
            SyncRootVersion();
         }

         AggComputeField::AggComputeField(const std::string &fieldName, BaseAggregate * parent) :
            BaseAggregate(fieldName, parent),
            field1("field1", TypeEnum::Int32Type, MetaData(), this),
            field2("field2", TypeEnum::Int32Type, MetaData(), this)
         {
            FieldList().push_back(&field1);
            FieldList().push_back(&field2);
            SyncRootVersion();
         }


         void AggComputeField::initMetaData(AggregateMetaData  *metaData)
         {
            s_metaData = metaData;
            s_initialized = true;
         }

         bool AggComputeField::s_initialized = false;
         AggregateMetaData *AggComputeField::s_metaData;
      };
   }
}