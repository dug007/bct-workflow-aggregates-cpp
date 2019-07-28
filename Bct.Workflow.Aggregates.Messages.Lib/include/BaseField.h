#pragma once

#include <vector>
#include <algorithm>

#include "AbstractAggregate.h"
#include "AbstractField.h"
#include "FieldMeta.h"
#include "AggregateMetaData.h"
#include "Exceptions.h"


namespace Bct
{
   namespace Workflow
   {
      namespace Aggregates
      {
         /// <summary>
         /// Base template class for scalar fields and derives from the AbstractField class. All scalar fields must derive from this class.
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
            /// <param name="aggregate">The associated aggregate this field is a member of.</param>
            BaseField(const std::string &fieldName, const TypeEnum::Type &t,  AbstractAggregate *aggregate)
               : _fieldName(fieldName), _type(t), _aggregate(aggregate), _fieldSetCounter(0)
            {
            }

            virtual ~BaseField() {};

            // Set/Get --------------------->

            /// <summary>
            /// Set the value of this field.
            /// </summary>
            /// <param name="v">Value to give this field.</param>
            void Value(const T &v)
            {
               switch (_state)
               {
               case FieldStateEnum::Constant:
               case FieldStateEnum::Unavailable:
               {
                  std::string aggName = typeid(*_aggregate).name();
                  throw NotAbleToSet(aggName, FieldName(), FieldStateEnum::FieldStateString(State()));
               }
               }
               ValueInternal(v, false);
            }

            /// <summary>
            /// Get the value of this field.
            /// </summary>
            /// <returns>The value of this field.</returns>
            const T &Value() const
            {
               // rules to implement here - User Story 126598
               switch (_state)
               {
               case FieldStateEnum::NotSet:
               {
                  std::string aggName = typeid(*_aggregate).name();
                  throw NotAbleToGet(aggName, FieldName(), FieldStateEnum::FieldStateString(State()));
               }
               case FieldStateEnum::Unavailable:
               {
                  std::string aggName_Unavail = typeid(*_aggregate).name();
                  throw NotAbleToGet(aggName_Unavail, FieldName(), FieldStateEnum::FieldStateString(State()));
               }
               case FieldStateEnum::Default:
                  return _default;
               }
               return _val;
            }

            T operator=(const T &val)
            {
               this->Value(val);
               return *this;
            }


            void Unset()
            {
               switch (_state)
               {
               case FieldStateEnum::Constant:
               case FieldStateEnum::Unavailable:
               {
                  std::string aggName = typeid(*_aggregate).name();
                  throw NotAbleToSet(aggName, FieldName(), FieldStateEnum::FieldStateString(State()));
               }
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
               FieldMeta &fm = findFieldMeta();
               const FieldStateEnum::FieldState &state = fm._fieldState;
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
            const std::string &DefaultStr() const
            {
               return findFieldMeta()._default;
            }

            /// <summary>
            /// Determines if this field has a value.
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
            void SetDefault(const T &def)
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
            int16_t _ver;
            uint32_t _fieldSetCounter;
            AbstractAggregate *_aggregate;

            void ValueInternal(const T &v, bool fromCalculation)
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
            
            FieldMeta &findFieldMeta() const
            {
               // check metadata marked for for all versions in the version 0 vector
               AggregateMetaData & aggMD = _aggregate->MetaData(); // reduce vtable hit and indirection overhead
               std::vector<int16_t> &fmi0 = aggMD.versionMetaData[0].fieldMetaDataI; // indirection vector for version 0 / all versions
               if (fmi0.size() > 0)
               {
                  for (size_t i = 0; i < fmi0.size(); i++)
                  {
                     FieldMeta &fm = aggMD.fieldMetaData[fmi0[i]]; // indirection
                     if (fm.FieldName() == _fieldName)
                     {
                        if (fm._parentVer == BaseAggregate::InAllVersions || (_ver == 0 && fm._parentVer == 0))
                        {
                           return fm;
                        }
                        else
                        {
                           break;
                        }
                     }
                  }
               }

               std::vector<int16_t> &fmi = aggMD.versionMetaData[_ver].fieldMetaDataI; // indirection vector for version
               if (fmi.size() > 0)
               {
                  for (size_t i = 0; i < fmi.size(); i++)
                  {
                     FieldMeta &fm = aggMD.fieldMetaData[fmi[i]]; // indirection
                     if (fm.FieldName() == _fieldName && fm._parentVer <= _ver)
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
