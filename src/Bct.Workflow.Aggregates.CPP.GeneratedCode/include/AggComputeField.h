#pragma once
#include "BaseAggregate.h"
#include "BaseField.h"
#include "AggregateMetaData.h"
#include "StringField.h"

using namespace Bct::Workflow::Aggregates;

namespace Bct
{
   namespace Workflow
   {
      namespace Implementation
      {
         /// <summary>
         /// Aggregate for ComputeRuleVersion unit test. This provides a simple 2-field aggregate to test at different versions in metadata.
         /// This class also demonstrates an alternative to other sample unit tests that allows metadata to be initialized separately from the aggregate.
         /// The key difference from other code generation samples is that the VersionMetaData is a pointer rather than a reference. 
         /// </summary>
         class AggComputeField : public BaseAggregate
         {
         private:
            static AggregateMetaData *s_metaData;
            static bool s_initialized;

         public:

            BaseField<int32_t>   field1;
            BaseField<int32_t>   field2;
            StringField          stringField;

            AggComputeField();
            AggComputeField(const std::string &version);
            AggComputeField(int32_t fieldId, BaseAggregate * parent);
            AggComputeField(AggComputeField &other, BaseAggregate *parent);
            AggComputeField & operator=(const AggComputeField &other);
            static void bindMetaData(AggregateMetaData *metaData);
            AggregateMetaData &MetaData() const;
         };
      }
   }
}

