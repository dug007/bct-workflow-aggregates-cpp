#include "StringFieldRo.h"

namespace Bct
{
   namespace Workflow
   {
      namespace Aggregates
      {
         StringFieldRo::StringFieldRo(int32_t fieldId, AbstractAggregate * const aggregate)
            : StringField(fieldId, aggregate)
         {
         }

         StringFieldRo::StringFieldRo(const StringFieldRo &other, AbstractAggregate * const aggregate)
            : StringField(other, aggregate)
         {
         }

         StringFieldRo::~StringFieldRo()
         {
         }

         StringFieldRo & StringFieldRo::operator=(const StringFieldRo & fld)
         {
            if (&fld != this)
            {
               StringField::operator=(fld);
            }
            return *this;
         }



         const std::string StringFieldRo::Value()
         {
            return StringField::Value();
         };
      }
   }
}


