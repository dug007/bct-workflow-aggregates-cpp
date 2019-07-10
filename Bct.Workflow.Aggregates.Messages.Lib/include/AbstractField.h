#pragma once
#include <string>

namespace Bct
{
   namespace Workflow
   {
      namespace Aggregates
      {
         /*!
          * Abstract base class for fields.
          * 
          */
         class AbstractField
         {
         public:
            /*!
             * Pure virtual function to return the name of this field as constructed.
             * 
             * \return The name of this field.
             */
            virtual const std::string FieldName() = 0;
            /*!
             * Pure virtual function to return the type enum of this field.
             * 
             * \return Type enum of this field.
             */
            virtual const TypeEnum::Type Type() = 0;
            /*!
             * Pure virtual function the return the field state of this field.
             * 
             * \return The field state of this field.
             */
            virtual const FieldStateEnum::FieldState State() = 0;
            /*!
             * Pure virtual function to return the current field set counter value. Implementers should just return
             * the current value of the field set counter. The field set counter is increased each time this field is
             * set, and this function just returns the current value.
             * 
             * \return The current field set counter for this field.
             */
            virtual const uint32_t FieldSetCounter() = 0;
         protected:
            /*!
             * Virtual function to return the string representation of the value of this field. This function is
             * intended to be used internally for evaluating RPN expressions and not for public set/get operations.
             * Implementers should convert this field value to its string representation, and the only friend that uses
             * this function is the BaseAggregate, which needs this function for RPN calculations.
             * \return The string representation of the value of this field.
             */
            virtual const std::string ComputedValueString() = 0;
            /*!
             * Virtual function to set the value of this field using its string representation. This function is
             * intended to be used internally for evaluating RPN expressions and not for public set/get operations.
             * Implementers should convert the string val to the value for this field. The only friend that uses
             * this function is the BaseAggregate, which needs this function for RPN calculations.
             * \param val The string representation of the value of this field.
             */
            virtual void ComputedValueString(std::string val) = 0;
            friend class BaseAggregate;

         private:
            virtual FieldStateEnum::FieldState &StateRef() = 0;

         };
      }
   }
}
