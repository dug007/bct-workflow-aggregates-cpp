#include "FieldInfo.h"

namespace Bct
{
   namespace Workflow
   {
      namespace Aggregates
      {
         FieldInfo::FieldInfo(int16_t fieldId, std::string const &fieldName, TypeEnum::Type const &fieldType) :
            _fieldId(fieldId), _fieldName(fieldName), _fieldType(fieldType), _fieldSubtype(TypeEnum::EmptyType)
         {
         }

         FieldInfo::FieldInfo(int16_t fieldId, std::string const &fieldName, TypeEnum::Type const &fieldType, TypeEnum::Type const &fieldSubtype) :
            _fieldId(fieldId), _fieldName(fieldName), _fieldType(fieldType), _fieldSubtype(fieldSubtype)
         {
         }

         int16_t FieldInfo::fieldId() const
         {
            return _fieldId;
         }

         std::string FieldInfo::fieldName() const
         {
            return _fieldName;
         }

         TypeEnum::Type FieldInfo::FieldType() const
         {
            return _fieldType;
         }

         TypeEnum::Type FieldInfo::FieldSubtype() const
         {
            return _fieldSubtype;
         }
      }
   }
}