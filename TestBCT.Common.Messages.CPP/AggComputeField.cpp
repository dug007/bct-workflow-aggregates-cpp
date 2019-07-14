#include "AggComputeField.h"

#include "AbstractAggregate.h"


namespace Bct
{
   namespace Workflow
   {
      namespace Aggregates
      {
         AggComputeField::AggComputeField(const std::string version) :
            BaseAggregate(version, s_metaData),
            field1("field1", TypeEnum::Int32Type, MetaData(), this)
         {

            FieldList().push_back(&field1);
            if (!s_initialized)
            {
               initMetaData();
            }
            SyncCurrentVersion();
         }

         AggComputeField::AggComputeField() :
            BaseAggregate(s_metaData),
            field1("field1", TypeEnum::Int32Type, MetaData(), this)
         {

            FieldList().push_back(&field1);

            if (!s_initialized)
            {
               initMetaData();
            }
            SyncCurrentVersion();
         }

         void AggComputeField::initMetaData()
         {
            std::string vers[5] =
            {
               "1.0.0",
               "1.1.0",
               "1.2.0",
               "1.3.0",
               "1.4.0"
            };

            for (int16_t i = 0; i < std::size(vers); i++)
            {
               MetaData().versionInfo.push_back(VersionInfo(vers[i]));
            }

            // One set of field metadata for all version
            FieldMeta field1Meta("field1", FieldStateEnum::NotSet, "0", 0);
            MetaData().fieldMetaData.push_back(field1Meta);


            ComputeRule cr0("field1v0", "field1", "1 1 ==", "1 1 +",   ".0.");
            ComputeRule cr1("field1v1", "field1", "1 1 ==", "1 2 +",   ".1.");
            ComputeRule cr2("field1v2", "field1", "1 1 ==", "1 3 +",   ".2.");
            ComputeRule cr3_4("field1v3_4", "field1", "1 1 ==", "1 4 +", ".3.4.");

            MetaData().computeRules.push_back(cr0);
            MetaData().computeRules.push_back(cr1);
            MetaData().computeRules.push_back(cr2);
            MetaData().computeRules.push_back(cr3_4);

            s_initialized = true;
         };

         VersionMetaData AggComputeField::s_metaData;
         bool AggComputeField::s_initialized = false;
      };
   }
}