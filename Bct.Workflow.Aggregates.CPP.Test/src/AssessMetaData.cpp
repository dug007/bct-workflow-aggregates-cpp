#include "AssessMetaData.h"
#include "BaseAggregate.h"

using namespace Bct::Workflow::Aggregates;

namespace Bct
{
   namespace Workflow
   {
      namespace Implementation
      {
         AssessMetaData::AssessMetaData()
         {
            std::string vers[5] =
            {
               "1.0.0",
               "1.1.0",
               "1.2.0",
               "1.3.0",
               "1.4.0"
            };

            for (uint16_t i = 0; i < std::size(vers); i++)
            {
               metaData.versionInfo.push_back(VersionInfo(vers[i]));
               VersionMetaData vm;
               metaData.versionMetaData.push_back(vm);
            }

            metaData.addField(0, "field1", Bct::Workflow::TypeEnum::Int32Type);
            metaData.addField(1, "field2", Bct::Workflow::TypeEnum::Int32Type);

            // One set of field metadata for all version
            FieldMeta field1Meta(0, FieldStateEnum::Default, "1", BaseAggregate::InAllVersions); // all versions
            FieldMeta field2Meta(1, FieldStateEnum::Default, "10", BaseAggregate::InAllVersions);

            int16_t k, cnt;

            metaData.fieldMetaData.push_back(field1Meta);
            k = 0; cnt = (int16_t)metaData.fieldMetaData.size() - 1;
            metaData.versionMetaData[k++].fieldMetaDataI.push_back(cnt); // since this is for all versions no need for more vectors

            metaData.fieldMetaData.push_back(field2Meta);
            k = 0; cnt = (int16_t)metaData.fieldMetaData.size() - 1;
            metaData.versionMetaData[k++].fieldMetaDataI.push_back(cnt);

            AssessmentRule ar0("assessv0", "assessv0", "field2 10 ==", "field1 field2 ==");      // fails
            AssessmentRule ar1("assessv1", "assessv1", "field2 10 ==", "field1 field2 !=");      // passes
            AssessmentRule ar2("assessv2", "assessv2", "field2 10 ==", "field1 field2 + 11 =="); // passes
            AssessmentRule ar3("assessv012", "assessv012", "field2 10 ==", "field1 field2 + 1 - 10 ==");

            metaData.assessmentRules.push_back(ar0);
            metaData.versionMetaData[0].assessmentRulesI.push_back((int16_t)metaData.assessmentRules.size() - 1);
            metaData.assessmentRules.push_back(ar1);
            metaData.versionMetaData[1].assessmentRulesI.push_back((int16_t)metaData.assessmentRules.size() - 1);
            metaData.assessmentRules.push_back(ar2);
            metaData.versionMetaData[2].assessmentRulesI.push_back((int16_t)metaData.assessmentRules.size() - 1);
            metaData.assessmentRules.push_back(ar3);
            metaData.versionMetaData[0].assessmentRulesI.push_back((int16_t)metaData.assessmentRules.size() - 1);
            metaData.versionMetaData[1].assessmentRulesI.push_back((int16_t)metaData.assessmentRules.size() - 1);
            metaData.versionMetaData[2].assessmentRulesI.push_back((int16_t)metaData.assessmentRules.size() - 1);
         };
      }
   }
}
