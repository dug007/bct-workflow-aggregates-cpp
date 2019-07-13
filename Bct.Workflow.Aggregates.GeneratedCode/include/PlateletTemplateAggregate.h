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
         class PlateletTemplateAggregate : public BaseAggregate
         {
         private:
            void initMetaData();
            static VersionMetaData s_metaData;
            static bool s_initialized;

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

            PlateletTemplateAggregate(const std::string version);

            virtual ~PlateletTemplateAggregate();
         };
      }
   }
}