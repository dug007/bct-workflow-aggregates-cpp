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
         template<class U, class X> class EnumField;

         template <class U, class X>
         std::ostream & operator<< (std::ostream& OutStream, const EnumField<U, X> enumField);

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

         public:
            /// <summary>
            /// Constructor.
            /// </summary>
            /// <param name="fieldId">Field id in aggregate.</param>
            /// <param name="enumName">String name of the wrapped enum.</param>
            /// <param name="enums">String with list of values being wrapped separated by spaces.</param>
            /// <param name="names">String with list of names being wrapped separated by spaces.</param>
            /// <param name="aggregate">The parent aggregate.</param>
            EnumField(int32_t fieldId, const std::string enumName, const std::string enums, const std::string names, AbstractAggregate * const aggregate)
               : BaseField<U>(fieldId, aggregate), _enumName(enumName)
            {
               _enumNames = split(names, ' ');
               _enums = split(enums, ' ');
            }

            /// <summary>
            /// Constructor for copying but not copy constructor.
            /// </summary>
            /// <param name="other">Object being copied.</param>
            /// <param name="aggregate">The parent aggregate.</param>
            EnumField(const EnumField &other, AbstractAggregate * const aggregate) :
               BaseField<U>(other, aggregate)
            {

            }

            virtual ~EnumField()
            {
            };

            /// <summary>
            /// Set the value of this field.
            /// </summary>
            /// <param name="v">Value to give this field.</param>
            void value(const X &v)
            {
               U c = v;
               BaseField<U>::value(c);
            }

            /// <summary>
            /// Get the value of this field.
            /// </summary>
            /// <returns>The value of this field.</returns>
            X value() const
            {
               X r = static_cast<X>(BaseField<U>::value());
               return r;
            }

            /// <summary>
            /// Assignment operator.
            /// </summary>
            /// <param name="val">Value.</param>
            /// <returns>Coerced to integer.</returns>
            U operator=(const X &val)
            {
               this->value(val);
               return *this;
            }

            /// <summary>
            /// Conversion to external.
            /// </summary>
            /// <returns>External representation.</returns>
            operator X() const
            {
               return this->value();
            }

            /// <summary>
            /// Returns the name of the enumeration value as configured by the metadata.
            /// </summary>
            /// <returns></returns>
            std::string EnumName() const
            {
               std::string val = BaseField<U>::computedValueString();
               for (size_t i = 0; i < _enums.size(); i++)
               {
                  if (_enums[i] == val)
                  {
                     return _enumNames[i];
                  }
               }
               return "";
            }

            EnumField & operator=(const EnumField & fld)
            {
               if (&fld != this)
               {
                  BaseField<U>::operator=(fld);
               }
               return *this;
            }

            
            /// /// <summary>
            /// Provides the string representation of the numeric value for of and enumeration given the string name of the value.
            /// </summary>
            /// <param name="name">String name of enumeration value.</param>
            /// <returns>String representation of enum value, such as "3". If the name cannot be found an empty string is returned.</returns>
            std::string s_enumValueString(const std::string name)
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

            /// <summary>
            /// Virtual function to get value of this enum in its string representation. This function is
            /// intended to be used internally for evaluating RPN expressions and not for public set/get operations.
            /// </summary>
            /// <returns>The string representation of the value of this enum.</returns>
            virtual std::string computedValueString()
            {
               return BaseField<U>::computedValueString();
            };

            /// <summary>
            /// Virtual function to set the value of this field using its string representation. This function is
            /// intended to be used internally for evaluating RPN expressions and not for public set/get operations.
            /// </summary>
            /// <param name="val">The string representation of the value of this field.</param>
            virtual void computedValueString(const std::string &val)
            {
               BaseField<U>::computedValueString(val);
            };

            friend std::ostream & operator<< <U, X>(std::ostream& OutStream, const EnumField enumField);

         private:

            std::string _enumName;
            std::vector<std::string> _enumNames;
            std::vector<std::string> _enums;
         };

         template <class U, class X>
         std::ostream & operator<< (std::ostream& OutStream, const EnumField<U, X> enumField )
         {
            OutStream << enumField.value();
            return OutStream;
         }
      }
   }
}
