#pragma once

#include <string>
#include "FieldStateEnum.h"

namespace Bct
{
   namespace Workflow
   {
      namespace Aggregates
      {
         class FieldMeta
         {
         public:
            FieldMeta(const std::string fieldName, const FieldStateEnum::FieldState fieldState, const std::string def) : _fieldName(fieldName), _fieldState(fieldState), _default(def) {};
            std::string FieldName();
            std::string _default;
            FieldStateEnum::FieldState _fieldState;

         private:
            std::string _fieldName;
         };

      }
   }
}

