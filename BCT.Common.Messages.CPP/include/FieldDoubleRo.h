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
            FieldDoubleRo(const std::string fieldName, const int16_t ver, const std::vector<VersionMetaData> &metaData) : FieldDouble(fieldName, ver, metaData) {}  // feature fEmbedMetaData
            const double Value()
            {
               return FieldDouble::Value();
            };
         };
      }
   }
}
