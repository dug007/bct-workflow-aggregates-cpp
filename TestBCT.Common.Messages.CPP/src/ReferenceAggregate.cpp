#include "ReferenceAggregate.h"

#include "AbstractAggregate.h"
#include "BaseAggregate.h"



namespace Bct
{
   namespace Workflow
   {
      namespace Aggregates
      {
         bool ReferenceAggregate::s_initialized = false;
         AggregateMetaData *ReferenceAggregate::s_metaData;

         ReferenceAggregate::ReferenceAggregate(const std::string &version) :
            BaseAggregate(version),
            boolField("boolField", TypeEnum::BoolType, this),
            int32Field("int32Field", TypeEnum::BoolType, this),
            uint32Field("uint32Field", TypeEnum::BoolType, this),
            int64Field("int64Field", TypeEnum::BoolType, this),
            uint64Field("uint64Field", TypeEnum::BoolType, this),
            doubleField("doubleField", TypeEnum::BoolType, this),
            stringField("stringField", TypeEnum::BoolType, this),
            enumField("enumField", TypeEnum::EnumType, "ReferenceEnum::Type",
               "0 1 2 4 8 16",
               "ReferenceEnum::VeryGood ReferenceEnum::Good ReferenceEnum::Average ReferenceEnum::BelowAverage ReferenceEnum::Poor ReferenceEnum::VeryPoor",
               this),
            nestedAggregate("nestedAggregate", this)
         {
            FieldList().push_back(&boolField);
            FieldList().push_back(&int32Field);
            FieldList().push_back(&uint32Field);
            FieldList().push_back(&int64Field);
            FieldList().push_back(&uint64Field);
            FieldList().push_back(&doubleField);
            FieldList().push_back(&stringField);
            FieldList().push_back(&enumField);
            AggList().push_back(&nestedAggregate);
            SyncVersion();
         }

         void ReferenceAggregate::initMetaData(AggregateMetaData  *metaData, AggregateMetaData *nestedAggregateMetaData)
         {
            s_metaData = metaData;
            AggComputeField::initMetaData(nestedAggregateMetaData);
            s_initialized = true;
         }

         AggregateMetaData &ReferenceAggregate::MetaData() const
         {
            return *s_metaData;
         }

      };
   }
}