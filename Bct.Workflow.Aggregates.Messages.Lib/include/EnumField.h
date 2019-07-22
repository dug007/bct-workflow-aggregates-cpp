#pragma once
#include "BaseField.h"

namespace Bct
{
   namespace Workflow
   {
      namespace Aggregates
      {
         /// <summary>
         /// Enumeration wrapper for fields. Enumeration is coerced to and from int32 values, so to the system
         /// below this wrapper the enum value looks like an int32.
         /// </summary>
         template<class T>
         class EnumField : public BaseField<int32_t>
         {
         public:
            /// <summary>
            /// Constructor. 
            /// </summary>
            /// <param name="fieldName">Name of this field.</param>
            /// <param name="aggregate">The associated aggregate this field is a member of.</param>
            EnumField(const std::string fieldName, AbstractAggregate *aggregate)
               : BaseField<int32_t>(fieldName, TypeEnum::Int32Type, aggregate)
            {
            }

            /// <summary>
           /// Set the value of this field.
           /// </summary>
           /// <param name="v">Value to give this field.</param>
            void Value(const T &v)
            {
               int32_t c = v;
               BaseField<int32_t>::Value(c);
            }

            /// <summary>
            /// Get the value of this field.
            /// </summary>
            /// <returns>The value of this field.</returns>
            T Value() const
            {
               T r = static_cast<T>(BaseField<int32_t>::Value());
               return r;
            }
         };
      }
   }
}
