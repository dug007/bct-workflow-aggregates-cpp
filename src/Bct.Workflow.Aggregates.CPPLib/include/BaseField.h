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
#include "rapidjson/document.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/writer.h"
#include "type_name.h"

using namespace rapidjson;

namespace Bct
{
   namespace Workflow
   {
      namespace Aggregates
      {
         class StringField;

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
            /// <param name="fieldId">Id of this field. The id begins with 0 for the first field in the aggregate and proceeds by one for every field in the aggregate, including nested aggregates. This field will be uses as an index into the FieldInfo vector of the AggregateMetaData object.</param>
            /// <param name="aggregate">The associated aggregate this field is a member of.</param>
            BaseField(int32_t fieldId, AbstractAggregate* const aggregate)
               : _fieldId(fieldId), _aggregate(aggregate), _fieldSetCounter(0)
            {
            }

            /// <summary>
            /// Constructor used for copying but not a copy constructor.
            /// </summary>
            /// <param name="other">Other field being copied.</param>
            /// <param name="aggregate">The associated aggregate this field is a member of.</param>
            BaseField(const BaseField& other, AbstractAggregate* const aggregate)
               : _ver(other._ver), _val(other._val), _default(other._default), _state(other._state),
               _fieldSetCounter(other._fieldSetCounter), _aggregate(aggregate), _fieldId(other._fieldId)
            {
            }

            virtual ~BaseField() {};

            // Set/Get --------------------->

            /// <summary>
            /// Set the value of this field.
            /// </summary>
            /// <param name="v">Value to give this field.</param>
            void value(const T& v)
            {
               valueInternal(v, false);
            }

            /// <summary>
            /// Get the value of this field.
            /// </summary>
            /// <returns>The value of this field.</returns>
            const T& value() const
            {
               // rules to implement here - User Story 126598
               switch (_state)
               {
               case FieldStateEnum::NotSet:
               {
                  int status = 0;
                  std::string aggName = type_name(*_aggregate, status);
                  NotAbleToGet obj = NotAbleToGet(aggName, fieldName(), FieldStateEnum::FieldStateString(state()));
                  BaseAggregate::getLogger()->logError(obj.what(), __FILE__, __LINE__);
                  throw obj;
               }
               case FieldStateEnum::Unavailable:
               {
                  int status = 0;
                  std::string aggName_Unavail = type_name(*_aggregate, status);
                  NotAbleToGet obj = NotAbleToGet(aggName_Unavail, fieldName(), FieldStateEnum::FieldStateString(state()));
                  BaseAggregate::getLogger()->logError(obj.what(), __FILE__, __LINE__);
                  throw obj;
               }
               case FieldStateEnum::Default:
                  return _default;

               default: break;
               }
               return _val;
            }

            /// <summary>
            /// Get the value of this field.
            /// </summary>
            /// <returns>The value of this field.</returns>
            const T& valueForSerialize(bool& isNull) const
            {
               // rules to implement here - User Story 126598
               switch (_state)
               {
               case FieldStateEnum::NotSet:
               case FieldStateEnum::Unavailable:
               {
                  isNull = true;
                  return _val;
               }
               case FieldStateEnum::Default:
                  return _default;

               default: break;
               }
               isNull = false;
               return _val;
            }


            /// <summary>
            /// Assignment operator from wrapped type.
            /// </summary>
            /// <param name="val">Value of wrapped type.</param>
            /// <returns>Value of field being assigned from.</returns>
            T& operator=(const T& val)
            {
               this->value(val);
               return this->_val;
            }

            /// <summary>
            /// Assignment operator for whole object
            /// </summary>
            /// <param name="fld">Other from object.</param>
            /// <returns>Reference to assigned object.</returns>
            BaseField<T>& operator=(const BaseField<T>& fld)
            {
               if (&fld != this)
               {
                  this->_val = fld._val;
                  this->_ver = fld._ver;
                  this->_default = fld._default;
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
            bool operator==(const BaseField<T>& fld) const
            {
               return (fld._val == _val);
            }

            /// <summary>
            /// Not equal operator.
            /// </summary>
            /// <param name="fld">Other field to compare to.</param>
            /// <returns>True if the two field's values are not equal.</returns>
            bool operator!=(const BaseField<T>& fld) const
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
                  int status = 0;
                  std::string aggName = type_name(*_aggregate, status);
                  NotAbleToSet obj = NotAbleToSet(aggName, fieldName(), FieldStateEnum::FieldStateString(state()));
                  BaseAggregate::getLogger()->logError(obj.what(), __FILE__, __LINE__);
                  throw obj;
               }

               default: break;
               }
               _state = FieldStateEnum::NotSet;
            }


            /// <summary>
            /// Conversion operator.
            /// </summary>
            /// <returns>The value of this field.</returns>
            operator T() const
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
               AggregateMetaData& md = _aggregate->MetaData();
               FieldInfo& fi = md.fieldInfo[fieldId()];
               std::string const& fieldName = fi.fieldName();
               return fieldName;
            }

            /// <summary>
            /// Get the type of this field.
            /// </summary>
            /// <returns>Type of this field.</returns>
            virtual const TypeEnum::Type type() const
            {
               AggregateMetaData& md = _aggregate->MetaData();
               FieldInfo& fi = md.fieldInfo[fieldId()];
               TypeEnum::Type const& fieldType = fi.FieldType();
               return fieldType;
            }

            /// <summary>
            /// Get the subtype of this field.
            /// </summary>
            /// <returns>Subtype of this field.</returns>
            virtual const TypeEnum::Type subtype() const
            {
               return TypeEnum::EmptyType;
            }

            /// <summary>
            /// Get the state of this field.
            /// </summary>
            /// <returns>State of this field.</returns>
            virtual const FieldStateEnum::FieldState& state() const
            {
               return _state;
            }

            /// <summary>
            /// Get the field set counter for this field. This provides the relative order of when fields were last set.
            /// </summary>
            /// <returns>Field set counter.</returns>
            virtual const uint32_t& fieldSetCounter() const
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
               FieldMeta& fm = findFieldMeta();
               const FieldStateEnum::FieldState& state = fm._fieldState;
               _state = state;

               if (state == FieldStateEnum::Constant || state == FieldStateEnum::Default)
               {
                  Document d;
                  d.Parse(defaultStr().c_str());
                  const Value& v = d;
                  setDefault(v, _default);
               }
               // If metatdata state is computed, initial value is not set
               else if (state == FieldStateEnum::Computed)
               {
                  _state = FieldStateEnum::NotSet;
               }
            }

            // AbstractField -------------------<

            /// <summary>
            /// Get the default value of this field as a string.
            /// </summary>
            /// <returns>Default value of field as a string.</returns>
            const std::string& defaultStr() const
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

            virtual void serialize(PrettyWriter<StringBuffer>* writer) const
            { //[PL] TODO
               if (NULL == writer)
               {
                  return;
               }

               const AbstractField* absField = dynamic_cast<const AbstractField*>(this);
               cout << "BaseField::serialize() type(): " << type() << endl;
               switch (type())
               {
               case TypeEnum::BoolType:
               {
                  const BaseField<bool>* pField = dynamic_cast<const BaseField<bool>*>(this);
                  if (pField)
                  {
                     writer->Bool(pField->value());
                  }
                  else
                  {
                     writer->Null();
                  }
               }
               break;
               case TypeEnum::Int32Type:
               {
                  const BaseField<int32_t>* pField = dynamic_cast<const BaseField<int32_t>*>(this);
                  if (pField)
                  {
                     writer->Int(pField->value());
                  }
                  else
                  {
                     writer->Null();
                  }
               }
               break;
               case TypeEnum::UInt32Type:
               {
                  const BaseField<uint32_t>* pField = dynamic_cast<const BaseField<uint32_t>*>(this);
                  if (pField)
                  {
                     writer->Uint(pField->value());
                  }
                  else
                  {
                     writer->Null();
                  }
               }
               break;
               case TypeEnum::Int64Type:
               {
                  const BaseField<int64_t>* pField = dynamic_cast<const BaseField<int64_t>*>(this);
                  if (pField)
                  {
                     writer->Int64(pField->value());
                  }
                  else
                  {
                     writer->Null();
                  }
               }
               break;
               case TypeEnum::UInt64Type:
               {
                  const BaseField<uint64_t>* pField = dynamic_cast<const BaseField<uint64_t>*>(this);
                  if (pField)
                  {
                     writer->Uint64(pField->value());
                  }
                  else
                  {
                     writer->Null();
                  }
               }
               break;
               case TypeEnum::DoubleType:
               {
                  const BaseField<double>* pField = dynamic_cast<const BaseField<double>*>(this);
                  if (pField)
                  {
                     writer->Double(pField->value());
                  }
                  else
                  {
                     writer->Null();
                  }
               }
               break;
               case TypeEnum::StringType:
               {
                  const BaseField<std::string>* pField = dynamic_cast<const BaseField<std::string>*>(this);
                  if (pField)
                  {
                     writer->String(pField->value().c_str(), pField->value().length(), false);
                  }
                  else
                  {
                     writer->Null();
                  }
               }
               break;
               default:
                  writer->String("ERROR: unexpected type");
                  break;
               }// switch(type)
            }

         private:

            // helper functions
            std::string& ltrim(std::string& str, const std::string& chars = "\"\t\n\v\f\r ") const
            {
               str.erase(0, str.find_first_not_of(chars));
               return str;
            }

            std::string& rtrim(std::string& str, const std::string& chars = "\"\t\n\v\f\r ") const
            {
               str.erase(str.find_last_not_of(chars) + 1);
               return str;
            }

            std::string& trim(std::string& str, const std::string& chars = "\"\t\n\v\f\r ") const
            {
               return ltrim(rtrim(str, chars), chars);
            }

            // Helpers to match string representation to generic T
            // The vv arguments are NOT USED for setting, only
            // to match type for templates. This is necessary
            // because C++ function templates do not have constraint
            // capability.
            void setValue(const Value& v, int32_t& vv, bool fromCalc)
            {
               // vv USED ONLY FOR TEMPLATE MATCHING
               T nval = v.GetInt();
               valueInternal(nval, fromCalc);
            }
            void setValue(const Value& v, int64_t& vv, bool fromCalc)
            {
               T nval = v.GetInt64();
               valueInternal(nval, true);
            }
            void setValue(const Value& v, uint32_t& vv, bool fromCalc)
            {
               T nval = v.GetUint();
               valueInternal(nval, true);
            }
            void setValue(const Value& v, uint64_t& vv, bool fromCalc)
            {
               T nval = v.GetUint64();
               valueInternal(nval, true);
            }
            void setValue(const Value& v, bool& vv, bool fromCalc)
            {
               T nval = v.GetBool();
               valueInternal(nval, true);
            }
            void setValue(const Value& v, double& vv, bool fromCalc)
            {
               T nval = v.GetDouble();
               valueInternal(nval, true);
            }
            void setValue(const Value& v, std::string& vv, bool fromCalc)
            {
               T nval = v.GetString();
               valueInternal(nval, true);
            }

            void setDefault(const Value& v, int32_t& vv)
            {
               T nval = v.GetInt();
               setDefault(nval);
            }
            void setDefault(const Value& v, int64_t& vv)
            {
               T nval = v.GetInt64();
               setDefault(nval);
            }
            void setDefault(const Value& v, uint32_t& vv)
            {
               T nval = v.GetUint();
               setDefault(nval);
            }
            void setDefault(const Value& v, uint64_t& vv)
            {
               T nval = v.GetUint64();
               setDefault(nval);
            }
            void setDefault(const Value& v, bool& vv)
            {
               T nval = v.GetBool();
               setDefault(nval);
            }
            void setDefault(const Value& v, double& vv)
            {
               T nval = v.GetDouble();
               setDefault(nval);
            }
            void setDefault(const Value& v, std::string& vv)
            {
               T nval = v.GetString();
               setDefault(nval);
            }

            Value getValue(const int32_t vv) const
            {
               Value v(vv);
               return v;
            }
            Value getValue(const int64_t vv) const
            {
               Value v(vv);
               return v;
            }
            Value getValue(const uint32_t vv) const
            {
               Value v(vv);
               return v;
            }
            Value getValue(const uint64_t vv) const
            {
               Value v(vv);
               return v;
            }
            Value getValue(const bool vv) const
            {
               Value v(vv);
               return v;
            }
            Value getValue(const double vv) const
            {
               Value v(vv);
               return v;
            }
            Value getValue(const std::string& vv) const
            {
               const char* cs = vv.c_str();
               rapidjson::SizeType size = (rapidjson::SizeType)vv.length();
               Value v(cs, size);
               return v;
            }

         protected:

            // AbstractField ----------->

            /// <summary>
            /// Gets the string representation value of this field. This function is only needed for RPN computations.
            /// </summary>
            /// <returns>String representation of this field.</returns>
            virtual std::string computedValueString() const
            {
               const Value v = getValue(_val);
               StringBuffer buffer;
               Writer<StringBuffer> writer(buffer);
               v.Accept(writer);
               std::string out(buffer.GetString());
               return trim(out);
            }

            /// <summary>
            /// Sets the value of this field using its string representation. This function is only needed for RPN computations.
            /// </summary>
            /// <param name="val">String representation of this field.</param>
            virtual void computedValueString(const std::string& val)
            {
               Document d;
               d.Parse(val.c_str());
               const Value& v = d;
               setValue(v, _val, true);
            }

            /// <summary>
            /// Returns a ref to the state to allow changes.
            /// </summary>
            /// <returns>The state reference.</returns>
            virtual FieldStateEnum::FieldState& stateRef()
            {
               return _state;
            }


            // AbstractField ---------<

            /// <summary>
            /// Sets default value.
            /// </summary>
            /// <param name="def">Default value.</param>
            void setDefault(const T& def)
            {
               _default = def;
               _val = def;
            }

            /// <summary>
            /// Internal value setter. This setter distinguishes between setting the value from a calculation and other cases.
            /// </summary>
            /// <param name="v">The new value to be set.</param>
            /// <param name="fromCalculation">true if the value is being set by a calculation, false otherwase.</param>
            void valueInternal(const T& v, bool fromCalculation)
            {
               switch (_state)
               {
               case FieldStateEnum::Constant:
               case FieldStateEnum::Unavailable:
               {
                  int status = 0;
                  std::string aggName = type_name(*_aggregate, status);
                  NotAbleToSet obj = NotAbleToSet(aggName, fieldName(), FieldStateEnum::FieldStateString(state()));
                  BaseAggregate::getLogger()->logError(obj.what(), __FILE__, __LINE__);
                  throw obj;
               }
               break;

               default: break;
               }

               FieldStateEnum::FieldState  metaState = findFieldMeta()._fieldState;
               switch (metaState)
               {
               case FieldStateEnum::Computed:
               {
                  if (!fromCalculation)
                  {
                     int status = 0;
                     std::string aggName = type_name(*_aggregate, status);
                     NotAbleToSet obj = NotAbleToSet(aggName, fieldName(), FieldStateEnum::FieldStateString(FieldStateEnum::Computed));
                     BaseAggregate::getLogger()->logError(obj.what(), __FILE__, __LINE__);
                     throw obj;
                  }
               }
               break;

               default: break;
               }

               _val = v;
               _fieldSetCounter = _aggregate->fieldSetCounter();
               if (fromCalculation)
               {
                  _state = FieldStateEnum::Computed;
               }
               else
               {
                  _state = FieldStateEnum::Set;
               }
            }

            /// <summary>
            /// Locates the field metadata from the current version.
            /// </summary>
            /// <returns>The current field metadata item.</returns>
            FieldMeta& findFieldMeta() const
            {
               // check metadata marked for for all versions in the version 0 vector
               AggregateMetaData& aggMD = _aggregate->MetaData(); // reduce vtable hit and indirection overhead
               std::vector<int16_t>& fmi0 = aggMD.versionMetaData[0].fieldMetaDataI; // indirection vector for version 0 / all versions
               if (fmi0.size() > 0)
               {
                  for (size_t i = 0; i < fmi0.size(); i++)
                  {
                     FieldMeta& fm = aggMD.fieldMetaData[fmi0[i]]; // indirection
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

               std::vector<int16_t>& fmi = aggMD.versionMetaData[_ver].fieldMetaDataI; // indirection vector for version
               if (fmi.size() > 0)
               {
                  for (size_t i = 0; i < fmi.size(); i++)
                  {
                     FieldMeta& fm = aggMD.fieldMetaData[fmi[i]]; // indirection
                     if (fm.fieldId() == _fieldId && fm._parentVer <= _ver)
                     {
                        return fm;
                     }
                  }
               }
               int status = 0;
               std::string aggName = type_name(*_aggregate, status);
               int32_t size = (int32_t)_aggregate->MetaData().fieldInfo.size();
               std::string fieldName = "unknown";
               std::string reqVersion = _aggregate->MetaData().versionInfo[_ver].Version();
               if (size > _fieldId)
               {
                  fieldName = _aggregate->MetaData().fieldInfo[_fieldId].fieldName();
                  NoSuchVersion obj = NoSuchVersion(aggName, fieldName, reqVersion);
                  BaseAggregate::getLogger()->logError(obj.what(), __FILE__, __LINE__);
                  throw obj;
               }
               NoSuchVersion obj = NoSuchVersion(aggName, reqVersion);
               BaseAggregate::getLogger()->logError(obj.what(), __FILE__, __LINE__);
               throw obj;
            }

            /// <summary>
            /// The current version.
            /// </summary>
            int16_t _ver;
            T _val;

         private:
            T _default;
            FieldStateEnum::FieldState _state;
            uint32_t _fieldSetCounter;
            AbstractAggregate* const _aggregate;
            int32_t _fieldId;
         };
      }
   }
}
