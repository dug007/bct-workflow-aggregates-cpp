#pragma once
#include "BaseAggregate.h"
#include "BaseField.h"
#include "AggregateMetaData.h"
#include "AggComputeField.h"
#include "AbstractAggregate.h"
#include "EnumField.h"
#include "ReferenceEnum.h"
#include "AggComputeField.h"

namespace Bct
{
   namespace Workflow
   {
      namespace Aggregates
      {
         class ReferenceAggregate : public BaseAggregate
         {
         private:
            static ReferenceAggregate *s_metaData;
            static bool s_initialized;

         public:
            BaseField<bool>                     boolField;
            BaseField<int32_t>                  int32Field;
            BaseField<uint32_t>                 uint32Field;
            BaseField<uint32_t>                 int64Field;
            BaseField<int64_t>                  uint64Field;
            BaseField<double>                   doubleField;
            BaseField<std::string>              stringField;
            EnumField<ReferenceEnum::Reference, uint16_t> enumField;
            AggComputeField                     nestedAggregate;

            ReferenceAggregate();
            ReferenceAggregate(const std::string &version);
            static void initMetaData(AggregateMetaData  *metaData, AggregateMetaData *field3MetaData);

            virtual AggregateMetaData &MetaData() const;
         };
      }
   }
}

