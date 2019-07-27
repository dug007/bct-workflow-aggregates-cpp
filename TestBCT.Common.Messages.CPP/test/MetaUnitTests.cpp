#include "AggregateMetaData.h"
#include "FluentMeta.h"
#include "FieldMeta.h"

#include "catch.hpp"

using namespace Bct::Workflow::Aggregates;

class TestMetaData
{
public:

   AggregateMetaData md;

   TestMetaData()
   {
      std::string vers[3] =
      {
         "1.0.0",
         "1.1.0",
         "1.2.0",
      };

      for (uint16_t i = 0; i < std::size(vers); i++)
      {
         md.versionInfo.push_back(VersionInfo(vers[i]));
         VersionMetaData vm;
         md.versionMetaData.push_back(vm);
      };


   };
};


TEST_CASE("FluentMetaTests", "[test]")
{
   TestMetaData tm;
   //tm.md.addMeta("field1", FieldStateEnum::Default, "2");
}
