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
         /// Base aggregate. All aggregates must derive from this base class.
         /// </summary>
         class BaseAggregate : public AbstractAggregate
         {
         public:
            /// <summary>
            /// Constructs base aggregate.
            /// </summary>
            /// <param name="version">The version to be constucted, such as 1.2.3</param>
            /// <param name="metaData">The aggregate metadata.</param>
            BaseAggregate(const std::string &version, AggregateMetaData * metaData);

            /// <summary>
            /// Constructor. This constucts the mose recent version.
            /// </summary>
            /// <param name="metaData">The aggregate metadata.</param>
            BaseAggregate(AggregateMetaData * metaData);

            BaseAggregate(const std::string &fieldName, AggregateMetaData * metaData, BaseAggregate * parent);

            virtual ~BaseAggregate();

            /// <summary>
            /// Get current version of aggregate.
            /// </summary>
            /// <returns>Aggregate version.</returns>
            const std::string& getVersion() const;

            /// <summary>
            /// Updates all calculated fields for this aggregate.
            /// </summary>
            void UpdateCalculatedFields();

            /// <summary>
            /// Run one or all assessment rules.
            /// </summary>
            /// <param name="id">The id of the assessment rule to run or * to run all assessment rules</param>
            /// <returns>The result of the assessment.</returns>
            AssessmentResult Assess();
            
            /// <summary>
            /// Convertes current version to the specified version.
            /// </summary>
            /// <param name="version">The new current version</param>
            void convertVersion(std::string version)
            {
               // TODO implement - User Story 126595
            };

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
            /// This function is used to set the current version. 
            /// 
            /// If _ver is -1, indicating the most recent version is desired, _ver and _version are set to the most recent metadata version. Otherwise _version is is used to set _ver.
            /// </summary>
            void SyncVersion();

            /// <summary>
            /// Sets the current version of a nested child aggregate based on this parent's current version and metadata.
            /// 
            /// This function should be called after this aggregate has a version, which should be after SyncVersion() is called. Each child aggregate should be intialized with this function.
            /// </summary>
            /// <param name="parentVer"></param>
            virtual void SyncChildVersion(int16_t parentVer);

            /// <summary>
            /// Returns the aggregate metatdata.
            /// </summary>
            /// <returns>Aggregate metadata</returns>
            AggregateMetaData & MetaData();

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
            AggregateMetaData & _aggregateMetaData;
            std::vector<AbstractField*> _fieldList;
            std::vector<AbstractAggregate*> _aggList;
            int16_t _ver;
            std::string _version;
            uint32_t _fieldSetCounter;
            BaseAggregate * _parent;
            std::string _fieldName;

            // Disallow default constructor
            //
            BaseAggregate();

            FieldMeta &findFieldMeta(int16_t parentVer);

         };
      }
   }
}