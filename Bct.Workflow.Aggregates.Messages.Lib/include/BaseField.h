#pragma once

#include <vector>
#include <algorithm>

#include "AbstractAggregate.h"
#include "AbstractField.h"
#include "FieldMeta.h"
#include "AggregateMetaData.h"


namespace Bct
{
   namespace Workflow
   {
      namespace Aggregates
      {
         /// <summary>
         /// Base template class for scalar fields. All scalar fields must derive from this class.
         /// </summary>
         template<class T>
         class BaseField : public AbstractField
         {
         public:

            /// <summary>
            /// Constructor.
            /// </summary>
            /// <param name="fieldName">Name of this field.</param>
            /// <param name="t">Type of this field. The given type should be consistent with the template class.</param>
            /// <param name="metaData">Metadata vector.</param>
            /// <param name="aggregate">The associated aggregate this field is a member of.</param>
            BaseField(const std::string fieldName, const TypeEnum::Type t, AggregateMetaData & metaData,  AbstractAggregate *aggregate)
               : _fieldName(fieldName), _type(t), _metaData(metaData), _aggregate(aggregate), _fieldSetCounter(0)
            {
            }

            virtual ~BaseField() {};

            // Set/Get --------------------->

            /// <summary>
            /// Set the value of this field.
            /// </summary>
            /// <param name="v">Value to give this field.</param>
            void Value(const T v)
            {
               if (_state == FieldStateEnum::Constant)
               {
                  throw "error: attempting to set constant field"; // TODO internalize - User Story 126598
               }
               ValueInternal(v, false);
            }

            /// <summary>
            /// Get the value of this field.
            /// </summary>
            /// <returns>The value of this field.</returns>
            const T &Value() const
            {
               // rules to implement here - User Story 12698
               switch (_state)
               {
               case FieldStateEnum::NotSet: // TODO: internationalize - User Story 126598
                  throw "error: value has not been set";
               case FieldStateEnum::Unavailable: // TODO: internationalize - User Story 126598
                  throw "error: not available in this version";

               case FieldStateEnum::Computed:
                  // fall through for now - User Story 126598
                  break;
               case FieldStateEnum::Default:
                  return _default;
               }
               return _val;
            }

            T operator=(const T val)
            {
               this->Value(val);
               return *this;
            }


            void Unset()
            {
               if (_state == FieldStateEnum::Constant)
               {
                  throw "error: attempting to set constant field"; // TODO internalize - User Story 126598
               }
               _state = FieldStateEnum::NotSet;
            }

            // Set/Get ------------------------------<

            /// <summary>
            /// Conversion operator.
            /// </summary>
            /// <returns>The value of this field.</returns>
            operator T() const
            {
               return this->Value();
            }

            // AbstractField ------------>
            
            /// <summary>
            /// Get the name of this field.
            /// </summary>
            /// <returns>Name of this field.</returns>
            virtual const std::string &FieldName() const
            {
               return _fieldName;
            }

            /// <summary>
            /// Get the type of this field.
            /// </summary>
            /// <returns>Type of this field.</returns>
            virtual const TypeEnum::Type &Type() const
            {
               return _type;
            }

            /// <summary>
            /// Get the state of this field.
            /// </summary>
            /// <returns>State of this field.</returns>
            virtual const FieldStateEnum::FieldState &State() const
            {
               return _state;
            }

            /// <summary>
            /// Get the field set counter for this field. This provides the relative order of when fields were last set.
            /// </summary>
            /// <returns>Field set counter.</returns>
            virtual const uint32_t &FieldSetCounter() const
            {
               return _fieldSetCounter;
            }

            virtual void initMetaData(int16_t ver)
            {
               _ver = ver;

               // search for the metadata for corresponding version and field name, then initialize this field
               // with that located metadata instance
               FieldMeta fm = findFieldMeta();
               FieldStateEnum::FieldState state = fm._fieldState;
               _state = state;

               if (state == FieldStateEnum::Constant || state == FieldStateEnum::Default)
               {
                  // TODO Use serialization library for string<->type conversion - User Story 126886
                  T out;
                  std::stringstream ss;
                  ss << DefaultStr();
                  ss >> out;
                  SetDefault(out);
               }
            }

            // AbstractField -------------------<

            /// <summary>
            /// Get the default value of this field as a string.
            /// </summary>
            /// <returns>Default value of field as a string.</returns>
            std::string DefaultStr()
            {
               return findFieldMeta()._default;
            }

            /// <summary>
            /// Determins if this field has a value.
            /// </summary>
            /// <returns>true if the field has a  value, false if the field does not hava a value.</returns>
            const bool &HasValue() const
            {
               // TODO handle Computed after field as been computed - User Story 126600
               return (_state == FieldStateEnum::Set || _state == FieldStateEnum::Constant || _state == FieldStateEnum::Default);
            }

         protected:

            // AbstractField ----------->

            /// <summary>
            /// Gets the string representation value of this field. This function is not public and is only needed for RPN computations.
            /// </summary>
            /// <returns>String representation of this field.</returns>
            virtual std::string ComputedValueString() const
            {
               // TODO Use serialization library for string<->type conversion - User Story 126886
               std::stringstream ss;
               ss << Value();
               return ss.str();
            }

            /// <summary>
            /// Sets the value of this field using its string representation. This function is not public and is only needed for RPN computations.
            /// </summary>
            /// <param name="val">String representation of this field.</param>
            virtual void ComputedValueString(const std::string & val)
            {
               // TODO Use serialization library for string<->type conversion - User Story 126886
               T out;
               std::stringstream ss;
               ss << val;
               ss >> out;
               ValueInternal(out, true);
            }

            // AbstractField ---------<

            /// <summary>
            /// Sets default value.
            /// </summary>
            /// <param name="def">Default value.</param>
            void SetDefault(const T def)
            {
               _default = def;
               _val = def;
            }

         private:

            T _val;
            T _default;
            FieldStateEnum::FieldState _state;
            TypeEnum::Type _type;
            std::string _fieldName;
            AggregateMetaData & _metaData;
            int16_t _ver;
            uint32_t _fieldSetCounter;
            AbstractAggregate *_aggregate;

            void ValueInternal(const T v, bool fromCalculation)
            {
               _val = v;
               FieldStateEnum::FieldState  metaState = findFieldMeta()._fieldState;
               _fieldSetCounter = _aggregate->FieldSetCounter();
               if (metaState == FieldStateEnum::Default)
               {
                  if (_val == _default)
                  {
                     _state = FieldStateEnum::Default;
                  }
                  else
                  {
                     _state = FieldStateEnum::Set;
                  }
               }
               else
               {
                  if (fromCalculation)
                  {
                     _state = FieldStateEnum::Computed;
                  }
                  else
                  {
                     _state = FieldStateEnum::Set;
                  }
               }

            }
            
            FieldMeta findFieldMeta()
            {
               std::vector<int16_t> fmi = _metaData.versionMetaData[_ver].fieldMetaDataI; // indirection vector for version
               if (fmi.size() > 0)
               {
                  for (size_t i = 0; i < fmi.size(); i++)
                  {
                     FieldMeta fm = _metaData.fieldMetaData[fmi[i]]; // indirection
                     if (fm.FieldName() == _fieldName && fm._ver <= _ver)
                     {
                        return fm;
                     }
                  }
               }
               throw "error: metadata missing requested version of field";
            }

            virtual FieldStateEnum::FieldState &StateRef()
            {
               return _state;
            }
         };
      }
   }
}
