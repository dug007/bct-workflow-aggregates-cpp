
//************ CODE GENERATION STARTS HERE ****************

#include "PlateletConfigAggregate.h"

namespace Bct
{
   namespace Workflow
   {
      namespace Implementation
      {
 
         PlateletConfigAggregate::PlateletConfigAggregate(const std::string &version) :
            BaseAggregate(version),
            postCellsPerMl(0, this),
            minTemplateCount(1, this),
            maxTemplateCount(2, this),
            minPostCellsPerMl(3, this),
            maxPostCellsPerMl(4, this),
            malePostCellsPerMl(5, this),
            femalePostCellsPerMl(6, this)
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
               bindMetaData();
            }
            syncVersion();
         }

         PlateletConfigAggregate::~PlateletConfigAggregate()
         {
         }

         void PlateletConfigAggregate::bindMetaData()
         {
            AggregateMetaData &aggMeta = MetaData();
            AbstractAggregate *agg = this;

            std::vector<std::string> vers;
            vers.push_back( "1.0.0" ); vers.push_back( "1.1.0" );

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

            aggMeta.addField(0, "postCellsPerMl", Bct::Workflow::TypeEnum::DoubleType);
            aggMeta.addField(1, "minTemplateCount", Bct::Workflow::TypeEnum::Int32Type);
            aggMeta.addField(2, "maxTemplateCount", Bct::Workflow::TypeEnum::Int32Type);
            aggMeta.addField(3, "minPostCellsPerMl", Bct::Workflow::TypeEnum::DoubleType);
            aggMeta.addField(4, "maxPostCellsPerMl", Bct::Workflow::TypeEnum::DoubleType);
            aggMeta.addField(5, "malePostCellsPerMl", Bct::Workflow::TypeEnum::DoubleType);
            aggMeta.addField(6, "femalePostCellsPerMl", Bct::Workflow::TypeEnum::DoubleType);

            uint16_t i = 0;
            for ( std::vector<std::string>::const_iterator itr = vers.begin(); itr != vers.end(); ++itr, ++i )
            {
               aggMeta.versionInfo.push_back(VersionInfo(*itr));
               VersionMetaData vm;
               aggMeta.versionMetaData.push_back(vm);

               FieldMeta postCellsPerMl_(0, _postCellsPerMlStates[i], _postCellsPerMlDefaults[i], i);
               FieldMeta minTemplateCount_(1, _minTemplateCountStates[i], _minTemplateCountDefaults[i], i);
               FieldMeta maxTemplateCount_(2, _maxTemplateCountStates[i], _maxTemplateCountDefaults[i], i);
               FieldMeta minPostCellsPerMl_(3, _minPostCellsPerMlStates[i], _minPostCellsPerMlDefaults[i], i);
               FieldMeta maxPostCellsPerMl_(4, _maxPostCellsPerMlStates[i], _maxPostCellsPerMlDefaults[i], i);
               FieldMeta malePostCellsPerMl_(5, _malePostCellsPerMlStates[i], _malePostCellsPerMlDefaults[i], i);
               FieldMeta femalePostCellsPerMl_(6, _femalePostCellsPerMlStates[i], _femalePostCellsPerMlDefaults[i], i);

               aggMeta.fieldMetaData.push_back(postCellsPerMl_);
               aggMeta.versionMetaData[i].fieldMetaDataI.push_back((int16_t)aggMeta.fieldMetaData.size() - 1);
               aggMeta.fieldMetaData.push_back(minTemplateCount_);
               aggMeta.versionMetaData[i].fieldMetaDataI.push_back((int16_t)aggMeta.fieldMetaData.size() - 1);
               aggMeta.fieldMetaData.push_back(maxTemplateCount_);
               aggMeta.versionMetaData[i].fieldMetaDataI.push_back((int16_t)aggMeta.fieldMetaData.size() - 1);
               aggMeta.fieldMetaData.push_back(minPostCellsPerMl_);
               aggMeta.versionMetaData[i].fieldMetaDataI.push_back((int16_t)aggMeta.fieldMetaData.size() - 1);
               aggMeta.fieldMetaData.push_back(maxPostCellsPerMl_);
               aggMeta.versionMetaData[i].fieldMetaDataI.push_back((int16_t)aggMeta.fieldMetaData.size() - 1);
               aggMeta.fieldMetaData.push_back(malePostCellsPerMl_);
               aggMeta.versionMetaData[i].fieldMetaDataI.push_back((int16_t)aggMeta.fieldMetaData.size() - 1);
               aggMeta.fieldMetaData.push_back(femalePostCellsPerMl_);
               aggMeta.versionMetaData[i].fieldMetaDataI.push_back((int16_t)aggMeta.fieldMetaData.size() - 1);
            }

            s_initialized = true;
         }

         AggregateMetaData PlateletConfigAggregate::s_metaData;
         bool PlateletConfigAggregate::s_initialized = false;

      }
   }
}
