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
            std::vector<VersionMetaData> _metaData; // feature fEmbedMetaData
            int16_t _ver; // feature fEmbedMetaData

         public:
            BaseField()
            {
            }
            BaseField(std::string fieldName, FieldTypeEnum::FieldType t, int16_t ver, std::vector<VersionMetaData> &metaData) : _fieldName(fieldName), _type(t),  _ver(ver), _metaData(metaData) // feature fEmbedMetaData
            {
               FieldMeta fm = findFieldMeta(); // feature fEmbedMetaData
               FieldStateEnum::FieldState state = fm._fieldState;
               _state = state;

            }
            //BaseField(FieldTypeEnum::FieldType t, FieldStateEnum::FieldState initState, T &val) : _type(t), _state(initState)
            //{
            //   Init(val);
            //};
         private:
            void Init(T &val)
            {
               switch (_state)
               {
               case FieldStateEnum::Default:
               case FieldStateEnum::Constant:
                  _default = val;
                  _val = val;
                  break;
               }
            }

            FieldMeta findFieldMeta() // feature fEmbedMetaData
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
            // setter-getter
            void Value(T v)
            {
               // TODO: rules to implement here, localization, etc
               if (_state == FieldStateEnum::Constant)
               {
                  throw "error: attempting to set constant field"; // TODO localize
               }
               _val = v;
               FieldMeta fm = findFieldMeta(); // feature fEmbedMetaData
               FieldStateEnum::FieldState metaState = fm._fieldState;
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
            T Value()
            {
               // rules to implement here
               switch (State())
               {
               case FieldStateEnum::NotSet: // TODO: internationalize 
                  throw "error: value has not been set";
               case FieldStateEnum::Unavailable:
                  throw "error: not available in this version";
                  break;
               case FieldStateEnum::Computed:

                  break;
               case FieldStateEnum::Default:
                  return _default;
               }
               return _val;
            };

            FieldStateEnum::FieldState State()
            {
               return _state;
            }
            // conversion
            operator T()
            {
               return this->Value();
            }
            std::string DefaultStr()
            {
               return findFieldMeta()._default; // feature fEmbedMetaData
            };
            protected:
               void SetDefault(T def)
               {
                 _default = def;
                 _val = def;
 
               }
         };
      }
   }
}
