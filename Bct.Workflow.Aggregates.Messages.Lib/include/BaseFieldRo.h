#pragma once

#include "BaseField.h"

namespace Bct
{
   namespace Workflow
   {
      namespace Aggregates
      {
         /// <summary>
         /// Base template class for read-only scalar fields. All read-only scalar fields must derive from this class.
         /// </summary>
         template<class T>
         class BaseFieldRo : public BaseField<T>
         {
         private:
            using BaseField<T>::Value; // hide value set/get
         public:
            /// <summary>
            /// Constructor.
            /// </summary>
            /// <param name="fieldName">Name of this field.</param>
            /// <param name="t">Type of this field. The given type should be consistent with the template class.</param>
            /// <param name="aggregate">The associated aggregate this field is a member of.</param>
            BaseFieldRo(const std::string fieldName, TypeEnum::Type t, AbstractAggregate *aggregate)
               : BaseField<T>(fieldName, t, aggregate)
            {
            }

            virtual ~BaseFieldRo()
            {
            }
            
            const T Value()
            {
               return BaseField<T>::Value();
            };
         };
      }
   }
}

