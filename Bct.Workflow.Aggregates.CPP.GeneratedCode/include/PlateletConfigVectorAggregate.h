#pragma once

#include "BaseAggregate.h"
#include "BaseField.h"
#include "VectorField.h"
#include "PlateletTemplateAggregate.h"

using namespace Bct::Workflow::Aggregates;

namespace Bct
{
   namespace Workflow
   {
      namespace Implementation
      {
         class PlateletConfigVectorAggregate : public BaseAggregate
         {
         private:
            void bindMetaData();
            static AggregateMetaData s_metaData;
            static bool s_initialized;

         public:
            VectorField<PlateletTemplateAggregate> templates;
            BaseField<double>  postCellsPerMl;
            BaseField<int32_t> minTemplateCount;
            BaseField<int32_t> maxTemplateCount;
            BaseField<double>  minPostCellsPerMl;
            BaseField<double>  maxPostCellsPerMl;
            BaseField<double>  malePostCellsPerMl;
            BaseField<double>  femalePostCellsPerMl;

            PlateletConfigVectorAggregate(const std::string &version);
            virtual ~PlateletConfigVectorAggregate();
         };

      }
   }
}
