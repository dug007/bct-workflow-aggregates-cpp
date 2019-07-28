#pragma once
namespace Bct
{
   namespace Workflow
   {
      namespace TypeEnum
      {
         enum Type
         {
            EmptyType = 0, // Error condition - denotes unassigned field type
            ObjectType = 1, //object
            BoolType = 2, //boolean
            Int32Type = 3, //signed 32-bit integer
            UInt32Type = 4, //unsigned 32-bit integer
            Int64Type = 5, //signed 64-bit integer
            UInt64Type = 6, //unsigned 64-bit integer
            DoubleType = 7, //double
            StringType = 8, //std::string
            EnumType = 9, //enum
            VariableType = 10, //internal use 
         };

         /// Get the name of a Type value for display
         static const char* TypeName(Type code)
         {
            switch (code)
            {
            case EmptyType:
               return "Empty";
            case ObjectType:
               return "ObjectType";
            case BoolType:
               return "BoolType";
            case Int32Type:
               return "Int32Type";
            case UInt32Type:
               return "UInt32Type";
            case Int64Type:
               return "Int64Type";
            case UInt64Type:
               return "UInt64Type";
            case DoubleType:
               return "DoubleType";
            case StringType:
               return "StringType";
            case EnumType:
               return "EnumType";
            case VariableType:
               return "VariableType";
            default:
               return "Empty";
            }
         }
      }

   };
}