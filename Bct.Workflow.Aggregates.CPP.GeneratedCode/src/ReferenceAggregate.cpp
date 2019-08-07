#include "ReferenceAggregate.h"

#include "AbstractAggregate.h"
#include "BaseAggregate.h"

using namespace Bct::Workflow::Aggregates;

namespace Bct
{
   namespace Workflow
   {
      namespace Implementation
      {
         ReferenceAggregate::ReferenceAggregate() :
            ReferenceAggregate(BaseAggregate::UseMostRecentVersionStr)
         {
         }

         ReferenceAggregate::ReferenceAggregate(const std::string &version) :
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

            syncVersion();
         }

         ReferenceAggregate::~ReferenceAggregate()
         {
         }

         AggregateMetaData & ReferenceAggregate::MetaData() const
         {
            return s_MetaData();
         };

         AggregateMetaData & ReferenceAggregate::s_MetaData()
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

               tm.addFieldMetaToAllVersions(0, FieldStateEnum::Default, "true");
               tm.addFieldMetaToAllVersions(1, FieldStateEnum::Default, "-1");
               tm.addFieldMetaToAllVersions(2, FieldStateEnum::Default, "1");
               tm.addFieldMetaToAllVersions(3, FieldStateEnum::Default, "-1");
               tm.addFieldMetaToAllVersions(4, FieldStateEnum::Default, "1");
               tm.addFieldMetaToAllVersions(5, FieldStateEnum::Default, "1.0");
               tm.addFieldMetaToAllVersions(6, FieldStateEnum::Default, "hello world");
               tm.addFieldMetaToAllVersions(7, FieldStateEnum::Default, "2");

               initialized = true;
            }

            return tm;
         }
      };
   }
}