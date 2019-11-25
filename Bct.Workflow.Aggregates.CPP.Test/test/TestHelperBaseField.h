#pragma once

#include "BaseField.h"
#include "AbstractField.h"

namespace Bct
{
   namespace Workflow
   {
      namespace Aggregates
      {
         template<class T>
         class TestHelperBaseField : public BaseField<T>
         {
         private:
           
         public:
            using AbstractField::computedValueString;
            TestHelperBaseField(int32_t fieldId, AbstractAggregate * const aggregate)
               : BaseField<T>(fieldId, aggregate)
            {
            }

            virtual ~TestHelperBaseField()
            {
            }
         };
      }
   }
}

