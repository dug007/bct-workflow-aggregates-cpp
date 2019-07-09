#pragma once
#include <string>

namespace Bct
{
   namespace Workflow
   {
      namespace Aggregates
      {
         class AbstractField
         {
         public:
            virtual const std::string FieldName() = 0;
            virtual const TypeEnum::Type Type() = 0;
            virtual const FieldStateEnum::FieldState State() = 0;
            virtual const uint32_t FieldSetCounter() = 0;
         protected:
            virtual const std::string ComputedValueString() = 0;
            virtual void ComputedValueString(std::string val) = 0;
            friend class BaseAggregate;

         private:
            virtual FieldStateEnum::FieldState &StateRef() = 0;

         };
      }
   }
}
