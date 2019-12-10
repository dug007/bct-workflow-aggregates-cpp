#include "StringField.h"

class AbstractAggregate;

namespace Bct
{
   namespace Workflow
   {
      namespace Aggregates
      {
         StringField::StringField(int32_t fieldId, AbstractAggregate * const aggregate)
            : BaseField<std::string>(fieldId, aggregate)
         {
         }

         StringField::StringField(const StringField &other, AbstractAggregate * const aggregate)
            : BaseField<std::string>(other, aggregate)
         {
         }

         StringField & StringField::operator=(const StringField & fld)
         {
            if (&fld != this)
            {
               BaseField<std::string>::operator=(fld);
            }
            return *this;
         }

         StringField::~StringField()
         {
         }

         std::string StringField::operator=(std::string const &val)
         {
            this->value(val);
            return *this;
         }

         void StringField::initMetaData(int16_t ver)
         {
            _ver = ver;

            // search for the metadata for corresponding version and field name, then initialize this field
            // with that located metadata instance
            FieldMeta &fm = findFieldMeta();
            const FieldStateEnum::FieldState &state = fm._fieldState;
            stateRef() = state;

            if (state == FieldStateEnum::Constant || state == FieldStateEnum::Default)
            {
               setDefault(defaultStr());
            }
         }

         void StringField::computedValueString(const std::string & val)
         {
            valueInternal(val, true);
         }

         std::string StringField::computedValueString() const
         {
            return BaseField<std::string>::computedValueString();
         }

         void StringField::serialize(PrettyWriter<StringBuffer> & writer) const
         {
            const std::string tmpStringValue = (std::string)(*this);
            writer.String(tmpStringValue.c_str());
         }
      }
   }
}
