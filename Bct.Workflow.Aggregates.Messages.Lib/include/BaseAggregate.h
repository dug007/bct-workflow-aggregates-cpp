#pragma once

#include <vector>
#include <map>
#include <stdint.h>
#include <sstream>

#include "AbstractAggregate.h"


#include "FieldStateEnum.h"
#include "TypeEnum.h"
#include "BaseAggregate.h"
#include "AssessmentRule.h"
#include "VersionMetaData.h"
#include "VersionChangeRule.h"
#include "ComputeRule.h"
#include "FieldMeta.h"
#include "AbstractField.h"


namespace Bct
{
   namespace Workflow
   {
      namespace Aggregates
      {
         class BaseAggregate : public AbstractAggregate
         {
         public:
            /// <summary>
            /// Constructs base aggregate.
            /// </summary>
            /// <param name="version">The version to be constucted, such as 1.2.3</param>
            BaseAggregate(const std::string version);

            virtual ~BaseAggregate();

         private:
            // Disallow default constructor
            //
            BaseAggregate();

            uint32_t _fieldSetCounter;

         public:
            /// <summary>
            /// Get current version of aggregate.
            /// </summary>
            /// <returns>Aggregate version.</returns>
            const std::string& getVersion();
            void UpdateCalculatedFields();
            void UpdateVer();

            /// <summary>
            /// Convertes to the specified version.
            /// </summary>
            /// <param name="version">The new version</param>
            void convertVersion(std::string version)
            {
               // TODO implement - User Story 126595
            };
            /// <summary>
            /// Increments the global field set counter and returns the result.
            /// </summary>
            /// <returns>The incremented field set counter.</returns>
            uint32_t FieldSetCounter();

         public:
            // Field types
            typedef int32_t Int32Type;
            typedef int64_t Int64Type;
            typedef uint32_t UInt32Type;
            typedef uint64_t UInt64Type;
            typedef double DoubleType;
            typedef std::string StringType;
            typedef bool BoolType;

         protected:
            std::vector<VersionMetaData> _aggregateMetaData; // TODO add set/get? - User Story 126596
            std::vector<AbstractField*> _fieldList; // TODO add set/get? - User Story 126596
            int32_t _ver;
            std::string _version;
       };
      }
   }
}