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
            BaseAggregate(BaseAggregate::UseMostRecentVersionStr),
            boolField(0, this), 
            int32Field(1, this), 
            uint32Field(2, this), 
            int64Field(3, this), 
            uint64Field(4, this), 
            doubleField(5, this), 
            stringField(6, this), 
            boolFieldRequiredv2(7, this), 
            enumField(8, "ReferenceEnum::Reference",
            "0 1 2 4 8 16 ",
            "ReferenceEnum::VeryGood ReferenceEnum::Good ReferenceEnum::Average ReferenceEnum::BelowAverage ReferenceEnum::Poor ReferenceEnum::VeryPoor ", this), 
            vectorIntField(9, this), 
            nestedField(10, this), 
            v100Field(11, this), 
            nestedField2(12, this), 
            boolFieldRequiredv0(13, this)
         {
            pushFields();
            syncVersion();
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
            boolFieldRequiredv2(7, this), 
            enumField(8, "ReferenceEnum::Reference",
            "0 1 2 4 8 16 ",
            "ReferenceEnum::VeryGood ReferenceEnum::Good ReferenceEnum::Average ReferenceEnum::BelowAverage ReferenceEnum::Poor ReferenceEnum::VeryPoor ", this), 
            vectorIntField(9, this), 
            nestedField(10, this), 
            v100Field(11, this), 
            nestedField2(12, this), 
            boolFieldRequiredv0(13, this)
          {
            pushFields();
            syncVersion();
          }

         ReferenceAggregate::ReferenceAggregate(int32_t fieldId, BaseAggregate * const parent) :
            BaseAggregate(fieldId, parent),
           boolField(0, this), 
           int32Field(1, this), 
           uint32Field(2, this), 
           int64Field(3, this), 
           uint64Field(4, this), 
           doubleField(5, this), 
           stringField(6, this), 
           boolFieldRequiredv2(7, this), 
           enumField(8, "ReferenceEnum::Reference",
           "0 1 2 4 8 16 ",
           "ReferenceEnum::VeryGood ReferenceEnum::Good ReferenceEnum::Average ReferenceEnum::BelowAverage ReferenceEnum::Poor ReferenceEnum::VeryPoor ", this), 
           vectorIntField(9, this), 
           nestedField(10, this), 
           v100Field(11, this), 
           nestedField2(12, this), 
           boolFieldRequiredv0(13, this)
         {
            pushFields();
            syncVersion();
         }

         ReferenceAggregate::ReferenceAggregate(const ReferenceAggregate & other) :
            BaseAggregate(other),
            boolField(other.boolField, this), 
            int32Field(other.int32Field, this), 
            uint32Field(other.uint32Field, this), 
            int64Field(other.int64Field, this), 
            uint64Field(other.uint64Field, this), 
            doubleField(other.doubleField, this), 
            stringField(other.stringField, this), 
            boolFieldRequiredv2(other.boolFieldRequiredv2, this), 
            enumField(other.enumField, this), 
            vectorIntField(other.vectorIntField, this), 
            nestedField(other.nestedField, this), 
            v100Field(other.v100Field, this), 
            nestedField2(other.nestedField2, this), 
            boolFieldRequiredv0(other.boolFieldRequiredv0, this)
         {
            pushFields();
         }

         ReferenceAggregate::ReferenceAggregate(const ReferenceAggregate & other, BaseAggregate * const parent) :
            BaseAggregate(other, parent),
            boolField(other.boolField, this), 
            int32Field(other.int32Field, this), 
            uint32Field(other.uint32Field, this), 
            int64Field(other.int64Field, this), 
            uint64Field(other.uint64Field, this), 
            doubleField(other.doubleField, this), 
            stringField(other.stringField, this), 
            boolFieldRequiredv2(other.boolFieldRequiredv2, this), 
            enumField(other.enumField, this), 
            vectorIntField(other.vectorIntField, this), 
            nestedField(other.nestedField, this), 
            v100Field(other.v100Field, this), 
            nestedField2(other.nestedField2, this), 
            boolFieldRequiredv0(other.boolFieldRequiredv0, this)
         {
            pushFields();
         }

         ReferenceAggregate & ReferenceAggregate::operator=(const ReferenceAggregate &other)
         {
            if (&other != this)
            {
               BaseAggregate::operator=(other);
               boolField = other.boolField;
               int32Field = other.int32Field;
               uint32Field = other.uint32Field;
               int64Field = other.int64Field;
               uint64Field = other.uint64Field;
               doubleField = other.doubleField;
               stringField = other.stringField;
               boolFieldRequiredv2 = other.boolFieldRequiredv2;
               enumField = other.enumField;
               vectorIntField = other.vectorIntField;
               nestedField = other.nestedField;
               v100Field = other.v100Field;
               nestedField2 = other.nestedField2;
               boolFieldRequiredv0 = other.boolFieldRequiredv0;
            }
            
            return *this;
         }

         bool ReferenceAggregate::operator==(const ReferenceAggregate &other) const
         {
            if (boolField != other.boolField)
            {
               return false;
            }
            if (int32Field != other.int32Field)
            {
               return false;
            }
            if (uint32Field != other.uint32Field)
            {
               return false;
            }
            if (int64Field != other.int64Field)
            {
               return false;
            }
            if (uint64Field != other.uint64Field)
            {
               return false;
            }
            if (doubleField != other.doubleField)
            {
               return false;
            }
            if (stringField != other.stringField)
            {
               return false;
            }
            if (boolFieldRequiredv2 != other.boolFieldRequiredv2)
            {
               return false;
            }
            if (enumField != other.enumField)
            {
               return false;
            }
            if (vectorIntField != other.vectorIntField)
            {
               return false;
            }
            if (nestedField != other.nestedField)
            {
               return false;
            }
            if (v100Field != other.v100Field)
            {
               return false;
            }
            if (nestedField2 != other.nestedField2)
            {
               return false;
            }
            if (boolFieldRequiredv0 != other.boolFieldRequiredv0)
            {
               return false;
            }
            return true;
         }

         bool ReferenceAggregate::operator!=(const ReferenceAggregate &other) const
         {
            return ! (*this == other);
         }

         ReferenceAggregate::~ReferenceAggregate()
         {
         }

         AggregateMetaData & ReferenceAggregate::MetaData() const
         {
            return s_MetaData();
         };

         void ReferenceAggregate::pushFields()
         {
            FieldList().push_back(&boolField);
            FieldList().push_back(&int32Field);
            FieldList().push_back(&uint32Field);
            FieldList().push_back(&int64Field);
            FieldList().push_back(&uint64Field);
            FieldList().push_back(&doubleField);
            FieldList().push_back(&stringField);
            FieldList().push_back(&boolFieldRequiredv2);
            FieldList().push_back(&enumField);
            FieldList().push_back(&vectorIntField);
            AggList().push_back(&nestedField);
            FieldList().push_back(&v100Field);
            AggList().push_back(&nestedField2);
            FieldList().push_back(&boolFieldRequiredv0);
         }

         AggregateMetaData & ReferenceAggregate::s_MetaData()
         {
            static AggregateMetaData tm;
            static bool initialized = false;

            if (!initialized)
            {
               tm.addVersion("v1.0.0");
               tm.addVersion("v1.1.0");

               tm.addField(0, "boolField", TypeEnum::BoolType);
               tm.addField(1, "int32Field", TypeEnum::Int32Type);
               tm.addField(2, "uint32Field", TypeEnum::UInt32Type);
               tm.addField(3, "int64Field", TypeEnum::Int64Type);
               tm.addField(4, "uint64Field", TypeEnum::UInt64Type);
               tm.addField(5, "doubleField", TypeEnum::DoubleType);
               tm.addField(6, "stringField", TypeEnum::StringType);
               tm.addField(7, "boolFieldRequiredv2", TypeEnum::BoolType);
               tm.addField(8, "enumField", TypeEnum::Int32Type);
               tm.addField(9, "vectorIntField", TypeEnum::ArrayType, TypeEnum::Int32Type);
               tm.addAggField(10, "nestedField");
               tm.addField(11, "v100Field", TypeEnum::DoubleType);
               tm.addAggField(12, "nestedField2");
               tm.addField(13, "boolFieldRequiredv0", TypeEnum::BoolType);
               tm.addFieldMetaToAllVersions(0, FieldStateEnum::Default, "true");
               tm.addFieldMetaToAllVersions(1, FieldStateEnum::Default, "-1");
               tm.addFieldMetaToAllVersions(2, FieldStateEnum::Default, "1");
               tm.addFieldMetaToAllVersions(3, FieldStateEnum::Default, "-1");
               tm.addFieldMetaToAllVersions(4, FieldStateEnum::Default, "1");
               tm.addFieldMetaToAllVersions(5, FieldStateEnum::Default, "1");
               tm.addFieldMetaToAllVersions(6, FieldStateEnum::Default, "hello world");
               tm.addFieldMeta(7, FieldStateEnum::NotSet, "notset")
                     .toVersion(1)
               ;
               tm.addFieldMetaToAllVersions(8, FieldStateEnum::Default, "2");
               tm.addFieldMetaToAllVersions(9, FieldStateEnum::NotSet, "notset");
               tm.addAggMetaToAllVersions(10, FieldStateEnum::NotSet, 0);
               tm.addFieldMeta(11, FieldStateEnum::Default, "1")
                     .toVersion(0)
               ;
               tm.addAggMeta(12, FieldStateEnum::NotSet, 0)
                     .toVersion(0)
               ;
               tm.addFieldMeta(13, FieldStateEnum::NotSet, "notset")
                     .toVersion(0)
               ;
               tm.addFieldMeta(7, FieldStateEnum::Unavailable, "notset")
                     .toVersion(0)
               ;
               tm.addFieldMeta(11, FieldStateEnum::Unavailable, "notset")
                     .toVersion(1)
               ;
               tm.addAggMeta(12, FieldStateEnum::Unavailable, 0)
                     .toVersion(1)
               ;
               tm.addFieldMeta(13, FieldStateEnum::Unavailable, "notset")
                     .toVersion(1)
               ;

               tm.addComputeRule("DoubleFieldCompute", 5, "true", "1 3 +")
                     .toVersion(1)
                     .toVersion(0)
               ;

               tm.addAssessmentRule("_requiredInVersion1", "_requiredInVersion", "true", "boolFieldRequiredv2 $HasValue")
                     .toVersion(1)
               ;
               tm.addAssessmentRule("ruleId1", "ruleStringId1", "true", "1 1 +")
                     .toVersion(1)
                     .toVersion(0)
               ;
               tm.addAssessmentRule("_requiredInVersion0", "_requiredInVersion", "true", "boolFieldRequiredv0 $HasValue")
                     .toVersion(0)
               ;

               tm.addVersionChangeRule(5, 0, "doubleField 1 ==", "1 2 +") .toVersion(1);
               tm.addVersionChangeRule(5, 1, "doubleField 1 ==", "1 1 +") .toVersion(0);
               initialized = true;
            }

            return tm;
         }


      }
   }
}

