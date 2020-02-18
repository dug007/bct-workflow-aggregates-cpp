#include "AggComputeField.h"

#include "AbstractAggregate.h"
#include "BaseAggregate.h"
#include "AggregateMetaData.h"


namespace Bct
{
   namespace Workflow
   {
      namespace Implementation
      {
         bool AggComputeField::s_initialized = false;
         AggregateMetaData *AggComputeField::s_metaData;

         AggComputeField::AggComputeField(const std::string &version) :
            BaseAggregate(version),
            field1(0, this),
            field2(1, this),
            stringField(2, this)
         {

            FieldList().push_back(&field1);
            FieldList().push_back(&field2);
            FieldList().push_back(&stringField);
            syncVersion();
         }

         AggComputeField::AggComputeField() :
            BaseAggregate(),
            field1(0, this),
            field2(1, this),
            stringField(2, this)
         {
            FieldList().push_back(&field1);
            FieldList().push_back(&field2);
            FieldList().push_back(&stringField);
            syncVersion();
         }

         AggComputeField::AggComputeField(int32_t fieldId, BaseAggregate * parent) :
            BaseAggregate(fieldId, parent),
            field1(0, this),
            field2(1, this),
            stringField(2, this)
         {
            FieldList().push_back(&field1);
            FieldList().push_back(&field2);
            FieldList().push_back(&stringField);
            syncVersion();
         }

         AggComputeField::AggComputeField(AggComputeField &other, BaseAggregate *parent) :
            BaseAggregate(other, parent),
            field1(other.field1, this),
            field2(other.field2, this),
            stringField(other.stringField, this)
         {
            FieldList().push_back(&field1);
            FieldList().push_back(&field2);
            FieldList().push_back(&stringField);
         }

         AggComputeField & AggComputeField::operator=(const AggComputeField &other)
         {
            if (&other != this)
            {
               BaseAggregate::operator=(other);
               field1.value(other.field1.value());
               field2.value(other.field2.value());
               stringField.value(other.stringField.value());
            }
            return *this;
         }


         AggregateMetaData &AggComputeField::MetaData() const
         {
            return *s_metaData;
         }

         void AggComputeField::bindMetaData(AggregateMetaData  *metaData)
         {
            s_metaData = metaData;
            s_initialized = true;
         }

      };
   }
}