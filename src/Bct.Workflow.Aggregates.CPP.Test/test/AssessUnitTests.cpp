#include <vector>
#include "AssessmentRule.h"
#include "AggAssess.h"
#include "BaseAggregate.h"
#include "AssessMetaData.h"
#include "catch.hpp"

using namespace Bct::Workflow::Aggregates;
using namespace Bct::Workflow::Implementation;

class AssessMetaDataLocal
{
public:

   AggregateMetaData metaData;

   AssessMetaDataLocal()
   {
      std::vector<std::string> vers;
      vers.push_back( "1.0.0" ); vers.push_back( "1.1.0" ); vers.push_back( "1.2.0" );
      vers.push_back( "1.3.0" ); vers.push_back( "1.4.0" );

      for (std::vector<std::string>::const_iterator itr = vers.begin(); itr != vers.end(); ++itr )
      {
         metaData.versionInfo.push_back(VersionInfo(*itr));
         VersionMetaData vm;
         metaData.versionMetaData.push_back(vm);
      }

      metaData.addField(0, "field1", Bct::Workflow::TypeEnum::Int32Type);
      metaData.addField(1, "field2", Bct::Workflow::TypeEnum::Int32Type);

      metaData.addFieldMetaToAllVersions(0, FieldStateEnum::Default, "1");
      metaData.addFieldMetaToAllVersions(1, FieldStateEnum::Default, "10");

      metaData.addAssessmentRule("assessv0", "assessv0", "field2 10 ==", "field1 field2 ==").toVersion(0);
      metaData.addAssessmentRule("assessv1", "assessv1", "field2 10 ==", "field1 field2 !=").toVersion(1);
      metaData.addAssessmentRule("assessv2", "assessv2", "field2 10 ==", "field1 field2 + 11 ==").toVersion(2);
      metaData.addAssessmentRule("assessv012", "assessv012", "field2 10 ==", "field1 field2 + 1 - 10 ==")
         .toVersion(0) .toVersion(1) .toVersion(2);
   };

};

TEST_CASE("AssessRulesTest", "[test]")
{
   // Setup metadata then initialize aggregate class with this metadata
   // AggComputeFieldMetaData is defined above
   AssessMetaDataLocal separateMetaData;
   AggAssess::bindMetaData(&separateMetaData.metaData);

   AggAssess a0("1.0.0");
   AggAssess a1("1.1.0");
   AggAssess a2("1.2.0");

   // prove assessment all work in their versions
   AssessmentResult r0 = a0.Assess();
   AssessmentResult r1 = a1.Assess();
   AssessmentResult r2 = a2.Assess();

   CHECK(r0.isSuccess() == false); // field1 field2 ==
   CHECK(r1.isSuccess() == true);  // field1 field2 !=
   CHECK(r2.isSuccess() == true);  // field1 field2 + 11 ==
}
