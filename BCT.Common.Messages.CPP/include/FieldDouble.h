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
            //FieldDouble(int16_t ver, std::vector<FieldStateEnum::FieldState> states, std::vector<double> defs) : BaseField(FieldTypeEnum::FieldType::DoubleField, states[ver], defs[ver]) {}
            FieldDouble(std::string fieldName, int16_t ver, std::vector<VersionMetaData> &metaData) : BaseField(fieldName, FieldTypeEnum::FieldType::DoubleField, ver, metaData) // feature fEmbedMetaData
            {
               FieldStateEnum::FieldState state = State();
               if (state == FieldStateEnum::Constant || state == FieldStateEnum::Default)
               {
                  SetDefault(atof(DefaultStr().c_str()));
               }
            }
            //FieldDouble(FieldStateEnum::FieldState state, double def) : BaseField(FieldTypeEnum::FieldType::DoubleField, state, def) {}
            FieldDouble& operator=(const double val)
            {
               this->Value(val);
               return *this;
            }
            double Default()
            {
               return atof(DefaultStr().c_str());
            }

         };
      }
   }
}
