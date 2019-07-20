#pragma once
#include "BaseAggregate.h"
#include "BaseField.h"
#include "AggregateMetaData.h"
#include "AggComputeField.h"

namespace Bct
{
   namespace Workflow
   {
      namespace Aggregates
      {
         class AggNested : public BaseAggregate
         {
         private:
            static AggregateMetaData *s_metaData;
            static bool s_initialized;

         public:

            BaseField<int32_t>   intField1;
            BaseField<int32_t>   intField2;
            AggComputeField      aggField;

            AggNested();
            AggNested(const std::string &version);
            static void initMetaData(AggregateMetaData  *metaData, AggregateMetaData *field3MetaData);

            AggComputeField aggComputeField;
         };
      }
   }
}

