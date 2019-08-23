
#pragma once
#include "BaseAggregate.h"
#include "BaseField.h"
#include "AggregateMetaData.h"
#include "AggComputeField.h"
#include "AbstractAggregate.h"
#include "EnumField.h"
#include "ReferenceEnum.h"
#include "AggComputeField.h"
#include "StringField.h"

using namespace Bct::Workflow::Aggregates;

namespace Bct
{
   namespace Workflow
   {
      namespace Implementation
      {
         /// <summary>
         /// ReferenceAggregate.
         /// </summary>
         class ReferenceAggregate : public BaseAggregate
         {
         private:
            void pushFields();

         public:
            /// <summary>
            /// Boolean field
            /// </summary>
            BaseField<bool>                     boolField;
                        /// <summary>
            /// integer field
            /// </summary>
            BaseField<int32_t>                     int32Field;
                        /// <summary>
            /// uinteger field
            /// </summary>
            BaseField<uint32_t>                     uint32Field;
                        /// <summary>
            /// integer field
            /// </summary>
            BaseField<int64_t>                     int64Field;
                        /// <summary>
            /// uinteger field
            /// </summary>
            BaseField<uint64_t>                     uint64Field;
                        /// <summary>
            /// double field
            /// </summary>
            BaseField<double>                     doubleField;
                        /// <summary>
            /// string field
            /// </summary>
            StringField                     stringField;
                        /// <summary>
            /// 
            /// </summary>
            EnumField<int32_t, ReferenceEnum::Reference>                     enumField;
            
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
            /// Constructor for nested aggregate.
            /// </summary>
            /// <param name="fieldId">Field id of this nested aggregate.</param>
            /// <param name="parent">Parent aggregate of this nested aggregate</param>
            ReferenceAggregate(int32_t fieldId, BaseAggregate * const parent);

            /// <summary>
            /// Copy constructor.
            /// </summary>
            /// <param name="other">Aggregate to be copied.</param>
            ReferenceAggregate(const ReferenceAggregate & other);

            /// <summary>
            /// Constructor for copying when the aggregate is nested.
            /// 
            /// This constructor is used when this aggregate is being nested inside a parent aggregate and the parent aggregate
            /// is being copied. The parent aggregate copy uses this constuctor to give this aggregate the parent's address.
            /// </summary>
            /// <param name="other">The object being copied</param>
            /// <param name="parent">The parent of this nested aggregate.</param>
            ReferenceAggregate(const ReferenceAggregate & other, BaseAggregate * const parent);


            /// <summary>
            /// Assignment operator. 
            /// </summary>
            /// <param name="other">Object being copied.</param>
            /// <returns>Reference to new object.</returns>
            ReferenceAggregate & operator=(const ReferenceAggregate &other);


            /// <summary>
            /// Virtual destructor
            /// </summary>
            virtual ~ReferenceAggregate();

            /// <summary>
            /// Virtual function to return the metadata reference for this object. Aggregates must implement this at the most-derived level such as generated code.
            /// </summary>
            /// <returns>The associated AggregateMetaData object.</returns>BaseAggregate-default-constructor-summary
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


