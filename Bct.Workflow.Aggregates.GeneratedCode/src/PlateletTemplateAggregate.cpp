//************ CODE GENERATION STARTS HERE ****************

#include "PlateletTemplateAggregate.h"

namespace Bct
{
   namespace Workflow
   {
      namespace Aggregates
      {
         PlateletTemplateAggregate::PlateletTemplateAggregate(const std::string &version) :
            BaseAggregate(version, &s_metaData),
            volumeMl("volumeMl", TypeEnum::DoubleType, MetaData(), this),
            cellsPerMl("cellsPerMl", TypeEnum::DoubleType, MetaData(), this),
            yield("yield", TypeEnum::DoubleType, MetaData(), this),
            minVolumeMl("minVolumeMl", TypeEnum::DoubleType, MetaData(), this),
            maxVolumeMl("maxVolumeMl", TypeEnum::DoubleType, MetaData(), this),
            minCellsPerMl("minCellsPerMl", TypeEnum::DoubleType, MetaData(), this),
            maxCellsPerMl("maxCellsPerMl", TypeEnum::DoubleType, MetaData(), this),
            minYield("minYield", TypeEnum::DoubleType, MetaData(), this),
            maxYield("maxYield", TypeEnum::DoubleType, MetaData(), this)
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

            if (!s_initialized)
            {
               initMetaData();
            }
            SyncRootVersion();
         }

         PlateletTemplateAggregate::~PlateletTemplateAggregate()
         {
         };

         void PlateletTemplateAggregate::initMetaData()
         {
            AggregateMetaData &aggMeta = MetaData();
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


            for (uint16_t  i = 0; i < std::size(vers); i++)
            {
               aggMeta.versionInfo.push_back(VersionInfo(vers[i]));
               VersionMetaData vm;
               aggMeta.versionMetaData.push_back(vm);

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
               aggMeta.versionMetaData[i].fieldMetaDataI.push_back((int16_t)aggMeta.fieldMetaData.size() - 1);
               aggMeta.fieldMetaData.push_back(cellsPerMl_);
               aggMeta.versionMetaData[i].fieldMetaDataI.push_back((int16_t)aggMeta.fieldMetaData.size() - 1);
               aggMeta.fieldMetaData.push_back(yield_);
               aggMeta.versionMetaData[i].fieldMetaDataI.push_back((int16_t)aggMeta.fieldMetaData.size() - 1);
               aggMeta.fieldMetaData.push_back(minVolumeMl_);
               aggMeta.versionMetaData[i].fieldMetaDataI.push_back((int16_t)aggMeta.fieldMetaData.size() - 1);
               aggMeta.fieldMetaData.push_back(maxVolumeMl_);
               aggMeta.versionMetaData[i].fieldMetaDataI.push_back((int16_t)aggMeta.fieldMetaData.size() - 1);
               aggMeta.fieldMetaData.push_back(minCellsPerMl_);
               aggMeta.versionMetaData[i].fieldMetaDataI.push_back((int16_t)aggMeta.fieldMetaData.size() - 1);
               aggMeta.fieldMetaData.push_back(maxCellsPerMl_);
               aggMeta.versionMetaData[i].fieldMetaDataI.push_back((int16_t)aggMeta.fieldMetaData.size() - 1);
               aggMeta.fieldMetaData.push_back(minYield_);
               aggMeta.versionMetaData[i].fieldMetaDataI.push_back((int16_t)aggMeta.fieldMetaData.size() - 1);
               aggMeta.fieldMetaData.push_back(maxYield_);
               aggMeta.versionMetaData[i].fieldMetaDataI.push_back((int16_t)aggMeta.fieldMetaData.size() - 1);


            }
            // Simple computation rules
            {
               ComputeRule cr1("yieldId1", "yield", "1 1 ==", "cellsPerMl volumeMl *", ".0.1."); // TODO make $True - User Story 126600
               aggMeta.computeRules.push_back(cr1);
            }
            {
               ComputeRule cr1("yieldId2", "yield", "volumeMl yield $EnteredLater", "cellsPerMl volumeMl *", ".0.1.");
               ComputeRule cr3("cellsPerMlId1", "cellsPerMl", "volumeMl cellsPerMl $EnteredLater yield cellsPerMl $EnteredLater &&", "yield volumeMl /", ".0.1.");
               ComputeRule cr2("volumeMlId1", "volumeMl", "cellsPerMl volumeMl $EnteredLater yield volumeMl $EnteredLater &&", "yield cellsPerMl /", ".0.1.");

               aggMeta.computeRules.push_back(cr1);
               aggMeta.versionMetaData[0].computeRulesI.push_back((int16_t)aggMeta.computeRules.size() - 1);
               aggMeta.versionMetaData[1].computeRulesI.push_back((int16_t)aggMeta.computeRules.size() - 1);
               aggMeta.computeRules.push_back(cr2);
               aggMeta.versionMetaData[0].computeRulesI.push_back((int16_t)aggMeta.computeRules.size() - 1);
               aggMeta.versionMetaData[1].computeRulesI.push_back((int16_t)aggMeta.computeRules.size() - 1);
               aggMeta.computeRules.push_back(cr3);
               aggMeta.versionMetaData[0].computeRulesI.push_back((int16_t)aggMeta.computeRules.size() - 1);
               aggMeta.versionMetaData[1].computeRulesI.push_back((int16_t)aggMeta.computeRules.size() - 1);
            }

            s_initialized = true;
         }

         AggregateMetaData PlateletTemplateAggregate::s_metaData;
         bool PlateletTemplateAggregate::s_initialized = false;

      }
   }
}