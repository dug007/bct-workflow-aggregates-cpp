#pragma once

#include "FieldDouble.h"

namespace Bct
{
   namespace Workflow
   {
      namespace Aggregates
      {

         class FieldDoubleRo : public FieldDouble
         {
         private:
            using FieldDouble::Value; // hide value set/get
         public:
            FieldDoubleRo()
            {
            }
            FieldDoubleRo(const std::string fieldName, const int16_t ver, VersionMetaData &metaData, AbstractAggregate *aggregate)
               : FieldDouble(fieldName, ver, metaData, aggregate) {}
            const double Value()
            {
               return FieldDouble::Value();
            };
         };
      }
   }
}
