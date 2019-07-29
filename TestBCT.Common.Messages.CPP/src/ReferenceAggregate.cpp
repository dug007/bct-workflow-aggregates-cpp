#include "ReferenceAggregate.h"

#include "AbstractAggregate.h"
#include "BaseAggregate.h"



namespace Bct
{
   namespace Workflow
   {
      namespace Aggregates
      {
         // true if the metadata has been initialized, false otherwise.
         bool ReferenceAggregate::s_initialized = false;
         // pointer to the metadata object.
         AggregateMetaData *ReferenceAggregate::s_metaData;

         ReferenceAggregate::ReferenceAggregate() :
            ReferenceAggregate("0.0.0")
         {
         }

         ReferenceAggregate::ReferenceAggregate(const std::string &version) :
            BaseAggregate(version),
            boolField("boolField", TypeEnum::BoolType, this),
            int32Field("int32Field", TypeEnum::Int32Type, this),
            uint32Field("uint32Field", TypeEnum::UInt32Type, this),
            int64Field("int64Field", TypeEnum::Int64Type, this),
            uint64Field("uint64Field", TypeEnum::UInt64Type, this),
            doubleField("doubleField", TypeEnum::DoubleType, this),
            stringField("stringField", this),
            enumField("enumField", TypeEnum::EnumType, "ReferenceEnum::Reference",
               "0 1 2 4 8 16",
               "ReferenceEnum::VeryGood ReferenceEnum::Good ReferenceEnum::Average ReferenceEnum::BelowAverage ReferenceEnum::Poor ReferenceEnum::VeryPoor",
               this)
         {
            FieldList().push_back(&boolField);
            FieldList().push_back(&int32Field);
            FieldList().push_back(&uint32Field);
            FieldList().push_back(&int64Field);
            FieldList().push_back(&uint64Field);
            FieldList().push_back(&doubleField);
            FieldList().push_back(&stringField);
            FieldList().push_back(&enumField);

            // metadata------------------->
            static AggregateMetaData tm;
            tm.addVersion("1.0.0");
            tm.addVersion("1.1.0");
            tm.addFieldMetaToAllVersions("boolField", FieldStateEnum::Default, "true");
            tm.addFieldMetaToAllVersions("int32Field", FieldStateEnum::Default, "-1");
            tm.addFieldMetaToAllVersions("uint32Field", FieldStateEnum::Default, "1");
            tm.addFieldMetaToAllVersions("int64Field", FieldStateEnum::Default, "-1");
            tm.addFieldMetaToAllVersions("uint64Field", FieldStateEnum::Default, "1");
            tm.addFieldMetaToAllVersions("doubleField", FieldStateEnum::Default, "1.0");
            tm.addFieldMetaToAllVersions("stringField", FieldStateEnum::Default, "hello world");
            tm.addFieldMetaToAllVersions("enumField", FieldStateEnum::Default, "2");
            bindMetaData(&tm);
            // <----------------- metadata

            syncVersion();
         }

         void ReferenceAggregate::bindMetaData(AggregateMetaData  *metaData)
         {
            s_metaData = metaData;
            s_initialized = true;
         }

         AggregateMetaData & ReferenceAggregate::MetaData() const
         {
            return *s_metaData;
         };
      };
   }
}