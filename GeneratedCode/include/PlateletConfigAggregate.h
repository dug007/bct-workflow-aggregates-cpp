#pragma once

#include "BaseAggregate.h"
#include "FieldInt32.h"
#include "FieldInt32Ro.h"
#include "FieldDouble.h"
#include "FieldDoubleRo.h"

namespace Bct
{
   namespace Workflow
   {
      namespace Aggregates
      {
         class PlateletConfigAggregate : public BaseAggregate
         {
         private:
            void initMetaData();

         public:
            FieldDouble postCellsPerMl;
            FieldInt32 minTemplateCount;
            FieldInt32 maxTemplateCount;
            FieldDouble minPostCellsPerMl;
            FieldDouble maxPostCellsPerMl;
            FieldDouble malePostCellsPerMl;
            FieldDouble femalePostCellsPerMl;

            PlateletConfigAggregate(const std::string version);
            virtual ~PlateletConfigAggregate();
         };
      }
   }
}
