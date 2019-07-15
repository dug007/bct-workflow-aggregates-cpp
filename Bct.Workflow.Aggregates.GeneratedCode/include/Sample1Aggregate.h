#pragma once

#include "BaseAggregate.h"
#include "BaseField.h"
#include "BaseFieldRo.h"

#include "AbstractField.h"

namespace Bct
{
   namespace Workflow
   {
      namespace Aggregates
      {
         class Sample1Aggregate : public BaseAggregate
         {
         private:
            void initMetaData();
            static VersionMetaData s_metaData;
            static bool s_initialized;

         public:

            BaseField<double>    Field1;
            BaseField<int32_t>   Field7;
            BaseFieldRo<int32_t> Field7ro;    // readonly - no setter
            BaseField<int32_t>   Field7c;     // constant - setter throws
            BaseField<int32_t>   Field7d;     // defaulted
            BaseField<int32_t>   Field7com;   // computed
            BaseField<int32_t>   Field7x;     // extra field for tests

            Sample1Aggregate();
            Sample1Aggregate(const std::string &version);
            virtual ~Sample1Aggregate();
         };

      }
   }
}
