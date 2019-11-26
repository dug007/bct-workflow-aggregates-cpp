#pragma once

#include "BaseField.h"
#include "AbstractField.h"

namespace Bct
{
   namespace Workflow
   {
      namespace Aggregates
      {
         /// <summary>
         /// Simple helper to allow exposing ComputedValueString for unit testing
         /// </summary>
         template<class T>
         class TestHelperBaseField : public BaseField<T>
         {
         private:
           
         public:
            /// <summary>
            /// Constructor
            /// </summary>
            /// <param name="fieldId">Field id.</param>
            /// <param name="aggregate">Owner aggregate of this field.</param>
            TestHelperBaseField(int32_t fieldId, AbstractAggregate * const aggregate)
               : BaseField<T>(fieldId, aggregate)
            {
            }

            /// <summary>
            /// Public exposure of ComputedValueString for testing purposes.
            /// </summary>
            /// <param name="val"></param>
            virtual void ComputedValueString(const std::string & val)
            {
               BaseField<T>::ComputedValueString(val);
            }

            /// <summary>
            /// Public exposure of ComputedValueString for testing purposes.
            /// </summary>
            /// <returns>The string representation of field value.</returns>
            virtual std::string ComputedValueString() const
            {
               return BaseField<T>::ComputedValueString();
            }


            virtual ~TestHelperBaseField()
            {
            }
         };
      }
   }
}

