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
            FieldDoubleRo(const std::string fieldName,  VersionMetaData &metaData, AbstractAggregate *aggregate)
               : FieldDouble(fieldName, metaData, aggregate) {}
            const double Value()
            {
               return FieldDouble::Value();
            };
         };
      }
   }
}
