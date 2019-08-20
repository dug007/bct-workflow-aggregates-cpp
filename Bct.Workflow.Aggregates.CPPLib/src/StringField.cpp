#include "StringField.h"

class AbstractAggregate;

namespace Bct
{
   namespace Workflow
   {
      namespace Aggregates
      {
         StringField::StringField(int32_t fieldId, AbstractAggregate * const aggregate)
            : BaseField(fieldId, aggregate)
         {
         }

         StringField::StringField(const StringField &other, AbstractAggregate * const aggregate)
            : BaseField<std::string>(other, aggregate)
         {
         }

         std::string & StringField::operator=(const StringField & fld)
         {
            this->Value(fld.Value());
            return this->_val;
         }

         StringField::~StringField()
         {
         }

         std::string StringField::operator=(std::string const &val)
         {
            this->Value(val);
            return *this;
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

         std::string StringField::ComputedValueString() const
         {
            return BaseField::ComputedValueString();
         }

      }
   }
}
