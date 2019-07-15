
//************ CODE GENERATION STARTS HERE ****************

#include "PlateletConfigAggregate.h"

namespace Bct
{
   namespace Workflow
   {
      namespace Aggregates
      {
 
         PlateletConfigAggregate::PlateletConfigAggregate(const std::string version) :
            BaseAggregate(version, &s_metaData),
            postCellsPerMl("postCellsPerMl", TypeEnum::DoubleType, MetaData(), this),
            minTemplateCount("minTemplateCount", TypeEnum::Int32Type, MetaData(), this),
            maxTemplateCount("maxTemplateCount", TypeEnum::Int32Type, MetaData(), this),
            minPostCellsPerMl("minPostCellsPerMl", TypeEnum::DoubleType, MetaData(), this),
            maxPostCellsPerMl("maxPostCellsPerMl", TypeEnum::DoubleType, MetaData(), this),
            malePostCellsPerMl("malePostCellsPerMl", TypeEnum::DoubleType, MetaData(), this),
            femalePostCellsPerMl("femalePostCellsPerMl", TypeEnum::DoubleType, MetaData(), this)
         {
            FieldList().push_back(&postCellsPerMl);
            FieldList().push_back(&minTemplateCount);
            FieldList().push_back(&maxTemplateCount);
            FieldList().push_back(&minPostCellsPerMl);
            FieldList().push_back(&maxPostCellsPerMl);
            FieldList().push_back(&malePostCellsPerMl);
            FieldList().push_back(&femalePostCellsPerMl);

            if (!s_initialized)
            {
               initMetaData();
            }
            SyncCurrentVersion();
         }

         PlateletConfigAggregate::~PlateletConfigAggregate()
         {
         }

         void PlateletConfigAggregate::initMetaData()
         {
            VersionMetaData &aggMeta = MetaData();
            AbstractAggregate *agg = this;

            std::string vers[2] =
            {
               "1.0.0",
               "1.1.0"
            };

            FieldStateEnum::FieldState _postCellsPerMlStates[2] =
            {
               FieldStateEnum::NotSet,
               FieldStateEnum::Unavailable
            };

            std::string _postCellsPerMlDefaults[2] =
            {
               "100.0",
               "0.0"
            };

            FieldStateEnum::FieldState _minTemplateCountStates[2] =
            {
               FieldStateEnum::Constant,
               FieldStateEnum::Unavailable
            };

            std::string _minTemplateCountDefaults[2] =
            {
               "1",
               "0"
            };

            FieldStateEnum::FieldState _maxTemplateCountStates[2] =
            {
               FieldStateEnum::Constant,
               FieldStateEnum::Unavailable
            };

            std::string _maxTemplateCountDefaults[2] =
            {
               "10",
               "0"
            };

            FieldStateEnum::FieldState _minPostCellsPerMlStates[2] =
            {
               FieldStateEnum::Constant,
               FieldStateEnum::Constant
            };

            std::string _minPostCellsPerMlDefaults[2] =
            {
               "80.0",
               "80.0"
            };
            FieldStateEnum::FieldState _maxPostCellsPerMlStates[2] =
            {
               FieldStateEnum::Constant,
               FieldStateEnum::Constant
            };

            std::string _maxPostCellsPerMlDefaults[2] =
            {
               "200.0",
               "200.0"
            };

            FieldStateEnum::FieldState _malePostCellsPerMlStates[2] =
            {
               FieldStateEnum::Unavailable,
               FieldStateEnum::NotSet
            };

            std::string _malePostCellsPerMlDefaults[2] =
            {
               "0.0",
               "100.0"
            };

            FieldStateEnum::FieldState _femalePostCellsPerMlStates[2] =
            {
               FieldStateEnum::Unavailable,
               FieldStateEnum::NotSet
            };

            std::string _femalePostCellsPerMlDefaults[2] =
            {
               "0.0",
               "100.0"
            };


            for (uint16_t i = 0; i < std::size(vers); i++)
            {
               aggMeta.versionInfo.push_back(VersionInfo(vers[i]));

               FieldMeta postCellsPerMl_("postCellsPerMl", _postCellsPerMlStates[i], _postCellsPerMlDefaults[i], i);
               FieldMeta minTemplateCount_("minTemplateCount", _minTemplateCountStates[i], _minTemplateCountDefaults[i], i);
               FieldMeta maxTemplateCount_("maxTemplateCount", _maxTemplateCountStates[i], _maxTemplateCountDefaults[i], i);
               FieldMeta minPostCellsPerMl_("minPostCellsPerMl", _minPostCellsPerMlStates[i], _minPostCellsPerMlDefaults[i], i);
               FieldMeta maxPostCellsPerMl_("maxPostCellsPerMl", _maxPostCellsPerMlStates[i], _maxPostCellsPerMlDefaults[i], i);
               FieldMeta malePostCellsPerMl_("malePostCellsPerMl", _malePostCellsPerMlStates[i], _malePostCellsPerMlDefaults[i], i);
               FieldMeta femalePostCellsPerMl_("femalePostCellsPerMl", _femalePostCellsPerMlStates[i], _femalePostCellsPerMlDefaults[i], i);

               aggMeta.fieldMetaData.push_back(postCellsPerMl_);
               aggMeta.fieldMetaData.push_back(minTemplateCount_);
               aggMeta.fieldMetaData.push_back(maxTemplateCount_);
               aggMeta.fieldMetaData.push_back(minPostCellsPerMl_);
               aggMeta.fieldMetaData.push_back(maxPostCellsPerMl_);
               aggMeta.fieldMetaData.push_back(malePostCellsPerMl_);
               aggMeta.fieldMetaData.push_back(femalePostCellsPerMl_);
            }

            s_initialized = true;
         }

         VersionMetaData PlateletConfigAggregate::s_metaData;
         bool PlateletConfigAggregate::s_initialized = false;

      }
   }
}