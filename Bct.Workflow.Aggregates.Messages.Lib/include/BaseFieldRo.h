#pragma once

#include "BaseField.h"

namespace Bct
{
   namespace Workflow
   {
      namespace Aggregates
      {
         template<class T>
         class BaseFieldRo : public BaseField<T>
         {
         private:
            using BaseField<T>::Value; // hide value set/get
         public:
            BaseFieldRo(const std::string fieldName, TypeEnum::Type t, VersionMetaData &metaData, AbstractAggregate *aggregate)
               : BaseField<T>(fieldName, t, metaData, aggregate) {}
            const T Value()
            {
               return BaseField<T>::Value();
            };
         };
      }
   }
}

