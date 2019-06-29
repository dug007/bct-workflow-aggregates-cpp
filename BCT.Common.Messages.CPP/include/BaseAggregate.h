#pragma once

#include <vector>
#include <map>
#include <stdint.h>
#include <sstream>
#include "FieldStateEnum.h"
#include "FieldTypeEnum.h"
#include "BaseAggregate.h"
#include "AssessmentRule.h"
#include "VersionMetaData.h"
#include "VersionChangeRule.h"
#include "ComputeRule.h"
#include "FieldMeta.h"
#include "AbstractField.h"
#include "TypeCode.h"
#include "AbstractAggregate.h"


namespace Bct
{
   namespace Workflow
   {
      namespace Aggregates
      {
         class BaseAggregate : public AbstractAggregate
         {
         public:
            BaseAggregate(const std::string version);

            virtual ~BaseAggregate();

         private:
            // Disallow default constructor
            //
            BaseAggregate();

            int32_t _fieldSetCounter;

         public:
            /**
             * Get current version of aggregate
             */
            const std::string& getVersion();
            void UpdateCalculatedFields();
            void UpdateVer();


            void convertVersion(std::string version)
            {
               // TODO implement
            };

            int16_t FieldSetCounter();

         public:
            // Field types
            typedef int32_t Int32Field;
            typedef int64_t Int64Field;
            typedef uint32_t UInt32Field;
            typedef uint64_t UInt64Field;
            typedef double DoubleField;
            typedef std::string StringField;
            typedef bool BoolField;

         protected:
            std::vector<VersionMetaData> _aggregateMetaData; // TODO add set/get?
            std::vector<AbstractField*> _fieldList; // TODO add set/get?
            int32_t _ver;
            std::string _version;

       };
      }
   }
}