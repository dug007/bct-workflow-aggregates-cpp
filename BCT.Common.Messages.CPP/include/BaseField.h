#pragma once

#include <vector>
#include <algorithm>
#include "VersionMetaData.h"
#include "FieldMeta.h"
#include "AbstractField.h"
#include "TypeCode.h"
#include "AbstractAggregate.h"


namespace Bct
{
   namespace Workflow
   {
      namespace Aggregates
      {
         template<class T>
         class BaseField : public AbstractField
         {
         private:
            T _val;
            T _default;
            FieldStateEnum::FieldState _state;
            FieldTypeEnum::FieldType _type;
            BCTCommonUtilitiesRPNEvaluatorCPPWin::TypeCode _typeCode;
            std::string _fieldName;
            std::vector<VersionMetaData> _metaData;
            int16_t _ver;
            int16_t _fieldSetCounter;
            AbstractAggregate *_aggregate;

         public:
            BaseField()
            {
            }
            BaseField(const std::string fieldName, const FieldTypeEnum::FieldType t, const int16_t ver, const std::vector<VersionMetaData> &metaData,  AbstractAggregate *aggregate)
               : _fieldName(fieldName), _type(t),  _ver(ver), _metaData(metaData), _aggregate(aggregate), _fieldSetCounter(0)
            {
               FieldMeta fm = findFieldMeta();
               FieldStateEnum::FieldState state = fm._fieldState;
               _state = state;
               _typeCode = mapTypeToCode(t);
            }
         private:
            const FieldMeta findFieldMeta()
            {
               std::vector<FieldMeta> fm = _metaData[_ver].fieldMetaData;
               for (size_t i = 0; i < fm.size(); i++)
               {
                  if (fm[i]._fieldName == _fieldName)
                  {
                     return fm[i];
                  }
               }
               throw "error: metadata missing requested version of field";
            }
            // TODO we need to decide what to do about type system - map it for now
            const BCTCommonUtilitiesRPNEvaluatorCPPWin::TypeCode mapTypeToCode(const FieldTypeEnum::FieldType t)
            {
                  if (t == FieldTypeEnum::UInt32Field)    return BCTCommonUtilitiesRPNEvaluatorCPPWin::TypeCode::UInt32;
                  if (t == FieldTypeEnum::Int32Field)     return BCTCommonUtilitiesRPNEvaluatorCPPWin::TypeCode::Int32;
                  if (t == FieldTypeEnum::UInt64Field)    return BCTCommonUtilitiesRPNEvaluatorCPPWin::TypeCode::UInt64;
                  if (t == FieldTypeEnum::Int64Field)     return BCTCommonUtilitiesRPNEvaluatorCPPWin::TypeCode::Int64;
                  if (t == FieldTypeEnum::DoubleField)    return BCTCommonUtilitiesRPNEvaluatorCPPWin::TypeCode::Double;
                  if (t == FieldTypeEnum::StringField)    return BCTCommonUtilitiesRPNEvaluatorCPPWin::TypeCode::String;
                  if (t == FieldTypeEnum::BoolField)      return BCTCommonUtilitiesRPNEvaluatorCPPWin::TypeCode::Boolean;
                  if (t == FieldTypeEnum::EnumField)      return BCTCommonUtilitiesRPNEvaluatorCPPWin::TypeCode::String;
                  if (t == FieldTypeEnum::AggregateField) return BCTCommonUtilitiesRPNEvaluatorCPPWin::TypeCode::Object;
                  return BCTCommonUtilitiesRPNEvaluatorCPPWin::TypeCode::Empty;
            };

         public:
            virtual ~BaseField() {};
            void Value(const T v)
            {
               // TODO: rules to implement here, localization, etc
               if (_state == FieldStateEnum::Constant)
               {
                  throw "error: attempting to set constant field"; // TODO localize
               }
               if (_state == FieldStateEnum::Computed)
               {
                  throw "error: attempting to set computed field"; // TODO localize
               }
               ValueInternal(v, false);
            }

            void Unset()
            {
               if (_state == FieldStateEnum::Constant)
               {
                  throw "error: attempting to set constant field"; // TODO localize
               }
               _state = FieldStateEnum::NotSet;
            }

            const T Value()
            {
               // rules to implement here
               switch (_state)
               {
               case FieldStateEnum::NotSet: // TODO: internationalize 
                  throw "error: value has not been set";
               case FieldStateEnum::Unavailable:
                  throw "error: not available in this version";

               case FieldStateEnum::Computed:
                  // fall through for now
                  break;
               case FieldStateEnum::Default:
                  return _default;
               }
               return _val;
            }

            virtual const FieldStateEnum::FieldState State()
            {
               return _state;
            }

            operator T()
            {
               return this->Value();
            }

            virtual const std::string FieldName()
            {
               return _fieldName;
            }

            virtual const FieldTypeEnum::FieldType FieldType()
            {
               return _type;
            }

            virtual const BCTCommonUtilitiesRPNEvaluatorCPPWin::TypeCode TypeCode()
            {
               return _typeCode;
            }

            const std::string DefaultStr()
            {
               return findFieldMeta()._default;
            }

            const bool HasValue()
            {
               // TODO handle Computed after field as been computed
               return (_state == FieldStateEnum::Set || _state == FieldStateEnum::Constant || _state == FieldStateEnum::Default);
            }

            virtual const int16_t FieldSetCounter()
            {
               return _fieldSetCounter;
            }

            
            protected:
               virtual const std::string ComputedValueString()
               {
                  std::stringstream ss;
                  ss << Value();
                  return ss.str();
               }

               virtual void ComputedValueString(std::string val)
               {
                  T out;
                  std::stringstream ss;
                  ss << val;
                  ss >> out;
                  ValueInternal(out, true);
               }

               void ValueInternal(const T v, bool fromCalculation)
               {
                  _val = v;
                  FieldStateEnum::FieldState metaState = findFieldMeta()._fieldState;
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

               void SetDefault(const T def)
               {
                 _default = def;
                 _val = def;
               }
         };
      }
   }
}
