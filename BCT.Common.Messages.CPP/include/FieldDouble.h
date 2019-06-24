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
         class FieldDouble : public BaseField<double>
         {
         public:
            FieldDouble() {};
            FieldDouble(const std::string fieldName, const int16_t ver, const std::vector<VersionMetaData> &metaData) :
               BaseField(fieldName, FieldTypeEnum::FieldType::DoubleField, ver, metaData)
            {
               FieldStateEnum::FieldState state = State();
               if (state == FieldStateEnum::Constant || state == FieldStateEnum::Default)
               {
                  SetDefault(atof(DefaultStr().c_str()));
               }
            }
            FieldDouble& operator=(const double val)
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
               double out;
               sscanf_s(val.c_str(), "%lf", &out);
               ValueInternal(out);
            }
         };
      }
   }
}
