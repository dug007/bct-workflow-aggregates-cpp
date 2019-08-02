#include "StringField.h"

class AbstractAggregate;

namespace Bct
{
   namespace Workflow
   {
      namespace Aggregates
      {
         StringField::StringField(int32_t fieldId, AbstractAggregate *aggregate)
            : BaseField(fieldId, TypeEnum::StringType, aggregate)
         {
         }

         void StringField::initMetaData(int16_t ver)
         {
            _ver = ver;

            // search for the metadata for corresponding version and field name, then initialize this field
            // with that located metadata instance
            FieldMeta &fm = findFieldMeta();
            const FieldStateEnum::FieldState &state = fm._fieldState;
            StateRef() = state;

            if (state == FieldStateEnum::Constant || state == FieldStateEnum::Default)
            {
               setDefault(DefaultStr());
            }
         }

         void StringField::ComputedValueString(const std::string & val)
         {
            ValueInternal(val, true);
         }
      }
   }
}
