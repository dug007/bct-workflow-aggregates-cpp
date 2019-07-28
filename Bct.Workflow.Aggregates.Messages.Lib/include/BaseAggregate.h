#pragma once

#include <vector>
#include <map>

#include "AbstractAggregate.h"
#include "AbstractField.h"
#include "AggregateMetaData.h"
#include "AssessmentResult.h"


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
            /// <param name="fieldName"></param>
            /// <param name="parent"></param>
            BaseAggregate(const std::string &fieldName, BaseAggregate * parent);

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
            /// <param name="version">The new current version</param>
            void convertVersion(std::string version)
            {
               // TODO implement - User Story 126595
            };

            void serialize(std::string & value) const;
            void deserialize(const std::string & value);
            void log(std::ostream & logStream, int flags) const;

            /// <summary>
            /// Increments the global field set counter and returns the result. Field setters can call this to get their
            /// latest counter.
            /// </summary>
            /// <returns>The incremented field set counter.</returns>
            virtual const uint32_t &FieldSetCounter();

            // TODO: determine best way to define - User Story 126907
            // Field types
            //typedef int32_t_ Int32Type_;
            //typedef int64_t_ Int64Type;
            //typedef uint32_t_ UInt32Type;
            //typedef uint64_t_ UInt64Type;
            //typedef double_ DoubleType;
            //typedef std::string_ StringType;
            //typedef bool_ BoolType;

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

         private:
            std::vector<AbstractField*> _fieldList;
            std::vector<AbstractAggregate*> _aggList;
            int16_t _ver;
            std::string _version;
            uint32_t _fieldSetCounter;
            BaseAggregate * _parent;
            std::string _fieldNameAsNested;

            FieldMeta &findFieldMeta(int16_t parentVer);

            // Use as a requested version to indicate the most recent version is requested.
            static const int16_t UseMostRecentVersion = -1;
         };
      }
   }
}