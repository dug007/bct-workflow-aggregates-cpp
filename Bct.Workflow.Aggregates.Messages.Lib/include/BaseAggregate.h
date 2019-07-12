#pragma once

#include <vector>
#include <map>

#include "AbstractAggregate.h"
#include "AbstractField.h"
#include "VersionMetaData.h"


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
            BaseAggregate(const std::string version);

            virtual ~BaseAggregate();

            /// <summary>
            /// Get current version of aggregate.
            /// </summary>
            /// <returns>Aggregate version.</returns>
            const std::string& getVersion();

            /// <summary>
            /// Updates all calculated fields for this aggregate.
            /// </summary>
            void UpdateCalculatedFields();

            /// <summary>
            /// Sets the internal current version to the version as constructed.
            /// 
            /// The aggregate constructor can be called before metadata is initialized. This function is used to set the internal version to
            /// point to the metadata version as requested by the constructor. This function should be called after metadata is initialized.
            /// </summary>
            void SyncCurrentVersion();

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
            uint32_t FieldSetCounter();

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
            /// Returns the aggregate metatdata.
            /// </summary>
            /// <returns>Aggregate metadata</returns>
            std::vector<VersionMetaData> & AggregateMetaData();
            /// <summary>
            /// Returns the list of fields in this aggregate.
            /// </summary>
            /// <returns>Field list.</returns>
            std::vector<AbstractField*> & FieldList();
            /// <summary>
            /// Returns the current version index for this aggregate.
            /// </summary>
            /// <returns>Current version index.</returns>
            int32_t Ver();
            /// <summary>
            /// Returns the current version string for this aggregate.
            /// </summary>
            /// <returns>Current verson string.</returns>
            const std::string & Version();

         private:
            std::vector<VersionMetaData> _aggregateMetaData;
            std::vector<AbstractField*> _fieldList;
            int32_t _ver;
            std::string _version;
            uint32_t _fieldSetCounter;

            // Disallow default constructor
            //
            BaseAggregate();


         };
      }
   }
}