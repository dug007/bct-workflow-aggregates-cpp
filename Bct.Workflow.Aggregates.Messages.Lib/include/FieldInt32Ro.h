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
            FieldInt32Ro(const std::string fieldName, VersionMetaData &metaData, AbstractAggregate *aggregate)
               : FieldInt32(fieldName, metaData, aggregate)
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

