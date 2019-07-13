#pragma once

#include <cinttypes>
#include <vector>
#include "BaseField.h"
#include "AbstractAggregate.h"

namespace Bct
{
   namespace Workflow
   {
      namespace Aggregates
      {
         class FieldInt32 : public BaseField<int32_t>
         {
         public:
            FieldInt32(const std::string fieldName, VersionMetaData &metaData, AbstractAggregate *aggregate)
               : BaseField(fieldName, TypeEnum::Type::Int32Type, metaData, aggregate)  
            {
               const FieldStateEnum::FieldState state = State();
               if (state == FieldStateEnum::Constant || state == FieldStateEnum::Default)
               {
                  SetDefault(atoi(DefaultStr().c_str()));
               }
            }

            FieldInt32& operator=(const int32_t val)
            {
               this->Value(val);
               return *this;
            }
         };

      }
   }
}