#pragma once

#include <vector>
#include <map>

#include "AbstractAggregate.h"
#include "AbstractField.h"
#include "AggregateMetaData.h"
#include "AssessmentResult.h"

#include "rapidjson/prettywriter.h"
#include "rapidjson/stringbuffer.h"
#include <iostream>  // [PL] just for testing

using namespace rapidjson;
using namespace std;

namespace Bct
{
   namespace Workflow
   {
      namespace Aggregates
      {
         /// <summary>
         /// Base aggregate that derives from the AbstractAggregate class. All aggregates must derive from this base class.
         /// </summary>
         class BaseAggregate : public AbstractAggregate
         {
         public:
            /// <summary>
            /// Specifies to use the most recent version.
            /// </summary>
            static const std::string UseMostRecentVersionStr;

            /// <summary>
            /// Used as a requested version to indicate the metadata item should be included in all versions of the parent.
            /// 
            /// Example:  FieldMeta intField1Meta("intField1", FieldStateEnum::Default, "1", BaseAggregate::InAllVersions);
            /// </summary>
            static const int16_t InAllVersions = -1;

            /// <summary>
            /// Constructs base aggregate.
            /// </summary>
            /// <param name="version">The version to be constucted, such as 1.2.3</param>
            BaseAggregate(const std::string &version);

            /// <summary>
            /// Constructor. This constucts the most recent version.
            /// </summary>
            BaseAggregate();

            /// <summary>
            /// Constructor. This constructor is used for nested aggregates.
            /// </summary>
            /// <param name="fieldIdAsNested">The field id of this nested aggregate.</param>
            /// <param name="parentAsNested">The parent of this nesteded aggregate</param>
            BaseAggregate(int32_t fieldIdAsNested, BaseAggregate * const parentAsNested);

            /// <summary>
            /// Copy constructor.
            /// </summary>
            /// <param name="other">Object to be copied.</param>
            BaseAggregate(const BaseAggregate & other);

            /// <summary>
            /// Constructor for copying a nested aggregate but not a copy constructor.
            /// </summary>
            /// <param name="other">Object to copy.</param>
            /// <param name="parent">Parent aggregate.</param>
            BaseAggregate(const BaseAggregate &other, BaseAggregate * const parent);

            BaseAggregate & operator=(const BaseAggregate & other);

            /// <summary>
            /// Virtual destructor.
            /// </summary>
            virtual ~BaseAggregate();

            /// <summary>
            /// Get current version of aggregate.
            /// </summary>
            /// <returns>Aggregate version.</returns>
            const std::string& getVersion() const;

            /// <summary>
            /// Updates all calculated fields for this aggregate.
            /// </summary>
            void updateCalculatedFields();

            /// <summary>
            /// Run one or all assessment rules.
            /// </summary>
            /// <param name="id">The id of the assessment rule to run or * to run all assessment rules</param>
            /// <returns>The result of the assessment.</returns>
            AssessmentResult Assess() const;
            
            /// <summary>
            /// Converts current version to the specified version.
            /// </summary>
            /// <param name="version">The new version</param>
            void convertToVersion(const std::string toVersion);

            void serialize( PrettyWriter<StringBuffer> * writer ) const;
            void deserialize(const std::string & value);
            void log(std::ostream & logStream, int flags) const;

            /// <summary>
            /// Increments the global field set counter and returns the result. Field setters can call this to get their
            /// latest counter.
            /// </summary>
            /// <returns>The incremented field set counter.</returns>
            virtual const uint32_t &fieldSetCounter();

         protected:
            /// <summary>
            /// Sets the current version as appropriate.
            /// 
            /// If default constructor is used, indicating the most recent version is desired, _ver and _version are set to the most recent metadata version. Otherwise _version is used to set _ver.
            /// This function does nothing if there is a parent aggregate and the system defers to after root parent version is known.
            /// </summary>
            void syncVersion();

            /// <summary>
            /// Sets the current version of a nested child aggregate based on this parent's current version and metadata.
            /// 
            /// This function should be called after this aggregate has a version, which should be after syncVersion() is called. Each child aggregate should be intialized with this function.
            /// </summary>
            /// <param name="parentVer"></param>
            virtual void syncChildVersion(int16_t parentVer);

            /// <summary>
            /// Pure virtual function that returns the field meta data id for this nested aggregate.
            /// 
            /// This value is the index into the _aggList vector.
            /// </summary>
            /// <returns>FieldMeta id for this nested aggregate.</returns>
            virtual int32_t &FieldIdAsNested();

            /// <summary>
            /// Returns the list of fields in this aggregate.
            /// </summary>
            /// <returns>Field list.</returns>
            std::vector<AbstractField*> & FieldList();

            /// <summary>
            /// Returns the list of nested aggregates in the aggregate;
            /// </summary>
            /// <returns>Aggregate list.</returns>
            std::vector<AbstractAggregate*> & AggList();

            /// <summary>
            /// Returns the current version index for this aggregate.
            /// </summary>
            /// <returns>Current version index.</returns>
            int32_t Ver() const;

            /// <summary>
            /// Returns the current version string for this aggregate.
            /// </summary>
            /// <returns>Current verson string.</returns>
            const std::string & Version() const;

            AbstractAggregate * findLastKeyAggregate() const;
            AbstractField     * findLastKeyField() const;

         private:

            std::vector<AbstractField*> _fieldList;
            std::vector<AbstractAggregate*> _aggList;
            int16_t _ver;
            std::string _version;
            uint32_t _fieldSetCounter;
            BaseAggregate * const _parent;
            std::string _fieldNameAsNested;
            int32_t _fieldIdAsNested;

            FieldMeta &findFieldMeta(int16_t parentVer);

            // Use as a requested version to indicate the most recent version is requested.
            static const int16_t UseMostRecentVersion = -1;

            struct DeserializeEventHandler // Required by the RapidJSON SAX parser.
            {
               bool Null();
               bool Bool(bool b);
               bool Int(int i);
               bool Uint(unsigned u);
               bool Int64(int64_t i);
               bool Uint64(uint64_t u);
               bool Double(double d);
               bool RawNumber(const char* str, SizeType length, bool copy) {
                   cout << "Number(" << str << ", " << length << ", " << boolalpha << copy << ")" << endl;
                   return true;
               }

               bool String(const char* str, SizeType length, bool copy);
               bool Key(const char* str, SizeType length, bool copy);
               bool StartObject();
               bool EndObject(SizeType memberCount);
               bool StartArray();
               bool EndArray(SizeType elementCount);

               DeserializeEventHandler(BaseAggregate * ag) { setCurrentAggregate(ag); };
               DeserializeEventHandler() {};

            private:
               template<typename T> void setFieldOrVectorElement(const T * value);
               void setCurrentAggregate(BaseAggregate * ag);
               void setCurrentAggregateToParent(void);
               BaseAggregate * getCurrentAggregate(void);

               // _currentAggregate keeps track of the current nested aggregate being parsed.
               // _currentAggregate[0] is the top-level/outermost aggregate
               // _currentAggregate[1] is the "level-1" nested aggregate.
               // _currentAggregate[2] is the "level-2" nested aggregate, and so on. Once it has been parsed, the EndObject()
               //   event handler removes it from the vector, and its parent, _currentAggregate[1], becomes the current aggregate.
               vector<BaseAggregate *> _currentAggregate;
               AbstractField *         _deserializeCurrentVector; // The vector being deserialized.
            };

         };
      }
   }
}
