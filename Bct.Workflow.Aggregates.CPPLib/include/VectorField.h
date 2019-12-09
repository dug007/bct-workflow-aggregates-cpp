#pragma once

#include <vector>
#include <algorithm>

#include "AbstractAggregate.h"
#include "AbstractField.h"
#include "FieldMeta.h"
#include "AggregateMetaData.h"
#include "NotAbleToGet.h"
#include "NoSuchVersion.h"
#include "NotAbleToSet.h"


namespace Bct
{
   namespace Workflow
   {
      namespace Aggregates
      {
         /// <summary>
         ///  Template class for vector fields, which derives from the AbstractField class. 
         /// 
         ///  Note: there is no Constant, Default, or Computed states for VectorField.
         /// </summary>
         template<class T>
         class VectorField: public AbstractField
         {
            
         public:
            /// <summary>
            /// Constructor.
            /// </summary>
            /// <param name="fieldId">Id of this field. The id begins with 0 for the first field in the aggregate and proceeds by one for every field in the aggregate, including nested aggregates. This field will be uses as an index into the FieldInfo vector of the AggregateMetaData object.</param>
            /// <param name="aggregate">The associated aggregate this field is a member of.</param>
            VectorField(int32_t fieldId, AbstractAggregate * const aggregate)
               : _fieldId(fieldId), _aggregate(aggregate), _fieldSetCounter(0)
            {
            }

            /// <summary>
            /// Constructor used for copying but not a copy constructor.
            /// </summary>
            /// <param name="other">Other field being copied.</param>
            /// <param name="aggregate">The associated aggregate this field is a member of.</param>
            VectorField(const VectorField & other, AbstractAggregate * const aggregate)
               : _ver(other._ver), _val(other._val), _state(other._state),
               _fieldSetCounter(other._fieldSetCounter), _aggregate(aggregate), _fieldId(other._fieldId)
            {
            }

            virtual ~VectorField() {};

            // Set/Get --------------------->

            /// <summary>
            /// Set the value of this field.
            /// </summary>
            /// <param name="v">Value to give this field.</param>
            void value(const std::vector<T> &v)
            {
               valueInternal(v, false);
            }

            /// <summary>
            /// Get the value of this field.
            /// </summary>
            /// <returns>The value of this field.</returns>
            const std::vector<T> &value() const
            {
               // rules to implement here - User Story 126598
               switch (_state)
               {
               case FieldStateEnum::NotSet:
               {
                  std::string aggName = typeid(*_aggregate).name();
                  throw NotAbleToGet(aggName, fieldName(), FieldStateEnum::FieldStateString(state()));
               }
               case FieldStateEnum::Unavailable:
               {
                  std::string aggName_Unavail = typeid(*_aggregate).name();
                  throw NotAbleToGet(aggName_Unavail, fieldName(), FieldStateEnum::FieldStateString(state()));
               }
               default:
               {

               }
               }
               return _val;
            }

            /// <summary>
            /// Swaps vector field value with other vector.
            /// </summary>
            /// <param name="other">Other vector to swap with.</param>
            void swap(std::vector<T> &other)
            {
               switch (_state)
               {
               case FieldStateEnum::Unavailable:
               {
                  std::string aggName = typeid(*_aggregate).name();
                  throw NotAbleToSet(aggName, fieldName(), FieldStateEnum::FieldStateString(state()));
               }
               }
               _val.swap(other);
               _fieldSetCounter = _aggregate->fieldSetCounter();
               _state = FieldStateEnum::Set;
            }

            /// <summary>
            /// Assignment operator from wrapped type.
            /// </summary>
            /// <param name="val">Value of wrapped type.</param>
            /// <returns>Value of field being assigned from.</returns>
            std::vector<T> &operator=(const std::vector<T> &val)
            {
               this->value(val);
               return this->_val;
            }

            /// <summary>
            /// Assignment operator for whole object
            /// </summary>
            /// <param name="fld">Other from object.</param>
            /// <returns>Reference to assigned object.</returns>
            VectorField<T> & operator=(const VectorField<T> & fld)
            {
               if (&fld != this)
               {
                  this->_val = fld._val;
                  this->_ver = fld._ver;
                  this->_state = fld._state;
                  this->_fieldSetCounter = fld._fieldSetCounter;
                  this->_fieldId = fld._fieldId;
               }
               return *this;
            }

            /// <summary>
            /// Equal operator.
            /// </summary>
            /// <param name="fld">Other field to compare to</param>
            /// <returns>True if the two field's values are equal.</returns>
            bool operator==(const VectorField<T> & fld) const
            {
               return (fld._val == _val);
            }

            /// <summary>
            /// Not equal operator.
            /// </summary>
            /// <param name="fld">Other field to compare to.</param>
            /// <returns>True if the two field's values are not equal.</returns>
            bool operator!=(const VectorField<T> & fld) const
            {
               return (fld._val != _val);
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
                  throw NotAbleToSet(aggName, fieldName(), FieldStateEnum::FieldStateString(state()));
               }
               default:
               {

               }
               }
               _state = FieldStateEnum::NotSet;
            }

            /// <summary>
            /// Conversion operator.
            /// </summary>
            /// <returns>The value of this field.</returns>
            operator std::vector<T>() const
            {
               return this->value();
            }

            // Set/Get ------------------------------<

            // AbstractField ------------>

            /// <summary>
            /// Get the name of this field.
            /// </summary>
            /// <returns>Name of this field.</returns>
            const std::string fieldName() const
            {
               AggregateMetaData &md = _aggregate->MetaData();
               FieldInfo &fi = md.fieldInfo[fieldId()];
               std::string const &fieldName = fi.fieldName();
               return fieldName;
            }

            /// <summary>
            /// Get the type of this field.
            /// </summary>
            /// <returns>Type of this field.</returns>
            virtual const TypeEnum::Type type() const
            {
               AggregateMetaData &md = _aggregate->MetaData();
               FieldInfo &fi = md.fieldInfo[fieldId()];
               TypeEnum::Type const &fieldType = fi.FieldType();
               return fieldType;
            }

            /// <summary>
            /// Get the state of this field.
            /// </summary>
            /// <returns>State of this field.</returns>
            virtual const FieldStateEnum::FieldState &state() const
            {
               return _state;
            }

            /// <summary>
            /// Get the field set counter for this field. This provides the relative order of when fields were last set.
            /// </summary>
            /// <returns>Field set counter.</returns>
            virtual const uint32_t &fieldSetCounter() const
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
            }

            // AbstractField -------------------<

            /// <summary>
            /// Get the default value of this field as a string. Question: need this?
            /// </summary>
            /// <returns>Default value of field as a string.</returns>
            const std::string &defaultStr() const
            {
               return findFieldMeta()._default;
            }

            /// <summary>
            /// Determines if this field has a value.
            /// </summary>
            /// <returns>true if the field has a  value, false if the field does not hava a value.</returns>
            const bool hasValue() const
            {
               return (_state == FieldStateEnum::Set || _state == FieldStateEnum::Constant || _state == FieldStateEnum::Default || _state == FieldStateEnum::Computed);
            }

            /// <summary>
            /// Pure virtual function that returns the field id for this field.
            /// </summary>
            /// <returns>Field id for this field.</returns>
            virtual int32_t fieldId() const
            {
               return _fieldId;
            }

         protected:

            // AbstractField ----------->

            /// <summary>
            /// Gets the string representation value of this field. 
            /// This function is only needed for RPN computations, which does not support vector.
            /// </summary>
            /// <returns>String representation of this field.</returns>
            virtual std::string computedValueString() const
            {              
               return "";
            }

            /// <summary>
            /// Sets the value of this field using its string representation. 
            /// This function is only needed for RPN computations, which does not support vector.
            /// </summary>
            /// <param name="val">String representation of this field.</param>
            virtual void computedValueString(const std::string & val)
            {
               
            }

            /// <summary>
            /// Returns a ref to the state to allow changes.
            /// </summary>
            /// <returns>The state reference.</returns>
            virtual FieldStateEnum::FieldState &stateRef()
            {
               return _state;
            }


            // AbstractField ---------<        

            /// <summary>
            /// Internal value setter. This setter distinguishes between setting the value from a calculation and other cases.
            /// </summary>
            /// <param name="v">The new value to be set.</param>
            /// <param name="fromCalculation">true if the value is being set by a calculation, false otherwase.</param>
            void valueInternal(const std::vector<T> &v, bool fromCalculation)
            {
               
               if (_state == FieldStateEnum::Unavailable)
               {
                  std::string aggName = typeid(*_aggregate).name();
                  throw NotAbleToSet(aggName, fieldName(), FieldStateEnum::FieldStateString(state()));
               }

               FieldStateEnum::FieldState  metaState = findFieldMeta()._fieldState;              

               _val = v;
               _fieldSetCounter = _aggregate->fieldSetCounter();
               if (metaState == FieldStateEnum::Default)
               {                
                  _state = FieldStateEnum::Set;                
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
                     if (fm.fieldId() == _fieldId)
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
                     if (fm.fieldId() == _fieldId && fm._parentVer <= _ver)
                     {
                        return fm;
                     }
                  }
               }
               std::string aggName = typeid(*_aggregate).name();
               int32_t size = (int32_t)_aggregate->MetaData().fieldInfo.size();
               std::string fieldName = "unknown";
               std::string reqVersion = _aggregate->MetaData().versionInfo[_ver].Version();
               if (size > _fieldId)
               {
                  fieldName = _aggregate->MetaData().fieldInfo[_fieldId].fieldName();
                  throw NoSuchVersion(aggName, fieldName, reqVersion);
               }
               throw NoSuchVersion(aggName, reqVersion);
            }
          

            /// <summary>
            /// The current version.
            /// </summary>
            int16_t _ver;

            /// <summary>
            /// The vector field of template <T>
            /// </summary>
            std::vector<T> _val;

         private:
            FieldStateEnum::FieldState _state;
            uint32_t _fieldSetCounter;
            AbstractAggregate * const _aggregate;
            int32_t _fieldId;
         };
      }
   }
}
