#pragma once

#include <string>
#include "TypeEnum.h"

namespace Bct
{
   namespace Workflow
   {
      namespace Aggregates
      {
         class FieldInfo
         {
         public:
            FieldInfo(int16_t fieldId, std::string const &fieldName, TypeEnum::Type const &fieldType);
            int16_t FieldId() const;
            std::string FieldName() const;
            TypeEnum::Type FieldType() const;

         private:
            int16_t _fieldId;
            std::string _fieldName;
            TypeEnum::Type _fieldType;
         };
      }
   }
}
