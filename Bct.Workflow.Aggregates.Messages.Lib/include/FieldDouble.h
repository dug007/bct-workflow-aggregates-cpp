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
            FieldDouble(const std::string fieldName, const int16_t ver, const std::vector<VersionMetaData> &metaData, AbstractAggregate *aggregate) :
               BaseField(fieldName, TypeEnum::DoubleType, ver, metaData, aggregate)
            {
               FieldStateEnum::FieldState state = State();
               if (state == FieldStateEnum::Constant || state == FieldStateEnum::Default)
               {
                  SetDefault(atof(DefaultStr().c_str()));
               }
            }
            FieldDouble operator=(const double val)
            {
               this->Value(val);
               return *this;
            }

         };
      }
   }
}
