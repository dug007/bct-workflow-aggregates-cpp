#include "ProjectEnumerations.h"
#include "AbstractAggregate.h"
#include "BaseAggregate.h"

using namespace Bct::Workflow::Aggregates; 



namespace Bct
{
   namespace Workflow
   {
      namespace Implementation
      {
         ProjectEnumerations::ProjectEnumerations() :
            BaseAggregate(BaseAggregate::UseMostRecentVersionStr),
            simpleReferenceEnumGenerator(0, "SimpleReferenceEnum::SimpleReference",
            "0 1 2 4 8 16 ",
            "SimpleReferenceEnum::VeryGood SimpleReferenceEnum::Good SimpleReferenceEnum::Average SimpleReferenceEnum::BelowAverage SimpleReferenceEnum::Poor SimpleReferenceEnum::VeryPoor ", this)
         {
            pushFields();
            syncVersion();
         }

         ProjectEnumerations::ProjectEnumerations(const std::string &version) :
            BaseAggregate(version),
            simpleReferenceEnumGenerator(0, "SimpleReferenceEnum::SimpleReference",
            "0 1 2 4 8 16 ",
            "SimpleReferenceEnum::VeryGood SimpleReferenceEnum::Good SimpleReferenceEnum::Average SimpleReferenceEnum::BelowAverage SimpleReferenceEnum::Poor SimpleReferenceEnum::VeryPoor ", this)
          {
            pushFields();
            syncVersion();
          }

         ProjectEnumerations::ProjectEnumerations(int32_t fieldId, BaseAggregate * const parent) :
            BaseAggregate(fieldId, parent),
           simpleReferenceEnumGenerator(0, "SimpleReferenceEnum::SimpleReference",
           "0 1 2 4 8 16 ",
           "SimpleReferenceEnum::VeryGood SimpleReferenceEnum::Good SimpleReferenceEnum::Average SimpleReferenceEnum::BelowAverage SimpleReferenceEnum::Poor SimpleReferenceEnum::VeryPoor ", this)
         {
            pushFields();
            syncVersion();
         }

         ProjectEnumerations::ProjectEnumerations(const ProjectEnumerations & other) :
            BaseAggregate(other),
            simpleReferenceEnumGenerator(other.simpleReferenceEnumGenerator, this)
         {
            pushFields();
         }

         ProjectEnumerations::ProjectEnumerations(const ProjectEnumerations & other, BaseAggregate * const parent) :
            BaseAggregate(other, parent),
            simpleReferenceEnumGenerator(other.simpleReferenceEnumGenerator, this)
         {
            pushFields();
         }

         ProjectEnumerations & ProjectEnumerations::operator=(const ProjectEnumerations &other)
         {
            if (&other != this)
            {
               BaseAggregate::operator=(other);
               simpleReferenceEnumGenerator = other.simpleReferenceEnumGenerator;
            }
            
            return *this;
         }

         bool ProjectEnumerations::operator==(const ProjectEnumerations &other) const
         {
            if (simpleReferenceEnumGenerator != other.simpleReferenceEnumGenerator)
            {
               return false;
            }
            return true;
         }

         bool ProjectEnumerations::operator!=(const ProjectEnumerations &other) const
         {
            return ! (*this == other);
         }

         ProjectEnumerations::~ProjectEnumerations()
         {
         }

         AggregateMetaData & ProjectEnumerations::MetaData() const
         {
            return s_MetaData();
         };

         void ProjectEnumerations::pushFields()
         {
            FieldList().push_back(&simpleReferenceEnumGenerator);
         }

         AggregateMetaData & ProjectEnumerations::s_MetaData()
         {
            static AggregateMetaData tm;
            static bool initialized = false;

            if (!initialized)
            {
               tm.addVersion("v1.0.0");

               tm.addField(0, "simpleReferenceEnumGenerator", TypeEnum::Int32Type);
               tm.addFieldMetaToAllVersions(0, FieldStateEnum::NotSet, "notset");



               initialized = true;
            }

            return tm;
         }


      }
   }
}

