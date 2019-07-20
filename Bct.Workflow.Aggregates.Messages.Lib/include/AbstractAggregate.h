#pragma once
#pragma once

namespace Bct
{
   namespace Workflow
   {
      namespace Aggregates
      {
         /// <summary>
         /// Abstract base class for aggregates. 
         /// </summary>
         class AbstractAggregate
         {
         public:
            virtual void SyncChildVersion(int16_t parentVer) = 0;

            /// <summary>
            /// Pure virtual function to return the current field set count for this aggregate. 
            /// </summary>
            /// <remarks> 
            /// Implementers should return increasing values each time this function is called. Users of this function
            /// should call this function each time a field in the aggregate is set and use the result to
            /// store an instance copy for that field. The intent is to have a running increasing counter for each field
            /// to determine the order that field setters are used. This is important for calculated fields to decide
            /// which fields are the most recently set.
            /// </remarks> 
            /// <returns>The field set counter incremented by 1 since that last time this function was called.</returns>
            virtual const uint32_t &FieldSetCounter() = 0;
         };
      }
   }
}