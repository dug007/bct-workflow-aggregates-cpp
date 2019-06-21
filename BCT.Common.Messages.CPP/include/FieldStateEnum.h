#pragma once

namespace Bct
{
   namespace Workflow
   {
      namespace Aggregates
      {
         namespace FieldStateEnum
         {
            enum FieldState
            {
               Unavailable,
               NotSet,
               Set,
               Constant,
               Default,
               Computed
            };
         }
      }
   }
}