#include "SimpleAggregate.h"
#include "AbstractAggregate.h"
#include "BaseAggregate.h"

using namespace Bct::Workflow::Aggregates;



namespace Bct
{
   namespace Workflow
   {
      namespace Implementation
      {
         SimpleAggregate::SimpleAggregate() :
            BaseAggregate(BaseAggregate::UseMostRecentVersionStr),
            doubleValue(0, this)
         {
            pushFields();
            syncVersion();
         }

         SimpleAggregate::SimpleAggregate(const std::string &version) :
            BaseAggregate(version),
            doubleValue(0, this)
          {
            pushFields();
            syncVersion();
          }

         SimpleAggregate::SimpleAggregate(int32_t fieldId, BaseAggregate * const parent) :
            BaseAggregate(fieldId, parent),
           doubleValue(0, this)
         {
            pushFields();
            syncVersion();
         }

         SimpleAggregate::SimpleAggregate(const SimpleAggregate & other) :
            BaseAggregate(other),
            doubleValue(other.doubleValue, this)
         {
            pushFields();
         }

         SimpleAggregate::SimpleAggregate(const SimpleAggregate & other, BaseAggregate * const parent) :
            BaseAggregate(other, parent),
            doubleValue(other.doubleValue, this)
         {
            pushFields();
         }

         SimpleAggregate & SimpleAggregate::operator=(const SimpleAggregate &other)
         {
            if (&other != this)
            {
               BaseAggregate::operator=(other);
               doubleValue = other.doubleValue;
            }
            
            return *this;
         }

         bool SimpleAggregate::operator==(const SimpleAggregate &other) const
         {
            if (doubleValue != other.doubleValue)
            {
               return false;
            }
            return true;
         }

         bool SimpleAggregate::operator!=(const SimpleAggregate &other) const
         {
            return ! (*this == other);
         }

         SimpleAggregate::~SimpleAggregate()
         {
         }

         AggregateMetaData & SimpleAggregate::MetaData() const
         {
            return s_MetaData();
         };

         void SimpleAggregate::pushFields()
         {
            FieldList().push_back(&doubleValue);
         }

         AggregateMetaData & SimpleAggregate::s_MetaData()
         {
            static AggregateMetaData tm;
            static bool initialized = false;

            if (!initialized)
            {
               tm.addVersion("v1.0.0");

               tm.addField(0, "doubleValue", TypeEnum::DoubleType);
               tm.addFieldMetaToAllVersions(0, FieldStateEnum::NotSet, "notset");



               initialized = true;
            }

            return tm;
         }


      }
   }
}

