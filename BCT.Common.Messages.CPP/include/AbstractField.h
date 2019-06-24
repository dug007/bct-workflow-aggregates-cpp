#pragma once
#include <string>

namespace Bct
{
   namespace Workflow
   {
      namespace Aggregates
      {
         class AbstractField
         {
         public:
            virtual const std::string ValueString() = 0;
            virtual void ValueString(std::string val) = 0;
            virtual const std::string FieldName() = 0;
            virtual const FieldTypeEnum::FieldType FieldType() = 0;
            virtual const FieldStateEnum::FieldState State() = 0;
         };
      }
   }
}
