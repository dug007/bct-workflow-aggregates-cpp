#include "AggComputeField.h"

#include "AbstractAggregate.h"
#include "BaseAggregate.h"
#include "AggregateMetaData.h"


namespace Bct
{
   namespace Workflow
   {
      namespace Aggregates
      {
         bool AggComputeField::s_initialized = false;
         AggregateMetaData *AggComputeField::s_metaData;

         AggComputeField::AggComputeField(const std::string &version) :
            BaseAggregate(version),
            field1("field1", TypeEnum::Int32Type, this),
            field2("field2", TypeEnum::Int32Type, this)
         {

            FieldList().push_back(&field1);
            FieldList().push_back(&field2);
            syncVersion();
         }

         AggComputeField::AggComputeField() :
            BaseAggregate(),
            field1("field1", TypeEnum::Int32Type, this),
            field2("field2", TypeEnum::Int32Type, this)

         {
            FieldList().push_back(&field1);
            FieldList().push_back(&field2);
            syncVersion();
         }

         AggComputeField::AggComputeField(const std::string &fieldName, BaseAggregate * parent) :
            BaseAggregate(fieldName, parent),
            field1("field1", TypeEnum::Int32Type, this),
            field2("field2", TypeEnum::Int32Type, this)
         {
            FieldList().push_back(&field1);
            FieldList().push_back(&field2);
            syncVersion();
         }

         AggregateMetaData &AggComputeField::MetaData() const
         {
            return *s_metaData;
         }

         void AggComputeField::initMetaData(AggregateMetaData  *metaData)
         {
            s_metaData = metaData;
            s_initialized = true;
         }

      };
   }
}