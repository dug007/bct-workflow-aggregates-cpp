#include "FieldInfo.h"

namespace Bct
{
   namespace Workflow
   {
      namespace Aggregates
      {
         FieldInfo::FieldInfo(int16_t fieldId, std::string const &fieldName, TypeEnum::Type const &fieldType) :
            _fieldId(fieldId), _fieldName(fieldName), _fieldType(fieldType)
         {
         }

         int16_t FieldInfo::FieldId() const
         {
            return _fieldId;
         }

         std::string FieldInfo::FieldName() const
         {
            return _fieldName;
         }

         TypeEnum::Type FieldInfo::FieldType() const
         {
            return _fieldType;
         }
      }
   }
}