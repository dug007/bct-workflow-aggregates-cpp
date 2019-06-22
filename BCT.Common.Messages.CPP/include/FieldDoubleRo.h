#pragma once

#include "FieldDouble.h"

namespace Bct
{
   namespace Workflow
   {
      namespace Aggregates
      {

         class FieldDoubleRo : public FieldDouble
         {
         private:
            using FieldDouble::Value;
         public:
            FieldDoubleRo()
            {
            }
            FieldDoubleRo(FieldStateEnum::FieldState state, double def) : FieldDouble(state, def) {}
            //FieldDoubleRo(int16_t ver, std::vector<FieldStateEnum::FieldState> states, std::vector<double> defs) : FieldDouble(ver, states, defs) {}
            double Value()
            {
               return FieldDouble::Value();
            };
         };
      }
   }
}
