#include "NestedWithReference.h"
#include "NestedWithReference.h"

#include "AbstractAggregate.h"
#include "BaseAggregate.h"

using namespace Bct::Workflow::Aggregates;

namespace Bct
{
   namespace Workflow
   {
      namespace Implementation
      {
         NestedWithReferenceAggregate::NestedWithReferenceAggregate() :
            BaseAggregate(BaseAggregate::UseMostRecentVersionStr),
            boolField(0, this),
            int32Field(1, this),
            uint32Field(2, this),
            int64Field(3, this),
            uint64Field(4, this),
            doubleField(5, this),
            stringField(6, this),
            enumField(7, "ReferenceEnum::Reference",
               "0 1 2 4 8 16",
               "ReferenceEnum::VeryGood ReferenceEnum::Good ReferenceEnum::Average ReferenceEnum::BelowAverage ReferenceEnum::Poor ReferenceEnum::VeryPoor",
               this),
            aggField(8, this)
      {
         pushFields();
         syncVersion();
      }

         NestedWithReferenceAggregate::NestedWithReferenceAggregate(const std::string &version) :
            BaseAggregate(version),
            boolField(0, this),
            int32Field(1, this),
            uint32Field(2, this),
            int64Field(3, this),
            uint64Field(4, this),
            doubleField(5, this),
            stringField(6, this),
            enumField(7, "ReferenceEnum::Reference",
               "0 1 2 4 8 16",
               "ReferenceEnum::VeryGood ReferenceEnum::Good ReferenceEnum::Average ReferenceEnum::BelowAverage ReferenceEnum::Poor ReferenceEnum::VeryPoor",
               this),
            aggField(8, this)
         {
            pushFields();
            syncVersion();
         }

         NestedWithReferenceAggregate::NestedWithReferenceAggregate(int32_t fieldId, BaseAggregate * const parent) :
            BaseAggregate(fieldId, parent),
            boolField(0, this),
            int32Field(1, this),
            uint32Field(2, this),
            int64Field(3, this),
            uint64Field(4, this),
            doubleField(5, this),
            stringField(6, this),
            enumField(7, "ReferenceEnum::Reference",
               "0 1 2 4 8 16",
               "ReferenceEnum::VeryGood ReferenceEnum::Good ReferenceEnum::Average ReferenceEnum::BelowAverage ReferenceEnum::Poor ReferenceEnum::VeryPoor",
               this),
            aggField(8, this)

         {
            pushFields();
            syncVersion();
         }

         NestedWithReferenceAggregate::NestedWithReferenceAggregate(const NestedWithReferenceAggregate & other) :
            BaseAggregate(other),
            boolField(other.boolField, this),
            int32Field(other.int32Field, this),
            uint32Field(other.uint32Field, this),
            int64Field(other.int64Field, this),
            uint64Field(other.uint64Field, this),
            doubleField(other.doubleField, this),
            stringField(other.stringField, this),
            enumField(other.enumField, this),
            aggField(other.aggField, this)
         {
            pushFields();
         }

         NestedWithReferenceAggregate::NestedWithReferenceAggregate(const NestedWithReferenceAggregate & other, BaseAggregate * const parent) :
            BaseAggregate(other, parent),
            boolField(other.boolField, this),
            int32Field(other.int32Field, this),
            uint32Field(other.uint32Field, this),
            int64Field(other.int64Field, this),
            uint64Field(other.uint64Field, this),
            doubleField(other.doubleField, this),
            stringField(other.stringField, this),
            enumField(other.enumField, this),
            aggField(other.aggField, this)
         {
            pushFields();
         }

         NestedWithReferenceAggregate & NestedWithReferenceAggregate::operator=(const NestedWithReferenceAggregate &other)
         {
            if (&other != this)
            {
               BaseAggregate::operator=(other);
               boolField.value(other.boolField.value());
               int32Field.value(other.int32Field.value());
               uint32Field.value(other.uint32Field.value());
               int64Field.value(other.int64Field.value());
               uint64Field.value(other.uint64Field.value());
               doubleField.value(other.doubleField.value());
               stringField.value(other.stringField.value());
               enumField.value(other.enumField.value());
               aggField = other.aggField;
            }

            return *this;
         }

         NestedWithReferenceAggregate::~NestedWithReferenceAggregate()
         {
         }

         AggregateMetaData & NestedWithReferenceAggregate::MetaData() const
         {
            return s_MetaData();
         };

         void NestedWithReferenceAggregate::pushFields()
         {
            FieldList().push_back(&boolField);
            FieldList().push_back(&int32Field);
            FieldList().push_back(&uint32Field);
            FieldList().push_back(&int64Field);
            FieldList().push_back(&uint64Field);
            FieldList().push_back(&doubleField);
            FieldList().push_back(&stringField);
            FieldList().push_back(&enumField);
            AggList().push_back(&aggField);
         }

         AggregateMetaData & NestedWithReferenceAggregate::s_MetaData()
         {
            static AggregateMetaData tm;
            static bool initialized = false;

            if (!initialized)
            {
               tm.addVersion("1.0.0");
               tm.addVersion("1.1.0");

               tm.addField(0, "boolField", Bct::Workflow::TypeEnum::BoolType);
               tm.addField(1, "int32Field", Bct::Workflow::TypeEnum::Int32Type);
               tm.addField(2, "uint32Field", Bct::Workflow::TypeEnum::UInt32Type);
               tm.addField(3, "int64Field", Bct::Workflow::TypeEnum::Int64Type);
               tm.addField(4, "uint64Field", Bct::Workflow::TypeEnum::UInt64Type);
               tm.addField(5, "doubleField", Bct::Workflow::TypeEnum::DoubleType);
               tm.addField(6, "stringField", Bct::Workflow::TypeEnum::StringType);
               tm.addField(7, "enumField", Bct::Workflow::TypeEnum::Int32Type);
               tm.addAggField(8, "aggField");

               tm.addFieldMetaToAllVersions(0, FieldStateEnum::Default, "true");
               tm.addFieldMetaToAllVersions(1, FieldStateEnum::Default, "-1");
               tm.addFieldMetaToAllVersions(2, FieldStateEnum::Default, "1");
               tm.addFieldMetaToAllVersions(3, FieldStateEnum::Default, "-1");
               tm.addFieldMetaToAllVersions(4, FieldStateEnum::Default, "1");
               tm.addFieldMetaToAllVersions(5, FieldStateEnum::Default, "1.0");
               tm.addFieldMetaToAllVersions(6, FieldStateEnum::Default, "hello world");
               tm.addFieldMetaToAllVersions(7, FieldStateEnum::Default, "2");
               tm.addAggMetaToAllVersions(8, FieldStateEnum::Set, 0);
               tm.addAggMetaToAllVersions(8, FieldStateEnum::Set, 1);

               initialized = true;
            }

            return tm;
         }
      };
   }
}
