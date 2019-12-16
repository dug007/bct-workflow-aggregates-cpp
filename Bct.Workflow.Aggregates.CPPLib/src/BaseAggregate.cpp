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
#include "AggregateNotFound.h"
#include "CannotConvertScalar.h"
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

         //
         // Serialization stuff below:
         //***************************************************************************

         // for debugging only #define COUT cout<<__LINE__<<endl;
         void BaseAggregate::serialize( PrettyWriter<StringBuffer> * writer ) const
         {
            //TODO - User Story 129258
            // Elsewhere, ensure computedValueString() uses serialializeValue/deserializeValue as appropriate.
            // See deserialize below.
            writer->StartObject();
            // Fields
            for (int32_t i = 0; i < static_cast<int32_t>(_fieldList.size()); i++)
            {
               const AbstractField *fld = _fieldList[i];
               //const std::string &val = fld->serializeValue();
               const int32_t fieldId = fld->fieldId();
               const std::string &fieldName = MetaData().fieldInfo[fieldId].fieldName();
               const TypeEnum::Type &type = fld->type();

               // [PL] temp
               //if (TypeEnum::ArrayType == type) continue;

               // now put into JSON
               writer->Key(fieldName.c_str());
               cout << "fieldName: " << fieldName.c_str() << ";   type: " << type << endl;
               try
               {
                  fld->serialize(writer);
               }
               catch(NotAbleToGet & exNotAbleToGet)
               {
                  cerr << "NotAbleToGet exception: " << exNotAbleToGet.what() << endl;
                  writer->Null();
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
               writer->Key( fieldName.c_str());
               cout << "fieldName: " << fieldName.c_str() << endl;
               try
               {
                  static_cast<BaseAggregate*>(agg)->serialize(writer);
               }//try
               catch (...)
               {
                  cerr << "Exception................ " << endl;
                  writer->Null();
               }
            }//for(_aggList)

            writer->EndObject();
         }

         //
         // Deserialization stuff below:
         //***************************************************************************
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
            for (vector<AbstractField*>::const_iterator itr = _fieldList.begin(); itr != _fieldList.end(); ++itr)
            {
               AbstractField *fld = *itr;
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
            _deserializeCurrentVector = NULL;

            cout << ">>> StartObject()" << endl;
            const BaseAggregate * currentAggregate = getCurrentAggregate();
            if (currentAggregate) {
               BaseAggregate * agg = dynamic_cast<BaseAggregate*>(currentAggregate->findLastKeyAggregate() );
               if (agg)
               {
                  setCurrentAggregate(agg);
               }
               else
               {
                  if (deserializeLastKeyName == "")
                  {
                     return true;
                  }
                  else
                  {
                     std::string tempAggName = typeid(*this).name();
                     throw AggregateNotFound(tempAggName);
                  }
               }
            }
            return true;
         }

         bool BaseAggregate::DeserializeEventHandler::EndObject(SizeType memberCount)
         {
            cout << "EndObject(" << memberCount << ")" << endl;
            setCurrentAggregateToParent();
            deserializeLastKeyName = "";
            return true;
         }

         bool BaseAggregate::DeserializeEventHandler::StartArray()
         {
            cout << "StartArray()" << endl;
            BaseAggregate * currentAggregate = getCurrentAggregate();
            if (currentAggregate)
            {
               AbstractField * fldAbs = currentAggregate->findLastKeyField();
               if (fldAbs)
               {
                  _deserializeCurrentVector = fldAbs;
                  cout << "================  StartArray(): subtype: " << fldAbs->subtype() << endl;
               }
            }
            //--------------------------------
            return true;
         }

         bool BaseAggregate::DeserializeEventHandler::EndArray(SizeType elementCount)
         {
            _deserializeCurrentVector = NULL;

            cout << "EndArray(" << elementCount << ")" << endl;
            return true;
         }

         void BaseAggregate::DeserializeEventHandler::setCurrentAggregate(BaseAggregate * ag = NULL)
         {
            if (ag)
            {
               _currentAggregate.push_back(ag);
            }
            else
            {
               std::string tempAggName = typeid(*this).name();
               throw AggregateNotFound(tempAggName);
            }
         }

         void BaseAggregate::DeserializeEventHandler::setCurrentAggregateToParent(void)
         {
            if (_currentAggregate.empty())
            {
               std::string tempAggName = typeid(*this).name();
               throw AggregateNotFound(tempAggName);
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

         bool BaseAggregate::DeserializeEventHandler::Null()
         {
            BaseAggregate * currentAggregate = getCurrentAggregate();
            if (currentAggregate)
            {
               AbstractField *fldAbs = currentAggregate->findLastKeyField();
               if (fldAbs && fldAbs->state() != FieldStateEnum::Unavailable)
               {
                  fldAbs->stateRef() = FieldStateEnum::NotSet;
               }
            }
            cout << "Null()" << endl;
            return true;
         }

         template <typename T>
         void BaseAggregate::DeserializeEventHandler::vectorPushBack(const T * element)
         {
            const TypeEnum::Type subtype = _deserializeCurrentVector->subtype();
            switch (subtype)
            {
            case TypeEnum::BoolType:
            {
               VectorField<bool> * pVector = dynamic_cast<VectorField<bool> *>(_deserializeCurrentVector);
               if (pVector)
               {
                  pVector->pushBack(reinterpret_cast<const bool *>(element) );
               }
            }
            break;
            case TypeEnum::Int32Type:
            {
               VectorField<int32_t> * pVector = dynamic_cast<VectorField<int32_t> *>(_deserializeCurrentVector);
               if (pVector)
               {
                  pVector->pushBack(reinterpret_cast<const int32_t *>(element));
               }
            }
            break;
            case TypeEnum::UInt32Type:
            {
               VectorField<uint32_t> * pVector = dynamic_cast<VectorField<uint32_t> *>(_deserializeCurrentVector);
               if (pVector)
               {
                  pVector->pushBack(reinterpret_cast<const uint32_t *>(element));
               }
            }
            break;
            case TypeEnum::Int64Type:
            {
               VectorField<int64_t> * pVector = dynamic_cast<VectorField<int64_t> *>(_deserializeCurrentVector);
               if (pVector)
               {
                  pVector->pushBack(reinterpret_cast<const int64_t *>(element));
               }
            }
            break;
            case TypeEnum::UInt64Type:
            {
               VectorField<uint64_t> * pVector = dynamic_cast<VectorField<uint64_t> *>(_deserializeCurrentVector);
               if (pVector)
               {
                  pVector->pushBack(reinterpret_cast<const uint64_t *>(element));
               }
            }
            break;
            case TypeEnum::DoubleType:
            {
               VectorField<double> * pVector = dynamic_cast<VectorField<double> *>(_deserializeCurrentVector);
               if (pVector)
               {
                  pVector->pushBack(reinterpret_cast<const double *>(element));
               }
            }
            break;
            case TypeEnum::StringType:
            {
               VectorField<std::string> * pVector = dynamic_cast<VectorField<std::string> *>(_deserializeCurrentVector);
               if (pVector)
               {
                  pVector->pushBack(reinterpret_cast<const std::string *>(element));
               }
            }
            break;

            default:
               break;
            }
         }

         // [PL] setField() is a global function b/c when I tried making it a BaseAggregate::DeserializeEventHandler
         // member I was getting circular dependency errors (BaseAggregate<->BaseField) when compiling for VxWorks.
         template <typename TFieldType, typename TValue>
         static void setField(TFieldType * fld, const TValue & theValue)
         {
            if( NULL == fld )
            {	// [PL] TODO: error handling?
               // [PL] Need this NULL-check b/c the upstream code calls dynamic_cast which can return NULL;
               cout << "!!!!!!!!!!!! ERROR in setField(): fld is NULL." << endl;
               return;
            }

            const string fldTypeName = typeid(*fld).name();
            cout << "setField() fldTypeName: " << fldTypeName;
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

         template<typename T>
         void BaseAggregate::DeserializeEventHandler::setFieldOrVectorElement(const T * value)
         {
            const type_info & valueTypeId = typeid(*value);
            const string valueTypeName = valueTypeId.name();
            cout << "setFieldOrVectorElement(): T (scalar type): " << valueTypeName << endl;

            TypeEnum::Type valueType(TypeEnum::EmptyType);
            if (_deserializeCurrentVector)
            {
               vectorPushBack(value);
            }
            else
            {
               BaseAggregate * currentAggregate = getCurrentAggregate();
               if (currentAggregate)
               {
                  AbstractField * fldAbs = currentAggregate->findLastKeyField();
                  if (fldAbs)
                  {
                     const TypeEnum::Type fldType = fldAbs->type();
                     cout << "setField(): fldType: " << fldType << endl;
                     switch (fldType)
                     {
                     case TypeEnum::BoolType:
                     {
                        const bool valueBool = *value;
                        setField(dynamic_cast<BaseField<bool>*>(fldAbs), valueBool);
                        break;
                     }
                     case TypeEnum::Int32Type:
                     {
                        const int32_t valueInt32 = *value;
                        setField(dynamic_cast<BaseField<int32_t>*>(fldAbs), valueInt32);
                        break;
                     }
                     case TypeEnum::UInt32Type:
                     {
                        const uint32_t valueUint32 = *value;
                        setField(dynamic_cast<BaseField<uint32_t>*>(fldAbs), valueUint32);
                        break;
                     }
                     case TypeEnum::Int64Type:
                     {
                        const int64_t valueInt64 = *value;
                        setField(dynamic_cast<BaseField<int64_t>*>(fldAbs), valueInt64);
                        break;
                     }
                     case TypeEnum::UInt64Type:
                     {
                        const uint64_t valueUint64 = *value;
                        setField(dynamic_cast<BaseField<uint64_t>*>(fldAbs), valueUint64);
                        break;
                     }
                     case TypeEnum::DoubleType:
                     {
                        const double valueDouble = *value;
                        setField(dynamic_cast<BaseField<double>*>(fldAbs), valueDouble);
                        break;
                     }
                     case TypeEnum::StringType:
                     {
                        const std::string valueString( reinterpret_cast<const char *>(value));
                        setField(dynamic_cast<BaseField<std::string>*>(fldAbs), valueString);
                        break;
                     }
                     case TypeEnum::ArrayType: // [PL] Should never get here.
                        break;
                     default: // [PL] TODO: error handling?
                        break;
                     }
                  }
               }
            }
         }

         bool BaseAggregate::DeserializeEventHandler::Int(int i) {
            cout << "Int(" << i << ")" << endl;
            setFieldOrVectorElement(&i);
            return true;
         }

         bool BaseAggregate::DeserializeEventHandler::Uint(unsigned u){
            cout << "Uint(" << u << ")" << endl;
            setFieldOrVectorElement(&u);
            return true;
         }

         bool BaseAggregate::DeserializeEventHandler::Int64(int64_t i) {
            cout << "Int64(" << i << ")" << endl;
            setFieldOrVectorElement(&i);
            return true;
         }

         bool BaseAggregate::DeserializeEventHandler::Uint64(uint64_t u) {
            cout << "Uint64(" << u << ")" << endl;
            setFieldOrVectorElement(&u);
            return true;
         }

         bool BaseAggregate::DeserializeEventHandler::Double(double d) {
            cout << "Double(" << d << ")" << endl;
            setFieldOrVectorElement(&d);
            return true;
         }

         bool BaseAggregate::DeserializeEventHandler::Bool(bool b) {
            cout << "Bool(" << boolalpha << b << ")" << endl;
            setFieldOrVectorElement(&b);
            return true;
         }

         bool BaseAggregate::DeserializeEventHandler::String(const char* psz, SizeType length, bool copy) {
            cout << "String(" << psz << ", " << length << ", " << boolalpha << copy << ")" << endl;
            setFieldOrVectorElement(psz);
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
