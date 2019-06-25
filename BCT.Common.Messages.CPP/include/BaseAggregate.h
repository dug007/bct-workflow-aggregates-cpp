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


namespace Bct
{
   namespace Workflow
   {
      namespace Aggregates
      {
         class BaseAggregate
         {
         public:
            BaseAggregate(const int16_t major, const int16_t minor, const int16_t patch);

            virtual ~BaseAggregate();

         private:
            // Disallow default constructor
            //
            BaseAggregate();

         public:
            /**
             * Get current version of aggregate
             */
            const std::string& getVersion();
            const int16_t Major();
            const int16_t Minor();
            const int16_t Patch();
            void UpdateCalculatedFields();
            void UpdateVer();

         virtual void convertVersion(int16_t major, int16_t minor, int16_t patch) = 0;

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

            std::string _version;
            int16_t _ver;
            int16_t _major;
            int16_t _minor;
            int16_t _patch;
         };
      }
   }
}