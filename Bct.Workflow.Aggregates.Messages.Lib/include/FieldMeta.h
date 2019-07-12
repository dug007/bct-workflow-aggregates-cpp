#pragma once

#include <string>
#include "FieldStateEnum.h"

namespace Bct
{
   namespace Workflow
   {
      namespace Aggregates
      {
         /// <summary>
         /// Metadata for a single field.
         /// </summary>
         class FieldMeta
         {
         public:
            FieldMeta(const std::string fieldName, const FieldStateEnum::FieldState fieldState, const std::string def, int16_t ver) : _fieldName(fieldName), _fieldState(fieldState), _default(def), _ver(ver) {};
            std::string FieldName();
            std::string _default;
            FieldStateEnum::FieldState _fieldState;
            int16_t _ver;

         private:
            std::string _fieldName;
         };

      }
   }
}

