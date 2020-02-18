#pragma once
#include "BaseAggregate.h"
#include "BaseField.h"
#include "AggregateMetaData.h"
#include "AbstractAggregate.h"
#include "EnumField.h"
#include "ReferenceEnum.h"
#include "ReferenceAggregate.h"
#include "StringField.h"

using namespace Bct::Workflow::Aggregates;

namespace Bct
{
   namespace Workflow
   {
      namespace Implementation
      {
         /// <summary>
         /// NestedWithReferenceAggregate-class-summary
         /// </summary>
         class NestedWithReferenceAggregate : public BaseAggregate
         {
         private:
            void pushFields();
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
            BaseField<int64_t>                 int64Field;
            /// <summary>
            /// uint64Field-field-summary
            /// </summary>
            BaseField<uint64_t>                  uint64Field;
            /// <summary>
            /// doubleField-field-summary
            /// </summary>
            BaseField<double>                   doubleField;
            /// <summary>
            /// stringField-field-summary
            /// </summary>
            StringField                         stringField;
            /// <summary>
            /// enumField-field-summary
            /// </summary>
            EnumField<uint32_t, ReferenceEnum::Reference> enumField;
            /// <summary>
            /// Nested ReferenceAggregate
            /// </summary>
            ReferenceAggregate                  aggField;

            /// <summary>
            /// Default constructor. Creates the most recent version.
            /// </summary>
            NestedWithReferenceAggregate();

            /// <summary>
            /// Version constructor. Creates the specified version.
            /// </summary>
            /// <param name="version">Version to construct such as "1.2.0"</param>
            NestedWithReferenceAggregate(const std::string &version);

            /// <summary>
            /// Constructor for nested aggregate.
            /// </summary>
            /// <param name="fieldId">Field id of this nested aggregate.</param>
            /// <param name="parent">Parent aggregate of this nested aggregate</param>
            NestedWithReferenceAggregate(int32_t fieldId, BaseAggregate * const parent);

            /// <summary>
            /// Copy constructor.
            /// </summary>
            /// <param name="other">Aggregate to be copied.</param>
            NestedWithReferenceAggregate(const NestedWithReferenceAggregate & other);

            /// <summary>
            /// Constructor for copying when the aggregate is nested.
            /// 
            /// This constructor is used when this aggregate is being nested inside a parent aggregate and the parent aggregate
            /// is being copied. The parent aggregate copy uses this constuctor to give this aggregate the parent's address.
            /// </summary>
            /// <param name="other">The object being copied</param>
            /// <param name="parent">The parent of this nested aggregate.</param>
            NestedWithReferenceAggregate(const NestedWithReferenceAggregate & other, BaseAggregate * const parent);

            /// <summary>
            /// Assignment operator. 
            /// </summary>
            /// <param name="other">Object being copied.</param>
            /// <returns>Reference to new object.</returns>
            NestedWithReferenceAggregate & operator=(const NestedWithReferenceAggregate &other);

            /// <summary>
            /// Virtual destructor
            /// </summary>
            virtual ~NestedWithReferenceAggregate();

            /// <summary>
            /// Virtual function to return the metadata reference for this object. Aggregates must implement this at the most-derived level such as generated code.
            /// </summary>
            /// <returns>The associated AggregateMetaData object.</returns>ReferenceAggregate-default-constructor-summary
            virtual AggregateMetaData &MetaData() const;

            /// <summary>
            /// Static method to access meta data for this aggregrate class.
            /// The method initializes the meta data structure if it has not already been done and returns a reference
            /// </summary>
            /// <returns>The associated AggregateMetaData object.</returns>
            static AggregateMetaData & s_MetaData();
         };
      }
   }
}


