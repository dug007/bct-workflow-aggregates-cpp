#include "FieldMeta.h"

namespace Bct
{
   namespace Workflow
   {
      namespace Aggregates
      {
         FieldMeta::FieldMeta(int16_t fieldId, FieldStateEnum::FieldState const &fieldState, std::string const &def, int16_t ver) :
            _fieldId(fieldId), _fieldState(fieldState), _default(def), _parentVer(ver)
         {
         }

         FieldMeta::FieldMeta(int16_t fieldId, const FieldStateEnum::FieldState fieldState, int16_t parentVer, int16_t childVer) :
            _fieldId(fieldId), _fieldState(fieldState), _parentVer(parentVer), _childVer(childVer)
         {
         }

         int16_t FieldMeta::FieldId()
         {
            return _fieldId;
         }
      }
   }
}