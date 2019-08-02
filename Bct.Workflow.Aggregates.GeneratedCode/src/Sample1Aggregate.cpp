
//************ CODE GENERATION STARTS HERE ****************

#include "Sample1Aggregate.h"
#include "AbstractAggregate.h"


namespace Bct
{
   namespace Workflow
   {
      namespace Aggregates
      {
         Sample1Aggregate::Sample1Aggregate(const std::string &version) :
            BaseAggregate(version),
            Field1(0, TypeEnum::DoubleType, this),
            Field7(1, TypeEnum::Int32Type, this),
            Field7d(2, TypeEnum::Int32Type, this),
            Field7c(3, TypeEnum::Int32Type, this),
            Field7ro(4, TypeEnum::Int32Type, this),
            Field7com(5, TypeEnum::Int32Type, this),
            Field7x(6, TypeEnum::Int32Type, this),
            FieldEnum(7, TypeEnum::Int32Type, "FieldStateEnum::FieldState",
               "0 1 2 3 4 5 6",
               "Unavailable NotSet Set Constant Default Computed", this),
            FieldEnumRo(8, TypeEnum::Int32Type, "FieldStateEnum::FieldState",
               "0 1 2 3 4 5 6",
               "Unavailable NotSet Set Constant Default Computed", this)

         {

            FieldList().push_back(&Field1);
            FieldList().push_back(&Field7);
            FieldList().push_back(&Field7d);
            FieldList().push_back(&Field7c);
            FieldList().push_back(&Field7ro);
            FieldList().push_back(&Field7com);
            FieldList().push_back(&Field7x);
            FieldList().push_back(&FieldEnum);
            FieldList().push_back(&FieldEnumRo);
            if (!s_initialized)
            {
               bindMetaData();
            }

            syncVersion();
         }

         Sample1Aggregate::Sample1Aggregate() :
            BaseAggregate(),
            Field1(0, TypeEnum::DoubleType, this),
            Field7(1, TypeEnum::Int32Type, this),
            Field7d(2, TypeEnum::Int32Type, this),
            Field7c(3, TypeEnum::Int32Type, this),
            Field7ro(4, TypeEnum::Int32Type, this),
            Field7com(5, TypeEnum::Int32Type, this),
            Field7x(6, TypeEnum::Int32Type, this),
            FieldEnum(7, TypeEnum::Int32Type, "FieldStateEnum::FieldState",
               "0 1 2 3 4 5 6",
               "Unavailable NotSet Set Constant Default Computed", this),
            FieldEnumRo(8, TypeEnum::Int32Type, "FieldStateEnum::FieldState",
               "0 1 2 3 4 5 6",
               "Unavailable NotSet Set Constant Default Computed", this)
         {

            FieldList().push_back(&Field1);
            FieldList().push_back(&Field7);
            FieldList().push_back(&Field7d);
            FieldList().push_back(&Field7c);
            FieldList().push_back(&Field7ro);
            FieldList().push_back(&Field7com);
            FieldList().push_back(&Field7x);
            FieldList().push_back(&FieldEnum);
            FieldList().push_back(&FieldEnumRo);
            if (!s_initialized)
            {
               bindMetaData();
            }
            syncVersion();
         }


         Sample1Aggregate::~Sample1Aggregate()
         {
         };

         void Sample1Aggregate::bindMetaData()
         {
            AggregateMetaData &aggMeta = MetaData();
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

            FieldStateEnum::FieldState _FieldEnumstates[3] =
            {
               FieldStateEnum::Default,
               FieldStateEnum::Default,
               FieldStateEnum::Default
            };

            std::string _FieldEnumdefaults[3] =
            {
               "1",
               "1",
               "1"
            };
            FieldStateEnum::FieldState _FieldEnumRostates[3] =
            {
               FieldStateEnum::Unavailable,
               FieldStateEnum::Unavailable,
               FieldStateEnum::Unavailable
            };

            std::string _FieldEnumRodefaults[3] =
            {
               "0",
               "0",
               "0"
            };



            for (uint16_t i = 0; i <std::size(vers); i++)
            {
               aggMeta.versionInfo.push_back(VersionInfo(vers[i]));
               VersionMetaData vm;
               aggMeta.versionMetaData.push_back(vm);
            }

            aggMeta.addField(0, "Field1", Bct::Workflow::TypeEnum::DoubleType);
            aggMeta.addField(1, "Field7", Bct::Workflow::TypeEnum::Int32Type);
            aggMeta.addField(2, "Field7d", Bct::Workflow::TypeEnum::Int32Type);
            aggMeta.addField(3, "Field7c", Bct::Workflow::TypeEnum::Int32Type);
            aggMeta.addField(4, "Field7ro", Bct::Workflow::TypeEnum::Int32Type);
            aggMeta.addField(5, "Field7com", Bct::Workflow::TypeEnum::Int32Type);
            aggMeta.addField(6, "Field7x", Bct::Workflow::TypeEnum::Int32Type);
            aggMeta.addField(7, "FieldEnum", Bct::Workflow::TypeEnum::Int32Type);
            aggMeta.addField(8, "FieldEnumRo", Bct::Workflow::TypeEnum::Int32Type);

            for (uint16_t i = 0; i < std::size(vers); i++)
            {
               FieldMeta Field1_(0, _Field1states[i], _Field1defaults[i], i);
               FieldMeta Field7_(1, _Field7states[i], _Field7defaults[i], i);
               FieldMeta Field7d_(2, _Field7dstates[i], _Field7ddefaults[i], i);
               FieldMeta Field7c_(3, _Field7cstates[i], _Field7cdefaults[i], i);
               FieldMeta Field7ro_(4, _Field7rostates[i], _Field7rodefaults[i], i);
               FieldMeta Field7com_(5, _Field7comstates[i], _Field7comdefaults[i], i);
               FieldMeta Field7x_(6, _Field7xstates[i], _Field7xdefaults[i], i);
               FieldMeta FieldEnum_(7, _FieldEnumstates[i], _FieldEnumdefaults[i], i);
               FieldMeta FieldEnumRo_(8, _FieldEnumRostates[i], _FieldEnumRodefaults[i], i);


               aggMeta.fieldMetaData.push_back(Field1_);
               aggMeta.versionMetaData[i].fieldMetaDataI.push_back((int16_t)aggMeta.fieldMetaData.size() - 1);
               aggMeta.fieldMetaData.push_back(Field7_);
               aggMeta.versionMetaData[i].fieldMetaDataI.push_back((int16_t)aggMeta.fieldMetaData.size() - 1);
               aggMeta.fieldMetaData.push_back(Field7d_);
               aggMeta.versionMetaData[i].fieldMetaDataI.push_back((int16_t)aggMeta.fieldMetaData.size() - 1);
               aggMeta.fieldMetaData.push_back(Field7c_);
               aggMeta.versionMetaData[i].fieldMetaDataI.push_back((int16_t)aggMeta.fieldMetaData.size() - 1);
               aggMeta.fieldMetaData.push_back(Field7ro_);
               aggMeta.versionMetaData[i].fieldMetaDataI.push_back((int16_t)aggMeta.fieldMetaData.size() - 1);
               aggMeta.fieldMetaData.push_back(Field7com_);
               aggMeta.versionMetaData[i].fieldMetaDataI.push_back((int16_t)aggMeta.fieldMetaData.size() - 1);
               aggMeta.fieldMetaData.push_back(Field7x_);
               aggMeta.versionMetaData[i].fieldMetaDataI.push_back((int16_t)aggMeta.fieldMetaData.size() - 1);
               aggMeta.fieldMetaData.push_back(FieldEnum_);
               aggMeta.versionMetaData[i].fieldMetaDataI.push_back((int16_t)aggMeta.fieldMetaData.size() - 1);
               aggMeta.fieldMetaData.push_back(FieldEnumRo_);
               aggMeta.versionMetaData[i].fieldMetaDataI.push_back((int16_t)aggMeta.fieldMetaData.size() - 1);
            }

            // Simple computation rules
            ComputeRule cr1("Field1Id1", "Field1", "1 1 ==", "Field1 20.0 +", ".0.1.2.");
            ComputeRule cr2("Field7Id1", "Field7", "Field7x Field7d $EnteredLater", "Field7x", ".0.1.2.");
            ComputeRule cr3("Field7Id2", "Field7", "Field7d Field7x $EnteredLater", "Field7d", ".0.1.2.");

            aggMeta.computeRules.push_back(cr1);
            aggMeta.versionMetaData[0].computeRulesI.push_back((int16_t)aggMeta.computeRules.size() - 1);
            aggMeta.versionMetaData[1].computeRulesI.push_back((int16_t)aggMeta.computeRules.size() - 1);
            aggMeta.versionMetaData[2].computeRulesI.push_back((int16_t)aggMeta.computeRules.size() - 1);
            aggMeta.computeRules.push_back(cr2);
            aggMeta.versionMetaData[0].computeRulesI.push_back((int16_t)aggMeta.computeRules.size() - 1);
            aggMeta.versionMetaData[1].computeRulesI.push_back((int16_t)aggMeta.computeRules.size() - 1);
            aggMeta.versionMetaData[2].computeRulesI.push_back((int16_t)aggMeta.computeRules.size() - 1);
            aggMeta.computeRules.push_back(cr3);
            aggMeta.versionMetaData[0].computeRulesI.push_back((int16_t)aggMeta.computeRules.size() - 1);
            aggMeta.versionMetaData[1].computeRulesI.push_back((int16_t)aggMeta.computeRules.size() - 1);
            aggMeta.versionMetaData[2].computeRulesI.push_back((int16_t)aggMeta.computeRules.size() - 1);

            s_initialized = true;
         };

         AggregateMetaData Sample1Aggregate::s_metaData;
         bool Sample1Aggregate::s_initialized = false;

         AggregateMetaData &Sample1Aggregate::MetaData() const
         {
            return s_metaData;
         }
      };
   }
}