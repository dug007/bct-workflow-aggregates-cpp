#include "BaseAggregate.h"

#include <stdint.h>
#include <sstream>

#include "FieldStateEnum.h"
#include "RPNEvaluator.h"
#include "AssessmentRule.h"
#include "AssessmentResult.h"
#include "Exceptions.h"
#include "FieldInfo.h"

#include "BaseField.h"
#include "StringField.h"
#include "VectorField.h"
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
                  if (fm.fieldId() == _fieldIdAsNested)
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
                  if (fm.fieldId() == _fieldIdAsNested && fm._parentVer <= parentVer)
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
               if (f->state() == FieldStateEnum::NotSet)
               {
                  strVal = "$Notset"; // TODO make sure this is correct - User Story 129259
               }
               else if (f->state() == FieldStateEnum::Unavailable)
               {
                  strVal = "$Unavailable"; // TODO make sure this is correct - User Story 129259
               }
               else
               {
                  strVal = f->computedValueString();
               }

               FieldStateEnum::FieldState &state = f->stateRef();
               std::string const &fieldName = MetaData().fieldInfo[f->fieldId()].fieldName();
               varMap[fieldName] = RPNEvaluator::RPNVariable(fieldName, f->type(), strVal, state, f->fieldSetCounter());
            }


            std::vector<int16_t> &cRulesV = MetaData().versionMetaData[Ver()].computeRulesI;
            for (size_t iRule = 0; iRule < cRulesV.size(); iRule++) // over rules in current version
            {
               ComputeRule &cRule = MetaData().computeRules[cRulesV[iRule]]; // indirection
               for (size_t iField = 0; iField < _fieldList.size(); iField++) // over fields
               {
                  // find field calcuation in current version
                  AbstractField *f = _fieldList[iField];
                  const FieldStateEnum::FieldState &state = f->state();
                  const TypeEnum::Type &type = f->type();
                  if (f->fieldId() == cRule.fieldId())
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
                        f->computedValueString(answerValue);
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
               if (f->state() == FieldStateEnum::NotSet)
               {
                  strVal = "$Notset"; // TODO make sure this is correct - User Story 129259
               }
               else if (f->state() == FieldStateEnum::Unavailable)
               {
                  strVal = "$Unavailable"; // TODO make sure this is correct - User Story 129259
               }
               else
               {
                  strVal = f->computedValueString();
               }

               FieldStateEnum::FieldState &state = f->stateRef();
               std::string const &fieldName = MetaData().fieldInfo[f->fieldId()].fieldName();
               varMap[fieldName] = RPNEvaluator::RPNVariable(fieldName, f->type(), strVal, state, f->fieldSetCounter());
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
            // TODO implement - User Story 129296

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
               if (f->state() == FieldStateEnum::NotSet)
               {
                  strVal = "$Notset"; // TODO make sure this is correct - User Story 129259
               }
               else if (f->state() == FieldStateEnum::Unavailable)
               {
                  strVal = "$Unavailable"; // TODO make sure this is correct - User Story 129259
               }
               else
               {
                  strVal = f->computedValueString();
               }

               FieldStateEnum::FieldState &state = f->stateRef();
               std::string const &fieldName = MetaData().fieldInfo[f->fieldId()].fieldName();
               varMap[fieldName] = RPNEvaluator::RPNVariable(fieldName, f->type(), strVal, state, f->fieldSetCounter());
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
                  const FieldStateEnum::FieldState &state = f->state();
                  const TypeEnum::Type &type = f->type();
                  if (f->fieldId() == vcRule.fieldId() && toVersion == vcRule.ToVersion())
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
                        f->computedValueString(answerValue);
                     }
                  }
               }
            }
            _ver = toVersion;
            _version = MetaData().versionInfo[_ver].Version();
         };


         const uint32_t &BaseAggregate::fieldSetCounter()
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

// for debugging only #define COUT cout<<__LINE__<<endl;
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
               const int32_t fieldId = fld->fieldId();
               const std::string &fieldName = MetaData().fieldInfo[fieldId].fieldName();
               const TypeEnum::Type &type = fld->type();
               // now put into JSON
               writer.Key(fieldName.c_str());
               //cout << "fieldName: " << fieldName.c_str() << ";   type: " << type << endl;
               try
               {
                  switch( type )
                  {
                     case TypeEnum::BoolType:
                        writer.Bool( (static_cast<const BaseField<bool>*>(fld))->value() );
                        break;
                     case TypeEnum::Int32Type:
                        writer.Int( (static_cast<const BaseField<int32_t>*>(fld))->value() );
                        break;
                     case TypeEnum::UInt32Type:
                        writer.Uint( (static_cast<const BaseField<uint32_t>*>(fld))->value() );
                        break;
                     case TypeEnum::Int64Type:
                        writer.Int64( (static_cast<const BaseField<int64_t>*>(fld))->value() );
                        break;
                     case TypeEnum::UInt64Type:
                        writer.Uint64( (static_cast<const BaseField<uint64_t>*>(fld))->value() );
                        break;
                     case TypeEnum::DoubleType:
                        writer.Double( (static_cast<const BaseField<double>*>(fld))->value() );
                        break;
                     case TypeEnum::StringType:
                        {
                           const std::string tmpStringValue = (std::string)( *(static_cast<const StringField*>(fld)) );
                           writer.String( tmpStringValue.c_str() );
                        }
                        break;
                     case TypeEnum::ArrayType:// TODO: story 149108
                        // writer.String( "<TODO: ArrayType>");
                        {
                           const vector<int32_t> & theVector = (static_cast<const VectorField<int32_t>*>(fld))->value();
                           cout << "VectorField.size(): " << theVector.size() << endl;
                           for (vector<int32_t>::const_iterator iter = theVector.begin(); iter != theVector.end(); ++iter)
                           {

                           }
                           writer.StartArray();
                           writer.EndArray();
                        }
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
               const std::string &fieldName = MetaData().fieldInfo[fieldIdNested].fieldName();
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
            for (vector<AbstractAggregate*>::const_iterator iter = _aggList.begin(); iter != _aggList.end(); ++iter)
            {
               AbstractAggregate *agg = *iter;
               const int32_t fieldIdNested = agg->FieldIdAsNested();
               const std::string &fieldName = MetaData().fieldInfo[fieldIdNested].fieldName();
               if (deserializeLastKeyName == fieldName)
               {
                  return agg;
               }
            }
            return NULL;
         }

         AbstractField * BaseAggregate::findLastKeyField() const
         {
            for (vector<AbstractField*>::const_iterator iter = _fieldList.begin(); iter != _fieldList.end(); ++iter)
            {
               AbstractField *fld = *iter;
               const int32_t fieldId = fld->fieldId();
               const std::string &fieldName = MetaData().fieldInfo[fieldId].fieldName();
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
                  // TODO: story 149109
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
				if( NULL == fld )
				{	// [PL] TODO: error handling?
					return;
				}
				
            const string fldTypeName = typeid(*fld).name();
            cout << "setFieldReinterpretType() fldTypeName: " << fldTypeName;
            const FieldStateEnum::FieldState fldState = fld->state();
            if (fldState != FieldStateEnum::Constant && fldState != FieldStateEnum::Unavailable) {
               fld->value(theValue);
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
            if (currentAggregate)
            {
               AbstractField * fldAbs = currentAggregate->findLastKeyField();
               if (fldAbs)
               {
                  const TypeEnum::Type fldType = fldAbs->type();
                  cout << "fldType: " << fldType << endl;
                  switch (fldType)
                  {
                  case TypeEnum::BoolType:
                     setFieldReinterpretType(dynamic_cast<BaseField<bool>*>(fldAbs), static_cast<bool>(theValue));
                     break;
                  case TypeEnum::Int32Type:
                     setFieldReinterpretType(dynamic_cast<BaseField<int32_t>*>(fldAbs), static_cast<int32_t>(theValue));
                     break;
                  case TypeEnum::UInt32Type:
                     setFieldReinterpretType(dynamic_cast<BaseField<uint32_t>*>(fldAbs), static_cast<uint32_t>(theValue));
                     break;
                  case TypeEnum::Int64Type:
                     setFieldReinterpretType(dynamic_cast<BaseField<int64_t>*>(fldAbs), static_cast<int64_t>(theValue));
                     break;
                  case TypeEnum::UInt64Type:
                     setFieldReinterpretType(dynamic_cast<BaseField<uint64_t>*>(fldAbs), static_cast<uint64_t>(theValue));
                     break;
                  case TypeEnum::DoubleType:
                     setFieldReinterpretType(dynamic_cast<BaseField<double>*>(fldAbs), static_cast<double>(theValue));
                     break;
                  default: // [PL] TODO: error handling?
                     break;
                  }
               }//if (fldAbs)
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
               // TODO: story 149109
            }
         }

         void BaseAggregate::DeserializeEventHandler::setCurrentAggregateToParent(void)
         {
            if (_currentAggregate.empty())
            {
               // TODO: story 149109
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
            const BaseAggregate * currentAggregate = getCurrentAggregate();
            if (currentAggregate)
            {
               BaseField<string> * fld = dynamic_cast<BaseField<string>*>(currentAggregate->findLastKeyField());
               if (fld)
               {
                  const FieldStateEnum::FieldState fldState = fld->state();
                  if (fldState != FieldStateEnum::Constant && fldState != FieldStateEnum::Unavailable) {
                     fld->value(str);
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
         }

         void BaseAggregate::log(std::ostream & logStream, int flags) const
         {
            //TODO - User Story 129791
         }

      }
   }
}
