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
            FieldDouble(const std::string fieldName,  VersionMetaData &metaData, AbstractAggregate *aggregate) :
               BaseField(fieldName, TypeEnum::DoubleType, metaData, aggregate)
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
