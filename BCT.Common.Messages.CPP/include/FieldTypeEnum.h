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
               None,          // Error condition - denotes unassigned field type
               UInt32Field,   // unsigned 32-bit integer
               Int32Field,    // signed 32-bit integer
               UInt64Field,   // unsigned 64-bit integer
               Int64Field,    // signed 64-bit integer
               DoubleField,   // double
               StringField,   // std::string
               BoolField,     // boolean
               EnumField,     // enum
               AggregateField // nested aggregate
            };
         }
      }
   }
}


