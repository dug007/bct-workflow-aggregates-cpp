#pragma once
#include <string>
#include "TypeCode.h"

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
            virtual const FieldTypeEnum::FieldType FieldType() = 0;
            virtual const BCTCommonUtilitiesRPNEvaluatorCPPWin::TypeCode TypeCode() = 0;
            virtual const FieldStateEnum::FieldState State() = 0;
            virtual const int16_t FieldSetCounter() = 0;
         protected:
            virtual const std::string ComputedValueString() = 0;
            virtual void ComputedValueString(std::string val) = 0;
            friend class BaseAggregate;
         };
      }
   }
}
