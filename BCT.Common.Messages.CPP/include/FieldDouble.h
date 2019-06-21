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
            //FieldDouble() {};
            FieldDouble(int16_t ver, std::vector<FieldStateEnum::FieldState> states, std::vector<double> defs) : BaseField(FieldTypeEnum::FieldType::DoubleField, states[ver], defs[ver]) {}
            FieldDouble& operator=(const double val)
            {
               this->Value(val);
               return *this;
            }
         };
      }
   }
}
