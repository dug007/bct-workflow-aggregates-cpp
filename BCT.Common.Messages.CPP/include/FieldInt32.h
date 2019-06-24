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
            FieldInt32(const std::string fieldName, const int16_t ver, const std::vector<VersionMetaData> &metaData) : BaseField(fieldName, FieldTypeEnum::FieldType::Int32Field, ver, metaData)  // feature fEmbedMetaData
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
            virtual const std::string ValueString()
            {
               std::stringstream ss;
               ss << Value();
               return ss.str();
            }
            virtual void ValueString(std::string val)
            {
               int32_t out;
               sscanf_s(val.c_str(), "%d", &out);
               ValueInternal(out);
            }
         };

      }
   }
}