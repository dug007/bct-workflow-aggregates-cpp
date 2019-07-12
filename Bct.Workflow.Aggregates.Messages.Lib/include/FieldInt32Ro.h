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
            using FieldInt32::Value; // hide set/get
         public:
            FieldInt32Ro() {}
            FieldInt32Ro(const std::string fieldName, const int16_t ver, VersionMetaData &metaData, AbstractAggregate *aggregate) : FieldInt32(fieldName, ver, metaData, aggregate)
            {
            }
            int32_t Value()
            {
               return FieldInt32::Value();
            };
         };
      }
   }
}

