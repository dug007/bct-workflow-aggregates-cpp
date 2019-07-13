//************ CODE GENERATION STARTS HERE ****************

#include "PlateletTemplateAggregate.h"

namespace Bct
{
   namespace Workflow
   {
      namespace Aggregates
      {
         PlateletTemplateAggregate::PlateletTemplateAggregate(const std::string version) :
            BaseAggregate(version),
            volumeMl("volumeMl", AggregateMetaData(), this),
            cellsPerMl("cellsPerMl", AggregateMetaData(), this),
            yield("yield", AggregateMetaData(), this),
            minVolumeMl("minVolumeMl", AggregateMetaData(), this),
            maxVolumeMl("maxVolumeMl", AggregateMetaData(), this),
            minCellsPerMl("minCellsPerMl", AggregateMetaData(), this),
            maxCellsPerMl("maxCellsPerMl", AggregateMetaData(), this),
            minYield("minYield", AggregateMetaData(), this),
            maxYield("maxYield", AggregateMetaData(), this)
         {

            FieldList().push_back(&volumeMl);
            FieldList().push_back(&cellsPerMl);
            FieldList().push_back(&yield);
            FieldList().push_back(&minVolumeMl);
            FieldList().push_back(&maxVolumeMl);
            FieldList().push_back(&minCellsPerMl);
            FieldList().push_back(&maxCellsPerMl);
            FieldList().push_back(&minYield);
            FieldList().push_back(&maxYield);

            initMetaData();
         }

         PlateletTemplateAggregate::~PlateletTemplateAggregate()
         {
         };

         void PlateletTemplateAggregate::initMetaData()
         {
            VersionMetaData &aggMeta = AggregateMetaData();
            AbstractAggregate *agg = this;
            std::string vers[2] =
            {
               "1.0.0",
               "1.1.0"
            };

            FieldStateEnum::FieldState _volumeMlStates[2] =
            {
               FieldStateEnum::NotSet,
               FieldStateEnum::NotSet
            };

            std::string _volumeMlDefaults[2] =
            {
               "0.0",
               "0.0"
            };

            FieldStateEnum::FieldState _cellsPerMlStates[2] =
            {
               FieldStateEnum::NotSet,
               FieldStateEnum::NotSet
            };

            std::string _cellsPerMlDefaults[2] =
            {
               "0.0",
               "0.0"
            };

            FieldStateEnum::FieldState _yieldStates[2] =
            {
               FieldStateEnum::NotSet,
               FieldStateEnum::NotSet
            };

            std::string _yieldDefaults[2] =
            {
               "0.0",
               "0.0"
            };

            FieldStateEnum::FieldState _minVolumeMlStates[2] =
            {
               FieldStateEnum::Constant,
               FieldStateEnum::Constant
            };

            std::string _minVolumeMlDefaults[2] =
            {
               "100.0",
               "100.0"
            };

            FieldStateEnum::FieldState _maxVolumeMlStates[2] =
            {
               FieldStateEnum::Constant,
               FieldStateEnum::Constant
            };

            std::string _maxVolumeMlDefaults[2] =
            {
               "500.0",
               "500.0"
            };

            FieldStateEnum::FieldState _minCellsPerMlStates[2] =
            {
               FieldStateEnum::Constant,
               FieldStateEnum::Constant
            };

            std::string _minCellsPerMlDefaults[2] =
            {
               "0.5e6",
               "0.5e6"
            };

            FieldStateEnum::FieldState _maxCellsPerMlStates[2] =
            {
               FieldStateEnum::Constant,
               FieldStateEnum::Constant
            };

            std::string _maxCellsPerMlDefaults[2] =
            {
               "5.0e6",
               "5.0e6"
            };

            FieldStateEnum::FieldState _minYieldStates[2] =
            {
               FieldStateEnum::Unavailable,
               FieldStateEnum::Constant
            };

            std::string _minYieldDefaults[2] =
            {
               "0.0",
               "1.0e8"
            };

            FieldStateEnum::FieldState _maxYieldStates[2] =
            {
               FieldStateEnum::Unavailable,
               FieldStateEnum::Constant
            };

            std::string _maxYieldDefaults[2] =
            {
               "0.0",
               "2.0e9"
            };

            for (int16_t i = 0; i < 2; i++)
            {
               aggMeta.versionInfo.push_back(VersionInfo(vers[i]));

               FieldMeta volumeMl_("volumeMl", _volumeMlStates[i], _volumeMlDefaults[i], i);
               FieldMeta cellsPerMl_("cellsPerMl", _cellsPerMlStates[i], _cellsPerMlDefaults[i], i);
               FieldMeta yield_("yield", _yieldStates[i], _yieldDefaults[i], i);
               FieldMeta minVolumeMl_("minVolumeMl", _minVolumeMlStates[i], _minVolumeMlDefaults[i], i);
               FieldMeta maxVolumeMl_("maxVolumeMl", _maxVolumeMlStates[i], _maxVolumeMlDefaults[i], i);
               FieldMeta minCellsPerMl_("minCellsPerMl", _minCellsPerMlStates[i], _minCellsPerMlDefaults[i], i);
               FieldMeta maxCellsPerMl_("maxCellsPerMl", _maxCellsPerMlStates[i], _maxCellsPerMlDefaults[i], i);
               FieldMeta minYield_("minYield", _minYieldStates[i], _minYieldDefaults[i], i);
               FieldMeta maxYield_("maxYield", _maxYieldStates[i], _maxYieldDefaults[i], i);

               aggMeta.fieldMetaData.push_back(volumeMl_);
               aggMeta.fieldMetaData.push_back(cellsPerMl_);
               aggMeta.fieldMetaData.push_back(yield_);
               aggMeta.fieldMetaData.push_back(minVolumeMl_);
               aggMeta.fieldMetaData.push_back(maxVolumeMl_);
               aggMeta.fieldMetaData.push_back(minCellsPerMl_);
               aggMeta.fieldMetaData.push_back(maxCellsPerMl_);
               aggMeta.fieldMetaData.push_back(minYield_);
               aggMeta.fieldMetaData.push_back(maxYield_);
            }
            // Simple computation rules
            {
               ComputeRule cr1("yieldId1", "yield", "1 1 ==", "cellsPerMl volumeMl *"); // TODO make $True - User Story 126600
               aggMeta.computeRules.push_back(cr1);
            }
            {
               ComputeRule cr1("yieldId2", "yield", "volumeMl yield $EnteredLater", "cellsPerMl volumeMl *");
               ComputeRule cr3("cellsPerMlId1", "cellsPerMl", "volumeMl cellsPerMl $EnteredLater yield cellsPerMl $EnteredLater &&", "yield volumeMl /");
               ComputeRule cr2("volumeMlId1", "volumeMl", "cellsPerMl volumeMl $EnteredLater yield volumeMl $EnteredLater &&", "yield cellsPerMl /");
               aggMeta.computeRules.push_back(cr1);
               aggMeta.computeRules.push_back(cr2);
               aggMeta.computeRules.push_back(cr3);
            }

            SyncCurrentVersion(); // determine ver for aggregate based on state of metadata

            volumeMl.initMeta(Ver());
            cellsPerMl.initMeta(Ver());
            yield.initMeta(Ver());
            minVolumeMl.initMeta(Ver());
            maxVolumeMl.initMeta(Ver());
            minCellsPerMl.initMeta(Ver());
            maxCellsPerMl.initMeta(Ver());
            minYield.initMeta(Ver());
            maxYield.initMeta(Ver());
         }
      }
   }
}