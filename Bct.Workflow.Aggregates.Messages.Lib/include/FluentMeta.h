#pragma once

//#include <string>
//#include <vector>
//#include <map>
//#include "VersionInfo.h"
//#include "FieldMeta.h"
//#include "AssessmentRule.h"
//#include "ComputeRule.h"
//#include "VersionMetaData.h"
#include "FieldMeta.h"
#include "AggregateMetaData.h"

namespace Bct
{
   namespace Workflow
   {
      namespace Aggregates
      {
         class AggregateMetaData;

         class FluentMeta
         {
         public:
            FluentMeta(AggregateMetaData &aggMeta, FieldMeta &fieldMeta, size_t position);
            FluentMeta &toVersion(int16_t ver);
         private:
            FieldMeta &_fieldMeta;
            AggregateMetaData &_aggMeta;
            size_t _position;
         };
      }
   }
}