#pragma once


namespace Bct
{
   namespace Workflow
   {
      namespace Aggregates
      {
         namespace FieldTypeEnum
         {
            // Note that enums must be usable in C# as well in order to keep them consistent across languages.  We append "Field" to some enum names
            // to avoid overlap with built-in C# types.
            //
            enum FieldType
            {
               None = 0,          // Error condition - denotes unassigned field type
               UInt32Field=1,   // unsigned 32-bit integer
               Int32Field=2,    // signed 32-bit integer
               UInt64Field=3,   // unsigned 64-bit integer
               Int64Field=4,    // signed 64-bit integer
               DoubleField=5,   // double
               StringField=6,   // std::string
               BoolField=7,     // boolean
               EnumField=8,     // enum
               AggregateField=9 // nested aggregate
            };
         }
      }
   }
}


