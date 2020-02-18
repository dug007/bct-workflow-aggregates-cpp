#pragma once
#include "BaseAggregate.h"
#include "BaseField.h"
#include "AggregateMetaData.h"
#include "AssessMetaData.h"
#include "AbstractAggregate.h"

using namespace Bct::Workflow::Aggregates;

namespace Bct
{
   namespace Workflow
   {
      namespace Implementation
      {
         class AggAssess : public BaseAggregate
         {
         private:
            static AssessMetaData s_meta;

            static AggregateMetaData *s_metaData;
            static bool s_initialized;

         public:
            BaseField<int32_t>   field1;
            BaseField<int32_t>   field2;

            AggAssess();
            AggAssess(const std::string &version);
            AggregateMetaData &MetaData() const;
            static void bindMetaData(AggregateMetaData *metaData);

         private:
         };
      }
   }
}

