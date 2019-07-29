#pragma once
#include "BaseAggregate.h"
#include "BaseField.h"
#include "AggregateMetaData.h"
#include "AggComputeField.h"
#include "AbstractAggregate.h"
#include "EnumField.h"
#include "ReferenceEnum.h"
#include "AggComputeField.h"

namespace Bct
{
   namespace Workflow
   {
      namespace Aggregates
      {
         /// <summary>
         /// ReferenceAggregate-class-summary
         /// </summary>
         class ReferenceAggregate : public BaseAggregate
         {
         private:
            static AggregateMetaData *s_metaData;
            static bool s_initialized;

         public:
            /// <summary>
            /// boolField-field-summary
            /// </summary>
            BaseField<bool>                     boolField;
            /// <summary>
            /// int32lField-field-summary
            /// </summary>
            BaseField<int32_t>                  int32Field;
            /// <summary>
            /// uint32Field-field-summary
            /// </summary>
            BaseField<uint32_t>                 uint32Field;
            /// <summary>
            /// int64-field-summary
            /// </summary>
            BaseField<uint32_t>                 int64Field;
            /// <summary>
            /// uint64Field-field-summary
            /// </summary>
            BaseField<int64_t>                  uint64Field;
            /// <summary>
            /// doubleField-field-summary
            /// </summary>
            BaseField<double>                   doubleField;
            /// <summary>
            /// stringField-field-summary
            /// </summary>
            BaseField<std::string>              stringField;
            /// <summary>
            /// enumField-field-summary
            /// </summary>
            EnumField<ReferenceEnum::Reference, uint16_t> enumField;

            /// <summary>
            /// Default constructor. Creates the most recent version.
            /// </summary>
            ReferenceAggregate();

            /// <summary>
            /// Version constructor. Creates the specified version.
            /// </summary>
            /// <param name="version">Version to construct such as "1.2.0"</param>
            ReferenceAggregate(const std::string &version);

            /// <summary>
            /// Associates (binds) a metadata object to this aggregate. This must be called before syncVersion is called.
            /// This will point to a static instance of AggregateMetaData.
            /// </summary>
            /// <param name="metaData">Pointer to the metadata object.</param>
            static void bindMetaData(AggregateMetaData  *metaData);

            /// <summary>
            /// Virtual function to return the metadata reference for this object. Aggregates must implement this at the most-derived level such as generated code.
            /// </summary>
            /// <returns>The associated AggregateMetaData object.</returns>ReferenceAggregate-default-constructor-summary
            virtual AggregateMetaData &MetaData() const;
         };
      }
   }
}

