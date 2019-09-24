#pragma once
#include "BaseAggregate.h"
#include "BaseField.h"
#include "AggregateMetaData.h"
#include "AggComputeField.h"
#include "AbstractAggregate.h"
#include "EnumField.h"
#include "TypeEnum.h"
#include "StringField.h"



namespace Bct
{
   namespace Workflow
   {
      namespace Implementation
      {
         class AggNested : public BaseAggregate
         {
         private:
            static AggregateMetaData *s_metaData;
            static bool s_initialized;

         public:

            BaseField<int32_t>                  intField1;
            BaseField<int32_t>                  intField2;
            AggComputeField                     aggField;
            AggComputeField                     aggFieldV2;
            EnumField<int32_t, TypeEnum::Type>  enumField;
            StringField                         stringField;

            AggNested();
            AggNested(const std::string &version);
            AggNested(AggNested &other);
            AggNested & operator=(const AggNested &other);
            void pushFields();
            static void bindMetaData(AggregateMetaData  *metaData, AggregateMetaData *field3MetaData);

            virtual AggregateMetaData &MetaData() const;

            AggComputeField aggComputeField;
         };
      }
   }
}

