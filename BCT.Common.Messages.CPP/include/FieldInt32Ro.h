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
            FieldInt32Ro() {}
            FieldInt32Ro(std::string fieldName, int16_t ver, std::vector<VersionMetaData> &metaData) : FieldInt32(fieldName, ver, metaData) {}  // feature fEmbedMetaData
            //FieldInt32Ro(FieldStateEnum::FieldState state, int32_t def) : FieldInt32(state, def) {}
            //FieldInt32Ro(int16_t ver, std::vector <FieldStateEnum::FieldState> states, std::vector<int32_t> defs) : FieldInt32(ver, states, defs) {}
            int32_t Value()
            {
               return FieldInt32::Value();
            };
         };
      }
   }
}

