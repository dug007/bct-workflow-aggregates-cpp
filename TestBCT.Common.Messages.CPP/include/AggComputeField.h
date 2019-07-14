#pragma once
#include "BaseAggregate.h"
#include "BaseField.h"
#include "VersionMetaData.h"

namespace Bct
{
   namespace Workflow
   {
      namespace Aggregates
      {
         class AggComputeField : public BaseAggregate
         {
         private:
            void initMetaData();
            static VersionMetaData s_metaData;
            static bool s_initialized;

         public:

            BaseField<int32_t>   field1;

            AggComputeField();
            AggComputeField(const std::string version);
         };
      }
   }
}

