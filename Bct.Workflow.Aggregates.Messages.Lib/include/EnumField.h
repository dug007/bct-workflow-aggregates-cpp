#pragma once
#include <string>
#include <iostream>
#include "BaseField.h"

namespace Bct
{
   namespace Workflow
   {
      namespace Aggregates
      {
         /// <summary>
         /// Enumeration wrapper for fields. U is the underlying type. X is the enum being wrapped.
         /// 
         /// This serves dual purposes: 1- integrate into aggregates 2-provide name resolution via the configured metadata.
         /// </summary>
         template<class U, class X>
         class EnumField : public BaseField<U>
         {
         private:
            std::vector<std::string> split(const std::string& s, char delimiter)
            {
               std::vector<std::string> tokens;
               std::string token;
               std::istringstream tokenStream(s);
               while (std::getline(tokenStream, token, delimiter))
               {
                  tokens.push_back(token);
               }
               return tokens;
            }

            std::vector<std::string> splitU(const std::string& s, char delimiter)
            {
               std::vector<std::string> tokens;
               std::string token;
               std::istringstream tokenStream(s);
               while (std::getline(tokenStream, token, delimiter))
               {
                  tokens.push_back(token);
               }
               return tokens;
            }

         public:
            /// <summary>
            /// Constructor.
            /// </summary>
            /// <param name="fieldName">Field name in aggregate.</param>
            /// <param name="t">TypeEnum::Type - of field being used internally by BaseField. This should correspond to the U type of the template.</param>
            /// <param name="enumName">String name of the wrapped enum.</param>
            /// <param name="enums">String with list of values being wrapped separated by spaces.</param>
            /// <param name="names">String with list of names being wrapped separated by spaces.</param>
            /// <param name="aggregate">The parent aggregate.</param>
            EnumField(const std::string fieldName, TypeEnum::Type t, const std::string enumName, const std::string enums, const std::string names, AbstractAggregate *aggregate)
               : BaseField<U>(fieldName, t, aggregate), _enumName(enumName)
            {
               // TODO parse enums into _enumNames and _enums and support RPN evaluator - Story 128470
               _enumNames = split(names, ' ');
               _enums = splitU(enums, ' ');
            }

            /// <summary>
            /// Set the value of this field.
            /// </summary>
            /// <param name="v">Value to give this field.</param>
            void Value(const X &v)
            {
               U c = v;
               BaseField<U>::Value(c);
            }

            /// <summary>
            /// Get the value of this field.
            /// </summary>
            /// <returns>The value of this field.</returns>
            X Value() const
            {
               X r = static_cast<X>(BaseField<U>::Value());
               return r;
            }

            /// <summary>
            /// Assignment operator.
            /// </summary>
            /// <param name="val">Value.</param>
            /// <returns>Coerced to integer.</returns>
            U operator=(const X &val)
            {
               this->Value(val);
               return *this;
            }

            /// <summary>
            /// Returns the name of the enumeration value as configured by the metadata.
            /// </summary>
            /// <returns></returns>
            std::string EnumName()
            {
               std::string val = BaseField<U>::ComputedValueString();
               for (size_t i = 0; i < _enums.size(); i++)
               {
                  if (_enums[i] == val)
                  {
                     return _enumNames[i];
                  }
               }
               return "";
            }

            /// <summary>
            /// Provides the string representation of the numeric value for of and enumeration given the string name of the value.
            /// </summary>
            /// <param name="name">String name of enumeration value.</param>
            /// <returns>String representation of enum value, such as "3". If the name cannot be found an empty string is returned.</returns>
            std::string enumValueString(std::string name)
            {
               for (size_t i = 0; i < _enumNames.size(); i++)
               {
                  if (_enumNames[i] == name)
                  {
                     return _enums[i];
                  }
               }
               return "";
            }

         private:

            std::string _enumName;
            std::vector<std::string> _enumNames;
            std::vector<std::string> _enums;
         };
      }
   }
}
