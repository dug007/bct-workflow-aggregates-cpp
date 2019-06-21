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
            FieldMeta(FieldStateEnum::FieldState fieldState, std::string def) : _fieldState(fieldState), _default(def) {};
         private:
            FieldStateEnum::FieldState _fieldState;
            std::string _default;
         };

      }
   }
}

