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
            BaseFieldRo(int32_t fieldId, AbstractAggregate * const aggregate)
               : BaseField<T>(fieldId, aggregate)
            {
            }

            /// <summary>
            /// Constructor for coping but not copy constructor.
            /// </summary>
            /// <param name="other">The object being copied.</param>
            /// <param name="aggregate">The associated aggregate this field is a member of.</param>
            BaseFieldRo(const BaseFieldRo &other, AbstractAggregate * const aggregate)
               : BaseField<T>(other, aggregate)
            {
            }

            virtual ~BaseFieldRo()
            {
            }

            /// <summary>
            /// Gets the read-only value.
            /// </summary>
            /// <returns>Value.</returns>
            const T Value()
            {
               return BaseField<T>::Value();
            };
         };
      }
   }
}

