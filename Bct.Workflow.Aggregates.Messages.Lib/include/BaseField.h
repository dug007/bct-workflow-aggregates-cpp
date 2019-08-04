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
            /// <param name="fieldId">Id of this field.</param>
            /// <param name="aggregate">The associated aggregate this field is a member of.</param>
            BaseField(int32_t fieldId, AbstractAggregate *aggregate)
               : _fieldId(fieldId), _aggregate(aggregate), _fieldSetCounter(0)
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

            /// <summary>
            /// Assignment operator
            /// </summary>
            /// <param name="val"></param>
            /// <returns></returns>
            T operator=(const T &val)
            {
               this->Value(val);
               return *this;
            }

            /// <summary>
            /// Sets the state of the field to NotSet.
            /// </summary>
            void unset()
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


            /// <summary>
            /// Conversion operator.
            /// </summary>
            /// <returns>The value of this field.</returns>
            operator T() const
            {
               return this->Value();
            }

            // Set/Get ------------------------------<

            // AbstractField ------------>
            
            /// <summary>
            /// Get the name of this field.
            /// </summary>
            /// <returns>Name of this field.</returns>
            const std::string FieldName() const
            {
               AggregateMetaData &md = _aggregate->MetaData();
               FieldInfo &fi = md.fieldInfo[FieldId()];
               std::string const &fieldName = fi.FieldName();
               return fieldName;
            }

            /// <summary>
            /// Get the type of this field.
            /// </summary>
            /// <returns>Type of this field.</returns>
            virtual const TypeEnum::Type Type() const
            {
               AggregateMetaData &md = _aggregate->MetaData();
               FieldInfo &fi = md.fieldInfo[FieldId()];
               TypeEnum::Type const &fieldType = fi.FieldType();
               return fieldType;
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

            /// <summary>
            /// 
            /// </summary>
            /// <param name="ver"></param>
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
                  setDefault(out);
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
            const bool &hasValue() const
            {
               // TODO handle Computed after field as been computed - User Story 126600
               return (_state == FieldStateEnum::Set || _state == FieldStateEnum::Constant || _state == FieldStateEnum::Default);
            }

            /// <summary>
            /// Pure virtual function that returns the field id for this field.
            /// </summary>
            /// <returns>Field id for this field.</returns>
            virtual int32_t FieldId() const
            {
               return _fieldId;
            }

          protected:

            // AbstractField ----------->

            /// <summary>
            /// Returns a ref to the state to allow changes.
            /// </summary>
            /// <returns>The state reference.</returns>
             virtual FieldStateEnum::FieldState &StateRef()
             {
                return _state;
             }

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
            void setDefault(const T &def)
            {
               _default = def;
               _val = def;
            }

            /// <summary>
            /// Internal value setter. This setter distinguishes between setting the value from a calculation and other cases.
            /// </summary>
            /// <param name="v">The new value to be set.</param>
            /// <param name="fromCalculation">true if the value is being set by a calculation, false otherwase.</param>
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

            /// <summary>
            /// Locates the field metadata from the current version.
            /// </summary>
            /// <returns>The current field metadata item.</returns>
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
                     if (fm.FieldId() == _fieldId)
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
                     if (fm.FieldId() == _fieldId && fm._parentVer <= _ver)
                     {
                        return fm;
                     }
                  }
               }
               throw "error: metadata missing requested version of field";
            }

            /// <summary>
            /// The current version.
            /// </summary>
            int16_t _ver;

         private:

            T _val;
            T _default;
            FieldStateEnum::FieldState _state;
            uint32_t _fieldSetCounter;
            AbstractAggregate *_aggregate;
            int32_t _fieldId;
        };
      }
   }
}
