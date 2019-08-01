#include "FieldMeta.h"

namespace Bct
{
   namespace Workflow
   {
      namespace Aggregates
      {
         FieldMeta::FieldMeta(std::string const &fieldName, FieldStateEnum::FieldState const &fieldState, std::string const &def, int16_t ver) :
            _fieldName(fieldName), _fieldState(fieldState), _default(def), _parentVer(ver)
         {
         }

         FieldMeta::FieldMeta(const std::string fieldName, const FieldStateEnum::FieldState fieldState, int16_t parentVer, int16_t childVer) :
            _fieldName(fieldName), _fieldState(fieldState), _parentVer(parentVer), _childVer(childVer)
         {
         }

         std::string FieldMeta::FieldName()
         {
            return _fieldName;
         }
      }
   }
}