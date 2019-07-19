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
			/// <summary>
			/// Takes the FieldStateEnum value and returns a string
			/// </summary>
			/// <param name="state">Current state of the field</param>
			/// <returns>The string value of the current state of the field</returns>
			static const char* FieldStateString(FieldState state)
			{
				switch (state)
				{
				case Unavailable:
					return "Unavailable";
				case NotSet:
					return "NotSet";
				case Set:
					return "Set";
				case Constant:
					return "Constant";
				case Default:
					return "Default";
				case Computed:
					return "Computed";
				default:
					return "Unavailable";
				}
			}

			
         }
      }
   }
}