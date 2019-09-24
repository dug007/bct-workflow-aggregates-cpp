#pragma once

#include "EnumField.h"

namespace Bct
{
   namespace Workflow
   {
      namespace Aggregates
      {
         /// <summary>
         /// Base template class for read-only enum class. All read-only enum fields must derive from this class.
         /// </summary>
         template<class U, class X>
         class EnumFieldRo : public EnumField<U, X>
         {
         private:
            using EnumField<U,X>::Value; // hide value set/get
            using EnumField<U, X>::unset;
         public:
            /// <summary>
            /// Constructor.
            /// </summary>
            /// <param name="fieldId">Id of this field.</param>
            /// <param name="aggregate">The associated aggregate this field is a member of.</param>
            EnumFieldRo(int32_t fieldId, const std::string enumName, const std::string enums, const std::string names, AbstractAggregate * const aggregate)
               : EnumField<U, X>(fieldId, enumName, enums, names, aggregate)
            {
            }

            /// <summary>
            /// Constructor for copying but not copy constructor.
            /// </summary>
            /// <param name="other">Object being copied.</param>
            /// <param name="aggregate">The associated aggregate this field is a member of.</param>
            EnumFieldRo(const EnumFieldRo &other, AbstractAggregate * const aggregate)
               : EnumField<U, X>(other, aggregate)
            {
            }

            /// <summary>
            /// Virtual destructor.
            /// </summary>
            virtual ~EnumFieldRo()
            {
            }

            /// <summary>
            /// Assignment operator.
            /// </summary>
            /// <param name="fld">Other to assign from.</param>
            /// <returns>Reference to assigned to.</returns>
            EnumFieldRo & operator=(const EnumFieldRo & fld)
            {
               if (&fld != this)
               {
                  EnumField<U,X>::operator=(fld);
               }
               return *this;
            }

            /// <summary>
            /// Gets numeric value.
            /// </summary>
            /// <returns>Numeric value of enumeration.</returns>
            const X Value()
            {
               return EnumField<U, X>::Value();
            };
         };
      }
   }
}


