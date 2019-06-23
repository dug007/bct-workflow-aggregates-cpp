#pragma once

#include <cinttypes>
#include <vector>
#include "BaseField.h"

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
            //FieldInt32(FieldStateEnum::FieldState state, int32_t def) : BaseField(FieldTypeEnum::FieldType::Int32Field, state, def) {}
            FieldInt32(std::string fieldName, int16_t ver, std::vector<VersionMetaData> &metaData) : BaseField(fieldName, FieldTypeEnum::FieldType::Int32Field, ver, metaData)  // feature fEmbedMetaData
            {
               FieldStateEnum::FieldState state = State();
               if (state == FieldStateEnum::Constant || state == FieldStateEnum::Default)
               {
                  SetDefault(atoi(DefaultStr().c_str()));
               }
            }
            //FieldInt32(int16_t ver, std::vector<FieldStateEnum::FieldState> states, std::vector<int32_t> defs) : BaseField(FieldTypeEnum::FieldType::Int32Field, states[ver], defs[ver]) {}
            FieldInt32& operator=(const int32_t val)
            {
               this->Value(val);
               return *this;
            }
         };

      }
   }
}