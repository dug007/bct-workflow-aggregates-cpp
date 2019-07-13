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

            FieldDouble volumeMl;
            FieldDouble cellsPerMl;
            FieldDouble yield;
            FieldDouble minVolumeMl;
            FieldDouble maxVolumeMl;
            FieldDouble minCellsPerMl;
            FieldDouble maxCellsPerMl;
            FieldDouble minYield;
            FieldDouble maxYield;

            PlateletTemplateAggregate(const std::string version);

            virtual ~PlateletTemplateAggregate();
         };
      }
   }
}