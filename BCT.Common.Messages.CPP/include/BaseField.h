#pragma once
namespace Bct
{
   namespace Workflow
   {
      namespace Aggregates
      {
         template<class T>
         class BaseField
         {
         private:
            T _val;
            T _default;
            FieldStateEnum::FieldState _state;
            FieldTypeEnum::FieldType _type;

         public:
            BaseField()
            {
            }
            BaseField(FieldTypeEnum::FieldType t, FieldStateEnum::FieldState initState, T &val)
            {
               Init(t, initState, val);
            };
            void Init(FieldTypeEnum::FieldType t, FieldStateEnum::FieldState initState, T &val)
            {
               _state = initState;
               _type = t;
               switch (initState)
               {
               case FieldStateEnum::Default:
               case FieldStateEnum::Constant:
                  _default = val;
                  _val = val;
                  break;
               }
            }

            virtual ~BaseField() {};

            // setter-getter
            void Value(T v)
            {  // TODO: rules to implement here, localization, etc
               if (_state == FieldStateEnum::Constant)
               {
                  throw "error: attempting to set constant field"; // TODO localize
               }
               _val = v;
               if (v == _default)
               {
                  _state = FieldStateEnum::Default;
               }
               else
               {
                  _state = FieldStateEnum::Set;
               }
            }
            T Value()
            {
               // rules to implement here
               switch (_state)
               {
               case FieldStateEnum::NotSet: // TODO: internationalize 
                  throw "error: value has not been set";
               case FieldStateEnum::Unavailable:
                  throw "error: not available in this version";
                  break;
               case FieldStateEnum::Computed:

                  break;
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
         };
      }
   }
}
