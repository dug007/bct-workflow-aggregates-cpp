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
            FieldInt32()
            {
            }

            FieldInt32(const std::string fieldName, const int16_t ver, const std::vector<VersionMetaData> &metaData, AbstractAggregate *aggregate) : BaseField(fieldName, TypeEnum::Type::Int32Type, ver, metaData, aggregate)  
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