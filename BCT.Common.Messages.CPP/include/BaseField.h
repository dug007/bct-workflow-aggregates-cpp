#pragma once

#include <vector>
#include <algorithm>
#include "VersionMetaData.h"
#include "FieldMeta.h"

namespace Bct
{
   namespace Workflow
   {
      namespace Aggregates
      {
         const bool _fEmbedMetaData = true;

         template<class T>
         class BaseField
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

            const FieldStateEnum::FieldState State()
            {
               return _state;
            }

            operator T()
            {
               return this->Value();
            }

            const std::string DefaultStr()
            {
               return findFieldMeta()._default;
            }

            const bool HasValue()
            {
               return (_state == FieldStateEnum::Set || _state == FieldStateEnum::Constant || _state == FieldStateEnum::Default);
            }

            protected:
               void SetDefault(const T def)
               {
                 _default = def;
                 _val = def;
               }
         };
      }
   }
}
