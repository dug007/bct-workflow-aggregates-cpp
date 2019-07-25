#pragma once
namespace Bct
{
   namespace Workflow
   {
      namespace ReferenceEnum
      {
         enum Reference
         {
            VeryGood = 0,      // very good description
            Good = 1,          // good description
            Average = 2,       // average description
            BelowAverage = 4,  // below description
            Poor = 8,          // poor description
            VeryPoor = 16      // very poor description
         };
      }
   }
}