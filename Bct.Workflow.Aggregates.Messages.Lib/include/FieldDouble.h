#pragma once

#include <cinttypes>
#include <vector>
#include "BaseField.h"

namespace Bct
{
   namespace Workflow
   {
      namespace Aggregates
      {
         class FieldDouble : public BaseField<double>
         {
         public:
            FieldDouble(const std::string fieldName,  VersionMetaData &metaData, AbstractAggregate *aggregate) :
               BaseField(fieldName, TypeEnum::DoubleType, metaData, aggregate)
            {
            }
            FieldDouble operator=(const double val)
            {
               this->Value(val);
               return *this;
            }

         };
      }
   }
}
