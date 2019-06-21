#pragma once

#include <cinttypes>
#include <vector>
#include "FieldInt32.h"
#include "FieldStateEnum.h"

namespace Bct
{
   namespace Workflow
   {
      namespace Aggregates
      {
         class FieldInt32Ro : public FieldInt32
         {
         private:
            using FieldInt32::Value;
         public:
            //FieldInt32Ro() {}
            FieldInt32Ro(int16_t ver, std::vector <FieldStateEnum::FieldState> states, std::vector<int32_t> defs) : FieldInt32(ver, states, defs) {}
            int32_t Value()
            {
               return FieldInt32::Value();
            };
         };
      }
   }
}

