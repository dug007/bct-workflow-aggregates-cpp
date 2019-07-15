#pragma once

#include "BaseAggregate.h"
#include "BaseField.h"


namespace Bct
{
   namespace Workflow
   {
      namespace Aggregates
      {
         class PlateletTemplateAggregate : public BaseAggregate
         {
         private:
            static VersionMetaData s_metaData;
            static bool s_initialized;
            void initMetaData();

         public:

            BaseField<double> volumeMl;
            BaseField<double> cellsPerMl;
            BaseField<double> yield;
            BaseField<double> minVolumeMl;
            BaseField<double> maxVolumeMl;
            BaseField<double> minCellsPerMl;
            BaseField<double> maxCellsPerMl;
            BaseField<double> minYield;
            BaseField<double> maxYield;

            PlateletTemplateAggregate(const std::string &version);
            virtual ~PlateletTemplateAggregate();
         };
      }
   }
}