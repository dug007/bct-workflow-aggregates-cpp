#pragma once

#include <vector>
#include <algorithm>
#include "VersionMetaData.h"
#include "FieldMeta.h"
#include "AbstractField.h"

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
            std::string _fieldName;
            std::vector<VersionMetaData> _metaData;
            int16_t _ver;

         public:
            BaseField()
            {
            }
            BaseField(const std::string fieldName, const FieldTypeEnum::FieldType t, const int16_t ver, const std::vector<VersionMetaData> &metaData)
               : _fieldName(fieldName), _type(t),  _ver(ver), _metaData(metaData)
            {
               FieldMeta fm = findFieldMeta();
               FieldStateEnum::FieldState state = fm._fieldState;
               _state = state;

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
               _val = v;
               FieldStateEnum::FieldState metaState = findFieldMeta()._fieldState;
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
                  _state = FieldStateEnum::Set;
               }

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

            const std::string DefaultStr()
            {
               return findFieldMeta()._default;
            }

            const bool HasValue()
            {
               // TODO handle Computed after field as been computed
               return (_state == FieldStateEnum::Set || _state == FieldStateEnum::Constant || _state == FieldStateEnum::Default);
            }

            protected:
               void ValueInternal(const T v)
               {
                  _val = v;
                  FieldStateEnum::FieldState metaState = findFieldMeta()._fieldState;
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
                     _state = FieldStateEnum::Set;
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
