#pragma once

#include "BaseAggregate.h"
#include "BaseField.h"
#include "FieldInt32.h"
#include "FieldInt32Ro.h"
#include "FieldDouble.h"
#include "FieldDoubleRo.h"
#include "AbstractField.h"
#include "AbstractAggregate.h"

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

         public:

            FieldDouble Field1;
            FieldInt32 Field7;
            FieldInt32Ro Field7ro;  // readonly - no setter
            FieldInt32 Field7c;     // constant - setter throws
            FieldInt32 Field7d;     // defaulted
            FieldInt32 Field7com;   // computed
            FieldInt32 Field7x;     // extra field for tests

            Sample1Aggregate(const std::string version);
            virtual ~Sample1Aggregate();
         };

      }
   }
}
