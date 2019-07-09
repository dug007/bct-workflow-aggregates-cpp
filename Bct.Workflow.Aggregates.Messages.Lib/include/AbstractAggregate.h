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
            virtual uint32_t FieldSetCounter() = 0;
         };
      }
   }
}