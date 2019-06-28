#pragma once

namespace Bct
{
   namespace Workflow
   {
      namespace Aggregates
      {
         class AbstractAggregate
         {
         public:
            virtual int16_t FieldSetCounter() = 0;
         };
      }
   }
}