#ifndef Token_H
#define Token_H
#include <string>
#include "TypeEnum.h"
#include "TokenClass.h"
#include <stdint.h>

namespace Bct
{
   namespace RPNEvaluator
   {
      /// <summary>
      /// The class for tokens that can contain data of "any" type as defined in the TypeEnum.h file
      /// Constructors are provided to take values of the types and convert to strings internally
      /// Accessors are provided for the value
      /// It is an attempt to mimic C#'s "object" type
      /// </summary>
      class Token
      {
      public:
         /// <summary>
         /// Constructor
         /// </summary>
         Token();

         /// <summary>
         /// Overloaded constructor that instantiates a token that contains a signed 32-bit integer data type
         /// </summary>
         /// <param name="tok">The variable name as a string</param>
         /// <param name="tokType">The data type of the variable as an enum</param>
         /// <param name="tokClass">An enumeration that classifies the token as either a special variable, a function operator, or a value</param>
         /// <param name="tokVal">The data value of the variable</param>
         Token(const char* tok, Workflow::TypeEnum::Type tokType, int& tokClass, int32_t& tokVal);

         /// <summary>
         /// Overloaded constructor that instantiates a token that contains an unsigned 32-bit integer data type
         /// </summary>
         /// <param name="tok">The variable name as a string</param>
         /// <param name="tokType">The data type of the variable as an enum</param>
         /// <param name="tokClass">An enumeration that classifies the token as either a special variable, a function operator, or a value</param>
         /// <param name="tokVal">The data value of the variable</param>
         Token(const char* tok, Workflow::TypeEnum::Type tokType, int& tokClass, uint32_t& tokVal);

         /// <summary>
         /// Overloaded constructor that instantiates a token that contains a signed 64-bit integer data type
         /// </summary>
         /// <param name="tok">The variable name as a string</param>
         /// <param name="tokType">The data type of the variable as an enum</param>
         /// <param name="tokClass">An enumeration that classifies the token as either a special variable, a function operator, or a value</param>
         /// <param name="tokVal">The data value of the variable</param>
         Token(const char* tok, Workflow::TypeEnum::Type tokType, int& tokClass, int64_t& tokVal);

         /// <summary>
         /// Overloaded constructor that instantiates a token that contains an unsigned 64-bit integer data type
         /// </summary>
         /// <param name="tok">The variable name as a string</param>
         /// <param name="tokType">The data type of the variable as an enum</param>
         /// <param name="tokClass">An enumeration that classifies the token as either a special variable, a function operator, or a value</param>
         /// <param name="tokVal">The data value of the variable</param>
         Token(const char* tok, Workflow::TypeEnum::Type tokType, int& tokClass, uint64_t& tokVal);

         /// <summary>
         /// Overloaded constructor that instantiates a token that contains a double data type
         /// </summary>
         /// <param name="tok">The variable name as a string</param>
         /// <param name="tokType">The data type of the variable as an enum</param>
         /// <param name="tokClass">An enumeration that classifies the token as either a special variable, a function operator, or a value</param>
         /// <param name="tokVal">The data value of the variable</param>
         Token(const char* tok, Workflow::TypeEnum::Type tokType, int& tokClass, double& tokVal);

         /// <summary>
         /// Overloaded constructor that instantiates a token that contains a string data type
         /// </summary>
         /// <param name="tok">The variable name as a string</param>
         /// <param name="tokType">The data type of the variable as an enum</param>
         /// <param name="tokClass">An enumeration that classifies the token as either a special variable, a function operator, or a value</param>
         /// <param name="tokVal">The data value of the variable</param>
         Token(const char* tok, Workflow::TypeEnum::Type tokType, int& tokClass, const char* tokVal);

         /// <summary>
         /// Overloaded constructor that instantiates a token that contains a boolean data type
         /// </summary>
         /// <param name="tok">The variable name as a string</param>
         /// <param name="tokType">The data type of the variable as an enum</param>
         /// <param name="tokClass">An enumeration that classifies the token as either a special variable, a function operator, or a value</param>
         /// <param name="tokVal">The data value of the variable</param>
         Token(const char* tok, Workflow::TypeEnum::Type tokType, int& tokClass, bool& tokVal);

         /// <summary>
         /// Destructor
         /// </summary>
         virtual ~Token();

         /// <summary>
         /// Converts a signed 32-bit integer data type into a string
         /// </summary>
         /// <param name="tokVal">Initial token value as a signed 32-bit integer</param>
         void SetTokValue(int32_t& tokVal);

         /// <summary>
         /// Converts an unsigned 32-bit integer data type into a string
         /// </summary>
         /// <param name="tokVal">Initial token value as an unsigned 32-bit integer</param>
         void SetTokValue(uint32_t& tokVal);

         /// <summary>
         /// Converts a signed 64-bit integer data type into a string
         /// </summary>
         /// <param name="tokVal">Initial token value as a signed 64-bit integer</param>
         void SetTokValue(int64_t& tokVal);

         /// <summary>
         /// Converts an unsigned 64-bit integer data type into a string
         /// </summary>
         /// <param name="tokVal">Initial token value as an unsigend 64-bit integer</param>
         void SetTokValue(uint64_t& tokVal);

         /// <summary>
         /// Converts a double data type into a string
         /// </summary>
         /// <param name="tokVal">Initial token value as a double</param>
         void SetTokValue(double& tokVal);

         /// <summary>
         /// Converts a string data type into a string
         /// </summary>
         /// <param name="tokVal">Initial token value as a string</param>
         void SetTokValue(std::string& tokVal);

         /// <summary>
         /// Converts a boolean data type into a string
         /// </summary>
         /// <param name="tokVal">Initial token value as a boolean</param>
         void SetTokValue(bool& tokVal);

         /// <summary>
         /// Gets the token value
         /// </summary>
         /// <returns> A string representation of the token value</returns>
         std::string GetTokValue();

         /// <summary>
         /// The name of this token variable
         /// </summary>
         std::string Tok;

         /// <summary>
         /// The data type of this token variable
         /// </summary>
         Workflow::TypeEnum::Type TokType;

         /// <summary>
         /// The classification of this token variable which is either a special variable, a function operator, or a data value
         /// </summary>
         int TokClass;

         /// <summary>
         /// The data value of this token variable
         /// </summary>
         std::string TokValue;
      };
   }
}
#endif
