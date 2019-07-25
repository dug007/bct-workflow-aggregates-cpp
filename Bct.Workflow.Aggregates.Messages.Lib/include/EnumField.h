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
         template<class T, class U>
         class EnumField : public BaseField<U>
         {
         public:
            /// <summary>
            /// Constructor. 
            /// </summary>
            /// <param name="fieldName">Name of this field.</param>
            /// <param name="aggregate">The associated aggregate this field is a member of.</param>
            EnumField(const std::string fieldName, TypeEnum::Type t, const std::string enumName, const std::string enums, const std::string names, AbstractAggregate *aggregate)
               : BaseField<U>(fieldName, t, aggregate), _enumName(enumName)
            {
               // TODO parse enums into _enumNames and _enums and support RPN evaluator - Story 128470
            }

            /// <summary>
            /// Set the value of this field.
            /// </summary>
            /// <param name="v">Value to give this field.</param>
            void Value(const T &v)
            {
               U c = v;
               BaseField<U>::Value(c);
            }

            /// <summary>
            /// Get the value of this field.
            /// </summary>
            /// <returns>The value of this field.</returns>
            T Value() const
            {
               T r = static_cast<T>(BaseField<U>::Value());
               return r;
            }

            U operator=(const T &val)
            {
               this->Value(val);
               return *this;
            }

         private:
            std::string _enumName;
            std::vector<std::string> _enumNames;
            std::vector<U> _enums;
         };
      }
   }
}
