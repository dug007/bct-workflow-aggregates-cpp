#pragma once
#include <string>

namespace Bct
{
   namespace Workflow
   {
      namespace Aggregates
      {
         /// <summary>
         /// Abstract base class for fields.
         /// </summary>
         class AbstractField
         {
         public:
            /// <summary>
            /// Pure virtual function to return the name of this field as constructed.
            /// </summary>
            /// <returns>The name of this field.</returns>
            virtual const std::string FieldName() const = 0;
            /// <summary>
            /// Pure virtual function to return the type enum of this field.
            /// </summary>
            /// <returns>Type enum of this field.</returns>
            virtual const TypeEnum::Type Type() const = 0;
            /// <summary>
            /// Pure virtual function the return the field state of this field.
            /// </summary>
            /// <returns>The field state of this field.</returns>
            virtual const FieldStateEnum::FieldState State() const = 0;
            /// <summary>
            /// Pure virtual function to return the current field set counter value. Implementers should just return
            /// the current value of the field set counter. The field set counter is increased each time this field is
            /// set, and this function just returns the current value.
            /// </summary>
            /// <returns>The current field set counter for this field.</returns>
            virtual const uint32_t FieldSetCounter() = 0;
         protected:
            /// <summary>
            /// Virtual function to return the string representation of the value of this field. This function is
            /// intended to be used internally for evaluating RPN expressions and not for public set/get operations.
            /// Implementers should convert this field value to its string representation, and the only friend that uses
            /// this function is the BaseAggregate, which needs this function for RPN calculations.
            /// </summary>
            /// <returns>The string representation of the value of this field.</returns>
            virtual const std::string ComputedValueString() const = 0;
            /// <summary>
            /// Virtual function to set the value of this field using its string representation. This function is
            /// intended to be used internally for evaluating RPN expressions and not for public set/get operations.
            /// Implementers should convert the string val to the value for this field. The only friend that uses
            /// this function is the BaseAggregate, which needs this function for RPN calculations.
            /// </summary>
            /// <param name="val">The string representation of the value of this field.</param>
            virtual void ComputedValueString(std::string val) = 0;
            friend class BaseAggregate;

         private:
            virtual FieldStateEnum::FieldState &StateRef() const = 0;

         };
      }
   }
}
