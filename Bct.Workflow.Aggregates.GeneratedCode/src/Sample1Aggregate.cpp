
//************ CODE GENERATION STARTS HERE ****************

#include "Sample1Aggregate.h"

namespace Bct
{
   namespace Workflow
   {
      namespace Aggregates
      {
         Sample1Aggregate::Sample1Aggregate(const std::string version) :
            BaseAggregate(version),
            Field1("Field1", AggregateMetaData(), this),
            Field7("Field7", AggregateMetaData(), this),
            Field7d("Field7d", AggregateMetaData(), this),
            Field7c("Field7c", AggregateMetaData(), this),
            Field7ro("Field7ro", AggregateMetaData(), this),
            Field7com("Field7com", AggregateMetaData(), this),
            Field7x("Field7x", AggregateMetaData(), this)
         {

            FieldList().push_back(&Field1);
            FieldList().push_back(&Field7);
            FieldList().push_back(&Field7d);
            FieldList().push_back(&Field7c);
            FieldList().push_back(&Field7ro);
            FieldList().push_back(&Field7com);
            FieldList().push_back(&Field7x);

            initMetaData();
         }

         Sample1Aggregate::~Sample1Aggregate()
         {
         };

         void Sample1Aggregate::initMetaData()
         {
            VersionMetaData &aggMeta = AggregateMetaData();
            AbstractAggregate *agg = this;

            std::string vers[3] =
            {
               "1.0.0",
               "1.1.0",
               "1.2.0"
            };

            FieldStateEnum::FieldState _Field1states[3] =
            {
               FieldStateEnum::NotSet,
               FieldStateEnum::NotSet,
               FieldStateEnum::NotSet
            };

            std::string _Field1defaults[3] =
            {
               "0.0",
               "0.0",
               "0.0"
            };

            FieldStateEnum::FieldState _Field7states[3] =
            {
               FieldStateEnum::NotSet,
               FieldStateEnum::NotSet,
               FieldStateEnum::NotSet,
            };

            std::string _Field7defaults[3] =
            {
               "0",
               "0",
               "0"
            };

            FieldStateEnum::FieldState _Field7rostates[3] =
            {
               FieldStateEnum::NotSet,
               FieldStateEnum::NotSet,
               FieldStateEnum::Constant
            };

            std::string _Field7rodefaults[3] =
            {
               "1",
               "2",
               "5"
            };

            FieldStateEnum::FieldState _Field7cstates[3] =
            {
               FieldStateEnum::NotSet,
               FieldStateEnum::NotSet,
               FieldStateEnum::Constant
            };

            std::string _Field7cdefaults[3] =
            {
               "1",
               "2",
               "6"
            };

            FieldStateEnum::FieldState _Field7dstates[3] =
            {
               FieldStateEnum::NotSet,
               FieldStateEnum::NotSet,
               FieldStateEnum::Default
            };

            std::string _Field7ddefaults[3] =
            {
               "0",
               "0",
               "-1"
            };

            FieldStateEnum::FieldState _Field7comstates[3] =
            {
               FieldStateEnum::NotSet,
               FieldStateEnum::NotSet,
               FieldStateEnum::Computed
            };

            std::string _Field7comdefaults[3] =
            {
               "0",
               "0",
               "-1"
            };

            FieldStateEnum::FieldState _Field7xstates[3] =
            {
               FieldStateEnum::NotSet,
               FieldStateEnum::NotSet,
               FieldStateEnum::NotSet
            };

            std::string _Field7xdefaults[3] =
            {
               "0",
               "0",
               "0"
            };


            for (int16_t i = 0; i < 3; i++)
            {
               aggMeta.versionInfo.push_back(VersionInfo(vers[i]));
            }

            for (int16_t i = 0; i < 3; i++)
            {
               FieldMeta Field1_("Field1", _Field1states[i], _Field1defaults[i], i);
               FieldMeta Field7_("Field7", _Field7states[i], _Field7defaults[i], i);
               FieldMeta Field7d_("Field7d", _Field7dstates[i], _Field7ddefaults[i], i);
               FieldMeta Field7c_("Field7c", _Field7cstates[i], _Field7cdefaults[i], i);
               FieldMeta Field7ro_("Field7ro", _Field7rostates[i], _Field7rodefaults[i], i);
               FieldMeta Field7com_("Field7com", _Field7comstates[i], _Field7comdefaults[i], i);
               FieldMeta Field7x_("Field7x", _Field7xstates[i], _Field7xdefaults[i], i);

               // This could be a sparse array - this example is fixed to 3 versions, but here we are
               // leaving out the aggregate data for the first version
               if (i != 1)
               {
                  aggMeta.fieldMetaData.push_back(Field1_);
                  aggMeta.fieldMetaData.push_back(Field7_);
               }
               aggMeta.fieldMetaData.push_back(Field7d_);
               aggMeta.fieldMetaData.push_back(Field7c_);
               aggMeta.fieldMetaData.push_back(Field7ro_);
               aggMeta.fieldMetaData.push_back(Field7com_);
               aggMeta.fieldMetaData.push_back(Field7x_);
            }

            SyncCurrentVersion(); // determine ver for aggregate based on metadata

            Field1.initMetaData(Ver());
            Field7.initMetaData(Ver());
            Field7d.initMetaData(Ver());
            Field7c.initMetaData(Ver());
            Field7ro.initMetaData(Ver());
            Field7com.initMetaData(Ver());
            Field7x.initMetaData(Ver());

            // Simple computation rules
            ComputeRule cr1("Field1Id1", "Field1", "1 1 ==", "Field1 20.0 +");
            ComputeRule cr2("Field7Id1", "Field7", "Field7x Field7d $EnteredLater", "Field7x");
            ComputeRule cr3("Field7Id2", "Field7", "Field7d Field7x $EnteredLater", "Field7d");

            aggMeta.computeRules.push_back(cr1);
            aggMeta.computeRules.push_back(cr2);
            aggMeta.computeRules.push_back(cr3);
         };
      };
   }
}