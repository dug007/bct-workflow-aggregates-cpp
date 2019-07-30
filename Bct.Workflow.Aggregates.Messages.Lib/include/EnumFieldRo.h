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
         template<class T, class U, class X>
         class EnumFieldRo : public EnumField<U, X>
         {
         private:
            using EnumField<U,X>::Value; // hide value set/get
         public:
            /// <summary>
            /// Constructor.
            /// </summary>
            /// <param name="fieldName">Name of this field.</param>
            /// <param name="t">Type of this field. The given type should be consistent with the template class.</param>
            /// <param name="aggregate">The associated aggregate this field is a member of.</param>
            EnumFieldRo(const std::string fieldName, TypeEnum::Type t, const std::string enumName, const std::string enums, const std::string names, AbstractAggregate *aggregate)
               : EnumField<U, X>(fieldName, t, enumName, enums, names, aggregate)
            {
            }
            const X Value()
            {
               return EnumField<U, X>::Value();
            };
         };
      }
   }
}


