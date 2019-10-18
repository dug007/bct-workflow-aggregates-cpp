#pragma once

#include "BaseAggregate.h"
#include "BaseField.h"
#include "BaseFieldRo.h"
#include "AbstractAggregate.h"
#include "AbstractField.h"
#include "EnumField.h"
#include "EnumFieldRo.h"
#include "StringField.h"
#include "StringFieldRo.h"

using namespace Bct::Workflow::Aggregates;

namespace Bct
{
   namespace Workflow
   {
      namespace Implementation
      {
         class Sample1Aggregate : public BaseAggregate
         {
         private:
            void bindMetaData();
            static AggregateMetaData s_metaData;
            static bool s_initialized;

         public:

            BaseField<double>    Field1;
            BaseField<int32_t>   Field7;
            BaseFieldRo<int32_t> Field7ro;    // readonly - no setter
            BaseField<int32_t>   Field7c;     // constant - setter throws
            BaseField<int32_t>   Field7d;     // defaulted
            BaseField<int32_t>   Field7com;   // computed
            BaseField<int32_t>   Field7x;     // extra field for tests
            EnumField<int32_t, FieldStateEnum::FieldState> FieldEnum;
            EnumFieldRo<int32_t, FieldStateEnum::FieldState> FieldEnumRo;
            StringField FieldString;
            StringFieldRo FieldStringro;

            Sample1Aggregate();
            Sample1Aggregate(const std::string &version);
            virtual ~Sample1Aggregate();
            AggregateMetaData &MetaData() const;

            friend bool operator==(const Sample1Aggregate& lhs, const Sample1Aggregate& rhs)
            {
               return true;
               //return (lhs.Field1.State == rhs.Field1.State && 
               //   lhs.Field7 == rhs.Field7 &&
               //   lhs.Field7ro == rhs.Field7ro &&
               //   lhs.Field7c == rhs.Field7c &&
               //   lhs.Field7d == rhs.Field7d &&
               //   lhs.Field7com == rhs.Field7com &&
               //   lhs.Field7x == rhs.Field7x
                  //lhs.FieldEnum == rhs.FieldEnum &&
                  //lhs.FieldEnumRo == rhs.FieldEnumRo &&
                  //lhs.FieldString == rhs.FieldString &&
                  //lhs.FieldStringRo == rhs.FieldStringRo
//                  );

            }


         };

      }
   }
}
