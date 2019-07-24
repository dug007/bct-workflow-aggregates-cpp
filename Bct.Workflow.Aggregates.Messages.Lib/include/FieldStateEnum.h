#pragma once

namespace Bct
{
   namespace Workflow
   {
      namespace Aggregates
      {
         /// <summary>
         /// Field state.
         /// </summary>
         namespace FieldStateEnum
         {
            enum FieldState
            {
               /// <summary>
               /// Unavailable for this version.
               /// </summary>
               Unavailable,
               /// <summary>
               /// Field has no defined value.
               /// </summary>
               NotSet,
               /// <summary>
               /// Field has a defined value.
               /// </summary>
               Set,
               /// <summary>
               /// Field has a fixed constant value. Any attempt to change the value will throw and exception.
               /// </summary>
               Constant,
               /// <summary>
               /// Curent value of the field has its default value.
               /// </summary>
               Default,
               /// <summary>
               /// The field currently has a value that has been computed.
               /// </summary>
               Computed
            };
         }
      }
   }
}