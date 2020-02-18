#include <vector>
#include "FluentMeta.h"
#include "FieldMeta.h"

namespace Bct
{
   namespace Workflow
   {
      namespace Aggregates
      {
         FluentMeta::FluentMeta(AggregateMetaData &aggMeta, FieldMeta &fieldMeta, size_t position) :
            _fieldMeta(fieldMeta), _aggMeta(aggMeta), _position(position)
         {
         };

         FluentMeta &FluentMeta::toVersion(int16_t ver)
         {
            int16_t i = static_cast<int16_t>(_position);
            _fieldMeta._parentVer = ver;
            _aggMeta.versionMetaData[ver].fieldMetaDataI.push_back(i);
            return *this;
         }
      }
   }
}
