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
            /// <param name="fieldId">Id of this field.</param>
            /// <param name="aggregate">The associated aggregate this field is a member of.</param>
            BaseFieldRo(int32_t fieldId, AbstractAggregate *aggregate)
               : BaseField<T>(fieldId, aggregate)
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

