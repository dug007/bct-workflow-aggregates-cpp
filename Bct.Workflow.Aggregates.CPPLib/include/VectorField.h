#pragma once
#include <string>
#include <iostream>
#include "BaseField.h"

namespace Bct
{
   namespace Workflow
   {
      namespace Aggregates
      {
         /// <summary>
         /// Field of type std::vector<T>. This field derives from BaseField to simplify serialization.
         /// </summary>
         template<class T>
         class VectorField : public BaseField<std::vector<T>>
         {
         public:
            /// <summary>
            /// Constructor.
            /// </summary>
            /// <param name="fieldId">Field id in aggregate.</param>
            /// <param name="aggregate">The parent aggregate.</param>
            VectorField(int32_t fieldId, AbstractAggregate * const aggregate)
               : BaseField<std::vector<T>>(fieldId, aggregate)
            {              
            }

            /// <summary>
            /// Constructor for copying but not copy constructor.
            /// </summary>
            /// <param name="other">Object being copied.</param>
            /// <param name="aggregate">The parent aggregate.</param>
            VectorField(const VectorField &other, AbstractAggregate * const aggregate) :
               BaseField<std::vector<T>>(other, aggregate)
            {

            }

            /// <summary>
            /// Destructor
            /// </summary>
            virtual ~VectorField()
            {
            };

            /// <summary>
            /// Set the value of this field.
            /// </summary>
            /// <param name="v">Value to give this field.</param>
            void Value(const std::vector<T> &v)
            {
               BaseField<std::vector<T>>::Value(v);
            }

            /// <summary>
            /// Get the value of this field.
            /// </summary>
            /// <returns>The value of this field.</returns>
            std::vector<T> Value() const
            {
               std::vector<T> r = BaseField<std::vector<T>>::Value(); // TODO
               return r;
            }

            /// <summary>
            /// Assignment operator
            /// </summary>
            /// <param name="fld">Other assigning from.</param>
            /// <returns>Reference to assigned.</returns>
            VectorField & operator=(const VectorField & fld)
            {
               if (&fld != this)
               {
                  BaseField<std::vector<T>>::operator=(fld);
               }
               return *this;
            }

            /// <summary>
            /// Assignment operator.
            /// </summary>
            /// <param name="val">Value assigning from..</param>
            /// <returns>The underlying value of the field.<T></returns>
            std::vector<T> operator=(const std::vector<T> &val)
            {
               this->Value(val);
               return *this;
            }

            /// <summary>
            /// Conversion to external.
            /// </summary>
            /// <returns>External representation.</returns>
            operator std::vector<T>() const
            {
               return this->Value();
            }          
          
            /// <summary>
            /// Virtual function to get value of this vector in its string representation. This function is
            /// intended to be used internally for evaluating RPN expressions and not for public set/get operations.
            /// </summary>
            /// <returns>The string representation of the value of this vector.</returns>
            virtual std::string ComputedValueString()
            {
               //return BaseField<std::vector<T>>::ComputedValueString();
               return "";
            };

            /// <summary>
            /// Virtual function to set the value of this field using its string representation. This function is
            /// intended to be used internally for evaluating RPN expressions and not for public set/get operations.
            /// </summary>
            /// <param name="val">The string representation of the value of this field.</param>
            virtual void ComputedValueString(const std::string &val)
            {
               //BaseField<std::vector<T>>::ComputedValueString(val);
            };
         };
      }
   }
}
