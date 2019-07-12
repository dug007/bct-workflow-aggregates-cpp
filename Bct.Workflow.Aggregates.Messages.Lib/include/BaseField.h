#pragma once

#include <vector>
#include <algorithm>

#include "AbstractAggregate.h"
#include "AbstractField.h"
#include "FieldMeta.h"
#include "VersionMetaData.h"


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
            BaseField()
            {
            }

            /// <summary>
            /// Constructor.
            /// </summary>
            /// <param name="fieldName">Name of this field.</param>
            /// <param name="t">Type of this field.</param>
            /// <param name="ver">Version this field is associated with.</param>
            /// <param name="metaData"></param>
            /// <param name="aggregate"></param>
            BaseField(const std::string fieldName, const TypeEnum::Type t, const int16_t ver, const std::vector<VersionMetaData> &metaData,  AbstractAggregate *aggregate)
               : _fieldName(fieldName), _type(t),  _ver(ver), _metaData(metaData), _aggregate(aggregate), _fieldSetCounter(0)
            {
               FieldMeta fm = findFieldMeta();
               FieldStateEnum::FieldState state = fm._fieldState;
               _state = state;
            }

            virtual ~BaseField() {};

            // Set/Get --------------------->

            /// <summary>
            /// 
            /// </summary>
            /// <param name="v"></param>
            void Value(const T v)
            {
               if (_state == FieldStateEnum::Constant)
               {
                  throw "error: attempting to set constant field"; // TODO internalize - User Story 126598
               }
               ValueInternal(v, false);
            }

            T Value() const
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

            void Unset()
            {
               if (_state == FieldStateEnum::Constant)
               {
                  throw "error: attempting to set constant field"; // TODO internalize - User Story 126598
               }
               _state = FieldStateEnum::NotSet;
            }

            // Set/Get ------------------------------<

            operator T() const
            {
               return this->Value();
            }

            // AbstractField ------------>

            virtual  std::string FieldName() const
            {
               return _fieldName;
            }

            virtual  TypeEnum::Type Type() const
            {
               return _type;
            }

            virtual  FieldStateEnum::FieldState State() const
            {
               return _state;
            }

            virtual uint32_t FieldSetCounter() const
            {
               return _fieldSetCounter;
            }

            // AbstractField -------------------<

            const std::string DefaultStr()
            {
               return findFieldMeta()._default;
            }

            const bool HasValue() const
            {
               // TODO handle Computed after field as been computed - User Story 126600
               return (_state == FieldStateEnum::Set || _state == FieldStateEnum::Constant || _state == FieldStateEnum::Default);
            }

         protected:

            // AbstractField ----------->

            virtual  std::string ComputedValueString() const
            {
               // TODO Use serialization library for string<->type conversion - User Story 126886
               std::stringstream ss;
               ss << Value();
               return ss.str();
            }

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
            std::vector<VersionMetaData> _metaData;
            int16_t _ver;
            uint32_t _fieldSetCounter;
            AbstractAggregate *_aggregate;

            const FieldMeta findFieldMeta()
            {
               std::vector<FieldMeta> fm = _metaData[_ver].fieldMetaData;
               for (size_t i = 0; i < fm.size(); i++)
               {
                  if (fm[i].FieldName() == _fieldName)
                  {
                     return fm[i];
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
