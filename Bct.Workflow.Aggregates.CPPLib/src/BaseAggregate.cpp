#include "BaseAggregate.h"

#include <stdint.h>
#include <sstream>

#include "FieldStateEnum.h"
#include "RPNEvaluator.h"
#include "AssessmentRule.h"
#include "AssessmentResult.h"
#include "NotAbleToGet.h"
#include "NoSuchVersion.h"
#include "NotAbleToSet.h"
#include "FieldInfo.h"

#include "BaseField.h"
#include "StringField.h"
#include "rapidjson/prettywriter.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/reader.h"
#include <iostream>  // [PL] just for testing

using namespace std;
using namespace rapidjson;

#define nullptr (NULL)

#define CLOG cout<<__LINE__<<endl;

namespace Bct
{
   namespace Workflow
   {
      namespace Aggregates
      {
         const std::string BaseAggregate::UseMostRecentVersionStr = "0.0.0";

         BaseAggregate::BaseAggregate(const std::string &version) :
            _version(version), _fieldSetCounter(0), _parent(nullptr)
         {
            if (version == UseMostRecentVersionStr)
            {
               _ver = BaseAggregate::UseMostRecentVersion;
            }
         }

         BaseAggregate::BaseAggregate() :
            _ver(BaseAggregate::UseMostRecentVersion), _fieldSetCounter(0), _parent(nullptr)
         {
         }

         BaseAggregate::BaseAggregate(int32_t fieldIdAsNested, BaseAggregate * const parentAsNested) :
            _fieldIdAsNested(fieldIdAsNested), _fieldSetCounter(0), _parent(parentAsNested)
         {
         }

         BaseAggregate::BaseAggregate(const BaseAggregate & other) :
            _version(other._version), _ver(other._ver),
            _fieldSetCounter(other._fieldSetCounter), _parent(nullptr),
            _fieldNameAsNested(other._fieldNameAsNested), _fieldIdAsNested(other._fieldIdAsNested)
         {
            // DO NOT try to copy the _fieldList or _aggList as they will be filled
            // by the body of the superclass
         }

         BaseAggregate::BaseAggregate(const BaseAggregate & other, BaseAggregate * const parent) :
            _version(other._version), _ver(other._ver),
            _fieldSetCounter(other._fieldSetCounter), _parent(parent),
            _fieldNameAsNested(other._fieldNameAsNested), _fieldIdAsNested(other._fieldIdAsNested)
         {
            // DO NOT try to copy the _fieldList or _aggList as they will be filled
            // by the body of the superclass
         }

         BaseAggregate & BaseAggregate::operator=(const BaseAggregate & other)
         {
            if (&other != this)
            {
               if (_parent != nullptr)
               {
                  _parent->operator=(other);
               }
            }
            return *this;

         }

         FieldMeta &BaseAggregate::findFieldMeta(int16_t parentVer)
         {
            // check metadata marked version or all versions in the version 0 vector
            std::vector<int16_t> &fmi0 = _parent->MetaData().versionMetaData[0].fieldMetaDataI; // indirection vector for version 0 / all versions
            if (fmi0.size() > 0)
            {
               for (size_t i = 0; i < fmi0.size(); i++)
               {
                  FieldMeta &fm = _parent->MetaData().fieldMetaData[fmi0[i]]; // indirection
                  if (fm.FieldId() == _fieldIdAsNested)
                  {
                     if (fm._parentVer == BaseAggregate::InAllVersions || (parentVer == 0 && fm._parentVer == 0))
                     {
                        return fm;
                     }
                     else
                     {
                        break;
                     }
                  }
               }
            }

            std::vector<int16_t> &fmi = _parent->MetaData().versionMetaData[parentVer].fieldMetaDataI; // indirection vector for version
            if (fmi.size() > 0)
            {
               for (size_t i = 0; i < fmi.size(); i++)
               {
                  FieldMeta &fm = _parent->MetaData().fieldMetaData[fmi[i]]; // indirection
                  if (fm.FieldId() == _fieldIdAsNested && fm._parentVer <= parentVer)
                  {
                     return fm;
                  }
               }
            }
            std::string aggName = typeid(*this).name();
            throw NoSuchVersion(aggName, _version); 
         }

         void BaseAggregate::syncChildVersion(int16_t parentVer)
         {
            FieldMeta &meta = findFieldMeta(parentVer);
            _ver = meta._childVer;
            _version = MetaData().versionInfo[_ver].Version();

            // initialize fields to current version
            for (size_t i = 0; i < _fieldList.size(); i++)
            {
               _fieldList[i]->initMetaData(Ver());
            }
            // initialize nested aggregates to current version of parent
            for (size_t i = 0; i < _aggList.size(); i++)
            {
               _aggList[i]->syncChildVersion(Ver());
            }
         }

         void BaseAggregate::syncVersion()
         {
            // do nothing unless aggregate is root aggregate
            if (_parent == nullptr)
            {
               if (_ver == BaseAggregate::UseMostRecentVersion) // seek most recent version
               {
                  AggregateMetaData &thisMd = MetaData();
                  _ver = static_cast<uint16_t>(thisMd.versionInfo.size() - 1);
                  _version = thisMd.versionInfo[_ver].Version();
               }
               else // use constuctor value
               {
                  bool found = false;
                  AggregateMetaData &thisMd = MetaData();
                  for (size_t i = 0; i < thisMd.versionInfo.size(); i++)
                  {
                     if (thisMd.versionInfo[i].Version() == _version)
                     {
                        _ver = (int16_t)i;
                        found = true;
                        break;
                     }
                  }
                  if (!found)
                  {
                     std::string aggName = typeid(*this).name();
                     throw NoSuchVersion(aggName, _version);
                  }
               }

               // initialize fields to current version
               for (size_t i = 0; i < _fieldList.size(); i++)
               {
                  _fieldList[i]->initMetaData(Ver());
               }
               // initialize nested aggregates to current version of parent
               for (size_t i = 0; i < _aggList.size(); i++)
               {
                  _aggList[i]->syncChildVersion(Ver());
               }
            }
         }
         int32_t &BaseAggregate::FieldIdAsNested()
         {
            return _fieldIdAsNested;
         }
         /**
          * Destructor
          */
         BaseAggregate::~BaseAggregate() {};

         const std::string& BaseAggregate::getVersion() const
         {
            return _version;
         };

         void BaseAggregate::updateCalculatedFields()
         {
            // populate variable map
            std::map<std::string, RPNEvaluator::RPNVariable> varMap;
            for (size_t i = 0; i < _fieldList.size(); i++)
            {
               AbstractField *f = _fieldList[i];
               std::string strVal;
               if (f->State() == FieldStateEnum::NotSet)
               {
                  strVal = "$Notset"; // TODO make sure this is correct - User Story 126600
               }
               else if (f->State() == FieldStateEnum::Unavailable)
               {
                  strVal = "$Unavailable"; // TODO make sure this is correct - User Story 126600
               }
               else
               {
                  strVal = f->ComputedValueString();
               }

               FieldStateEnum::FieldState &state = f->StateRef();
               std::string const &fieldName = MetaData().fieldInfo[f->FieldId()].FieldName();
               varMap[fieldName] = RPNEvaluator::RPNVariable(fieldName, f->Type(), strVal, state, f->FieldSetCounter());
            }


            std::vector<int16_t> &cRulesV = MetaData().versionMetaData[Ver()].computeRulesI;
            for (size_t iRule = 0; iRule < cRulesV.size(); iRule++) // over rules in current version
            {
               ComputeRule &cRule = MetaData().computeRules[cRulesV[iRule]]; // indirection
               for (size_t iField = 0; iField < _fieldList.size(); iField++) // over fields
               {
                  // find field calcuation in current version
                  AbstractField *f = _fieldList[iField];
                  const FieldStateEnum::FieldState &state = f->State();
                  const TypeEnum::Type &type = f->Type();
                  if (f->FieldId() == cRule.FieldId())
                  {
                     const std::string &condition = cRule.Condition();
                     const std::string &expression = cRule.Expression();
                     std::string answerValue;
                     TypeEnum::Type answerType;
                     RPNEvaluator::RPNEvaluator evaluator;
                     evaluator.EvaluateRPNExpression(condition, varMap, answerType, answerValue);
                     if ("true" == answerValue)
                     {
                        evaluator.EvaluateRPNExpression(expression, varMap, answerType, answerValue);
                        f->ComputedValueString(answerValue);
                     }
                  }
               }
            }
         }


         AssessmentResult BaseAggregate::Assess() const
         {
            AssessmentResult result;

            // populate variable map
            std::map<std::string, RPNEvaluator::RPNVariable> varMap;
            for (size_t i = 0; i < _fieldList.size(); i++)
            {
               AbstractField *f = _fieldList[i];
               std::string strVal;
               if (f->State() == FieldStateEnum::NotSet)
               {
                  strVal = "$Notset"; // TODO make sure this is correct - User Story 126600
               }
               else if (f->State() == FieldStateEnum::Unavailable)
               {
                  strVal = "$Unavailable"; // TODO make sure this is correct - User Story 126600
               }
               else
               {
                  strVal = f->ComputedValueString();
               }

               FieldStateEnum::FieldState &state = f->StateRef();
               std::string const &fieldName = MetaData().fieldInfo[f->FieldId()].FieldName();
               varMap[fieldName] = RPNEvaluator::RPNVariable(fieldName, f->Type(), strVal, state, f->FieldSetCounter());
            }

            std::vector<int16_t> const &aRulesV = MetaData().versionMetaData[Ver()].assessmentRulesI;
            for (size_t j = 0; j < aRulesV.size(); j++)
            {
               AssessmentRule &aRule = MetaData().assessmentRules[aRulesV[j]]; // indirection
               const std::string &condition = aRule.Condition();
               const std::string &expression = aRule.Expression();
               std::string answerValue;
               TypeEnum::Type answerType;
               RPNEvaluator::RPNEvaluator evaluator;
               evaluator.EvaluateRPNExpression(condition, varMap, answerType, answerValue);
               if ("true" == answerValue)
               {
                  evaluator.EvaluateRPNExpression(expression, varMap, answerType, answerValue);
                  if (answerValue != "true")
                  {
                     result.addError(aRule.StringId(), answerValue);
                  }
               }
            }
            return result;
         }

         void BaseAggregate::convertToVersion(const std::string toVersionStr)
         {
            // TODO implement - User Story 126595

            // populate variable map
            int16_t toVersion = -1;
            for (size_t i = 0; i < MetaData().versionInfo.size(); i++)
            {
               if (MetaData().versionInfo[i].Version() == toVersionStr)
               {
                  toVersion = (int16_t)i;
                  break;
               }
            }
            if (toVersion == -1)
            {
               std::string aggName = typeid(*this).name();
               throw NoSuchVersion(aggName, toVersionStr);
            }

            std::map<std::string, RPNEvaluator::RPNVariable> varMap;
            for (size_t i = 0; i < _fieldList.size(); i++)
            {
               AbstractField *f = _fieldList[i];
               std::string strVal;
               if (f->State() == FieldStateEnum::NotSet)
               {
                  strVal = "$Notset"; // TODO make sure this is correct - User Story 126600
               }
               else if (f->State() == FieldStateEnum::Unavailable)
               {
                  strVal = "$Unavailable"; // TODO make sure this is correct - User Story 126600
               }
               else
               {
                  strVal = f->ComputedValueString();
               }

               FieldStateEnum::FieldState &state = f->StateRef();
               std::string const &fieldName = MetaData().fieldInfo[f->FieldId()].FieldName();
               varMap[fieldName] = RPNEvaluator::RPNVariable(fieldName, f->Type(), strVal, state, f->FieldSetCounter());
            }

            std::vector<int16_t> const &vcRulesV = MetaData().versionMetaData[Ver()].versionChangeRulesI;
            for (size_t j = 0; j < vcRulesV.size(); j++)
            {
               VersionChangeRule &vcRule = MetaData().versionChangeRules[vcRulesV[j]]; // indirection
               const std::string &expression = vcRule.Expression();
               for (size_t iField = 0; iField < _fieldList.size(); iField++) // over fields
               {
                  // find field calcuation in current version
                  AbstractField *f = _fieldList[iField];
                  const FieldStateEnum::FieldState &state = f->State();
                  const TypeEnum::Type &type = f->Type();
                  if (f->FieldId() == vcRule.FieldId() && toVersion == vcRule.ToVersion())
                  {
                     const std::string &condition = vcRule.Condition();
                     const std::string &expression = vcRule.Expression();
                     std::string answerValue;
                     TypeEnum::Type answerType;
                     RPNEvaluator::RPNEvaluator evaluator;
                     evaluator.EvaluateRPNExpression(condition, varMap, answerType, answerValue);
                     if ("true" == answerValue)
                     {
                        evaluator.EvaluateRPNExpression(expression, varMap, answerType, answerValue);
                        f->ComputedValueString(answerValue);
                     }
                  }
               }
            }
            _ver = toVersion;
            _version = MetaData().versionInfo[_ver].Version();
         };


         const uint32_t &BaseAggregate::FieldSetCounter()
         {
            _fieldSetCounter++;
            return _fieldSetCounter;
         }

         std::vector<AbstractField*> & BaseAggregate::FieldList()
         {
            return _fieldList;
         }

         std::vector<AbstractAggregate*> & BaseAggregate::AggList()
         {
            return _aggList;
         }

         int32_t BaseAggregate::Ver() const
         {
            return _ver;
         }

         const std::string & BaseAggregate::Version() const
         {
            return _version;
         }

// [PL] #define COUT cout<<__LINE__<<endl;
         void BaseAggregate::serialize( PrettyWriter<StringBuffer> & writer ) const
         {
            //TODO - User Story 129258
            // Elsewhere, ensure computedValueString() uses serialializeValue/deserializeValue as appropriate.
            // See deserialize below.
            writer.StartObject();
            // Fields
            for (int32_t i = 0; i < static_cast<int32_t>(_fieldList.size()); i++)
            {
               const AbstractField *fld = _fieldList[i];
               //const std::string &val = fld->serializeValue();
               const int32_t fieldId = fld->FieldId();
               const std::string &fieldName = MetaData().fieldInfo[fieldId].FieldName();
               const TypeEnum::Type &type = fld->Type();
               // now put into JSON
               writer.Key(fieldName.c_str());
               //cout << "fieldName: " << fieldName.c_str() << ";   type: " << type << endl;
               try
               {
                  switch( type )
                  {
                     case TypeEnum::BoolType:
                        writer.Bool( (static_cast<const BaseField<bool>*>(fld))->Value() );
                        break;
                     case TypeEnum::Int32Type:
                        writer.Int( (static_cast<const BaseField<int32_t>*>(fld))->Value() );
                        break;
                     case TypeEnum::UInt32Type:
                        writer.Uint( (static_cast<const BaseField<uint32_t>*>(fld))->Value() );
                        break;
                     case TypeEnum::Int64Type:
                        writer.Int64( (static_cast<const BaseField<int64_t>*>(fld))->Value() );
                        break;
                     case TypeEnum::UInt64Type:
                        writer.Uint64( (static_cast<const BaseField<uint64_t>*>(fld))->Value() );
                        break;
                     case TypeEnum::DoubleType:
                        writer.Double( (static_cast<const BaseField<double>*>(fld))->Value() );
                        break;
                     case TypeEnum::StringType:
                        {
                           const std::string tmpStringValue = (std::string)( *(static_cast<const StringField*>(fld)) );
                           writer.String( tmpStringValue.c_str() );
                        }
                        break;
                     case TypeEnum::EnumType:
                        // [PL] TODO As of 10-24-19, this case is never executed. Rather, it goes to case TypeEnum::Int32Type.
                        break;
                     case TypeEnum::ArrayType:// [PL] TODO
                        writer.String( "<TODO: ArrayType>");
                        break;
                     case TypeEnum::EmptyType: // [PL] TODO ?
                        writer.String( "<TODO: EmptyType>");
                        break;
                     default:
                        writer.String( "ERROR: unexpected type");
                        break;
                  }// switch(type)
               }//try
               catch(NotAbleToGet & exNotAbleToGet)
               {
                  cerr << "NotAbleToGet exception: " << exNotAbleToGet.what() << endl;
                  writer.Null();
               }
            }// for(_fieldList)

// Nested aggregates
            cout << "Nested count: " << static_cast<int32_t>(_aggList.size()) << endl;
            for (int32_t i = 0; i < static_cast<int32_t>(_aggList.size()); i++)
            {
               AbstractAggregate *agg = _aggList[i];
               const int32_t fieldIdNested = agg->FieldIdAsNested();
               const std::string &fieldName = MetaData().fieldInfo[fieldIdNested].FieldName();
               // Now put into JSON
               writer.Key( fieldName.c_str());
               static_cast<BaseAggregate*>(agg)->serialize( writer );
            }

            writer.EndObject();
         }

         // Deserialize-related stuff -----------------------------:
         static string deserializeLastKeyName;

         AbstractAggregate * BaseAggregate::findLastKeyAggregate() const
         {
            for (int32_t i = 0; i < static_cast<int32_t>(_aggList.size()); i++)
            {
               AbstractAggregate *agg = _aggList[i];
               const int32_t fieldIdNested = agg->FieldIdAsNested();
               const std::string &fieldName = MetaData().fieldInfo[fieldIdNested].FieldName();
               if (deserializeLastKeyName == fieldName)
               {
                  return agg;
               }
            }
            return NULL;
         }

         AbstractField * BaseAggregate::findLastKeyField() const
         {
            for (int32_t i = 0; i < static_cast<int32_t>(_fieldList.size()); i++)
            {
               AbstractField *fld = _fieldList[i];
               const int32_t fieldId = fld->FieldId();
               const std::string &fieldName = MetaData().fieldInfo[fieldId].FieldName();
               if ( deserializeLastKeyName == fieldName )
               {
                  return fld;
               }
            }
            return NULL;
         }

         bool BaseAggregate::DeserializeEventHandler::Key(const char* str, SizeType length, bool copy)
         {
            deserializeLastKeyName = str;
            cout << "--- Key(" << deserializeLastKeyName << ", " << length << ", " << boolalpha << copy << ")" << endl;
            return true;
         }

         bool BaseAggregate::DeserializeEventHandler::StartObject()
         {
            cout << ">>> StartObject()" << endl;
            const BaseAggregate * currentAggregate = getCurrentAggregate();
            if (currentAggregate) {
               BaseAggregate * agg = dynamic_cast<BaseAggregate*>(currentAggregate->findLastKeyAggregate() );
               if (agg)
               {
                  setCurrentAggregate( agg );
               }
               else
               {
                  // [PL] TODO: error handling.
               }
            }

            return true;
         }

         bool BaseAggregate::DeserializeEventHandler::EndObject(SizeType memberCount)
         {
            cout << "EndObject(" << memberCount << ")" << endl;
            setCurrentAggregateToParent();
            return true;
         }

         // [PL] setFieldReinterpretType() is a global function b/c when I tried making it a BaseAggregate::DeserializeEventHandler
         // member I was getting circular dependency errors (BaseAggregate<->BaseField) when compiling for VxWorks.
         template <typename T>
         void setFieldReinterpretType(BaseField<T> * fld, T theValue)
         {
            const string fldTypeName = typeid(*fld).name();
            cout << "fldTypeName: " << fldTypeName;
            const FieldStateEnum::FieldState fldState = fld->State();
            if (fldState != FieldStateEnum::Constant && fldState != FieldStateEnum::Unavailable) {
               fld->Value(theValue);
               cout << "\ttheValue: " << theValue;
            }
            else
            {
               cout << "\tfield State: " << fldState;
            }
            cout << endl;
         }

         template <typename ScalarType>
         void BaseAggregate::DeserializeEventHandler::setField( ScalarType theValue )
         {
            const type_info & theValueType = typeid(theValue);
            const string theValueTypeName = theValueType.name();
            cout << "ScalarType: " << theValueTypeName << endl;
            BaseAggregate * currentAggregate = getCurrentAggregate();
            if (currentAggregate) {
               AbstractField * fldAbs = currentAggregate->findLastKeyField();
               BaseField<ScalarType> * fld = dynamic_cast<BaseField<ScalarType>*>( fldAbs );
               if (fld)
               {
                  setFieldReinterpretType(fld, theValue);
               }
               else
               {
                  // The actual field type could be EnumField<U,X>, U being int32_t, uint32_t, int64_t, uint64_t.
                  //   If (rapidjson-detected) ScalarType is uint32_t, U could actually be any of the above four types.
                  //   If ScalarType is  int32_t - U could be  int32_t or  int64_t
                  //   If ScalarType is uint64_t - U could be uint32_t or uint64_t
                  //   If ScalarType is  int64_t - U can only be int64_t
                  BaseField<int32_t> * fld_int32 = dynamic_cast<BaseField<int32_t>*>(fldAbs);
                  if (fld_int32)
                  {
                     int32_t i(theValue);
                     setFieldReinterpretType(fld_int32, i );
                  }
                  else {
                     BaseField<uint32_t> * fld_uint32 = dynamic_cast<BaseField<uint32_t>*>(fldAbs);
                     if (fld_uint32)
                     {
                        setFieldReinterpretType(fld_uint32, static_cast<uint32_t>(theValue));
                     }
                     else {
                        BaseField<int64_t> * fld_int64 = dynamic_cast<BaseField<int64_t>*>(fldAbs);
                        if (fld_int64)
                        {
                           setFieldReinterpretType(fld_int64, static_cast<int64_t>(theValue));
                        }
                        else {
                           BaseField<uint64_t> * fld_uint64 = dynamic_cast<BaseField<uint64_t>*>(fldAbs);
                           if (fld_uint64)
                           {
                              setFieldReinterpretType(fld_uint64, static_cast<uint64_t>(theValue));
                           }
                           else {
                              // [PL] TODO: error handling.
                           }
                        }
                     }
                  }
               }//else (! fld) 
            }//if (currentAggregate) 
         }//BaseAggregate::DeserializeEventHandler::setField()

         void BaseAggregate::DeserializeEventHandler::setCurrentAggregate(BaseAggregate * ag = NULL)
         {
            if (ag)
            {
               _currentAggregate.push_back(ag);
            }
            else
            {
               // [PL] TODO error handling?
            }
         }

         void BaseAggregate::DeserializeEventHandler::setCurrentAggregateToParent(void)
         {
            if (_currentAggregate.empty())
            {
               // [PL] TODO: error handling.
            }
            else
            {
               _currentAggregate.pop_back();
            }
         }

         BaseAggregate * BaseAggregate::DeserializeEventHandler::getCurrentAggregate(void)
         {
            return _currentAggregate.empty() ? NULL: _currentAggregate.back();
         }

         bool BaseAggregate::DeserializeEventHandler::Bool(bool b) {
            cout << "Bool(" << boolalpha << b << ")" << endl;
            setField( b );
            return true;
         }

         bool BaseAggregate::DeserializeEventHandler::Int(int i) {
            cout << "Int(" << i << ")" << endl;
            setField(i);
            return true;
         }

         bool BaseAggregate::DeserializeEventHandler::Uint(unsigned u){
            cout << "Uint(" << u << ")" << endl;
            setField(u);
            return true;
         }

         bool BaseAggregate::DeserializeEventHandler::Int64(int64_t i) {
            cout << "Int64(" << i << ")" << endl;
            setField(i);
            return true;
         }

         bool BaseAggregate::DeserializeEventHandler::Uint64(uint64_t u) {
            cout << "Uint64(" << u << ")" << endl;
            setField(u);
            return true;
         }

         bool BaseAggregate::DeserializeEventHandler::Double(double d) {
            cout << "Double(" << d << ")" << endl;
            setField(d);
            return true;
         }

         bool BaseAggregate::DeserializeEventHandler::String(const char* str, SizeType length, bool copy) {
            cout << "String(" << str << ", " << length << ", " << boolalpha << copy << ")" << endl;
            //setField( string(str) );
            const BaseAggregate * currentAggregate = getCurrentAggregate();
            if (currentAggregate)
            {
               BaseField<string> * fld = dynamic_cast<BaseField<string>*>(currentAggregate->findLastKeyField());
               if (fld)
               {
                  const FieldStateEnum::FieldState fldState = fld->State();
                  if (fldState != FieldStateEnum::Constant && fldState != FieldStateEnum::Unavailable) {
                     fld->Value(str);
                     cout << "str: " << str << endl;
                  }
               }
            }
            return true;
         }

         void BaseAggregate::deserialize(const std::string & value)
         {
            DeserializeEventHandler handler( this );
            cout << __FUNCTION__ << "() value: " << value << endl;
            Reader reader;
            StringStream ss( value.c_str() );
            reader.Parse(ss, handler);

            return;

            /****
            //TODO - User Story 129259
            // Change valueInternal() to use an enum {Set, Deserialize, Compute} instead of just bool.
            // Add serializeValue/deserializeValue() to AbstractField similar to computedValueString(). Implement as appropriate.
            // Ensure computedValueString() uses serialializeValue/deserializeValue as appropriate.

            // for each fieldNameIn/fieldValueIn from JSON, do the following loop
            std::string fieldNameIn = "field1-for-example";
            std::string fieldValueIn = "avalue-for-example";
            for (int32_t i = 0; i < static_cast<int32_t>(_fieldList.size()); i++)
            {
               const AbstractField *fld = _fieldList[i];
               const int32_t fieldId = fld->FieldId();
               const std::string &fieldName = MetaData().fieldInfo[fieldId].FieldName();
               if (fieldName == fieldNameIn)
               {
                  //fld->deserializeValue(fieldValueIn);
               }
            }
            // for each nested aggregate from JSON, do the following loop
            std::string aggNameIn = "agg-name";
            std::string aggValueIn = "agg-json";
            for (int32_t i = 0; i < static_cast<int32_t>(_aggList.size()); i++)
            {
               AbstractAggregate *agg = _aggList[i];
               const int32_t fieldIdNested = agg->FieldIdAsNested();
               const std::string &fieldName = MetaData().fieldInfo[fieldIdNested].FieldName();
               if (aggNameIn == fieldName)
               {
                  //agg->deserialize(aggValueIn);
               }          
            }
            ****/
         }

         void BaseAggregate::log(std::ostream & logStream, int flags) const
         {
            //TODO - User Story 129791
         }

      }
   }
}
