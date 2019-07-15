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
            SyncCurrentVersion();
         }

         AggComputeField::AggComputeField() :
            BaseAggregate(s_metaData),
            field1("field1", TypeEnum::Int32Type, MetaData(), this),
            field2("field2", TypeEnum::Int32Type, MetaData(), this)

         {
            FieldList().push_back(&field1);
            FieldList().push_back(&field2);
            SyncCurrentVersion();
         }

         void AggComputeField::initMetaData(VersionMetaData  *metaData)
         {
            s_metaData = metaData;
            s_initialized = true;
         }

         bool AggComputeField::s_initialized = false;
         VersionMetaData *AggComputeField::s_metaData;
      };
   }
}