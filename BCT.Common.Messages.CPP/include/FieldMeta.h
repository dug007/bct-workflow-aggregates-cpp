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
            FieldMeta() {}
            FieldMeta(std::string fieldName, FieldStateEnum::FieldState fieldState, std::string def) : _fieldName(fieldName), _fieldState(fieldState), _default(def) {};
         private:
            std::string _fieldName;
            FieldStateEnum::FieldState _fieldState;
            std::string _default;
         };

      }
   }
}

