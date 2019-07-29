#pragma once

#include "BaseAggregate.h"
#include "BaseField.h"

namespace Bct
{
   namespace Workflow
   {
      namespace Aggregates
      {
         class PlateletConfigAggregate : public BaseAggregate
         {
         private:
            void bindMetaData();
            static AggregateMetaData s_metaData;
            static bool s_initialized;

         public:
            BaseField<double>  postCellsPerMl;
            BaseField<int32_t> minTemplateCount;
            BaseField<int32_t> maxTemplateCount;
            BaseField<double>  minPostCellsPerMl;
            BaseField<double>  maxPostCellsPerMl;
            BaseField<double>  malePostCellsPerMl;
            BaseField<double>  femalePostCellsPerMl;

            PlateletConfigAggregate(const std::string &version);
            virtual ~PlateletConfigAggregate();
         };

      }
   }
}
