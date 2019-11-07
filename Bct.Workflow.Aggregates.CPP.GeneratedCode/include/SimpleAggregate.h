
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
#include "VectorField.h"

using namespace Bct::Workflow::Aggregates;


namespace Bct
{
   namespace Workflow
   {
      namespace Implementation
      {


         /// <summary>
         /// Simple Type.
         /// </summary>
         class SimpleAggregate : public BaseAggregate
         {
         private:
            void pushFields();

         public:
            /// <summary>
            /// float field
            /// </summary>
            BaseField<double>                     doubleValue;
            
            /// <summary>
            /// Default constructor. Creates the most recent version.
            /// </summary>
            SimpleAggregate();

            /// <summary>
            /// Version constructor. Creates the specified version.
            /// </summary>
            /// <param name="version">Version to construct such as "1.2.0"</param>
            SimpleAggregate(const std::string &version);

            /// <summary>
            /// Constructor for nested aggregate.
            /// </summary>
            /// <param name="fieldId">Field id of this nested aggregate.</param>
            /// <param name="parent">Parent aggregate of this nested aggregate</param>
            SimpleAggregate(int32_t fieldId, BaseAggregate * const parent);

            /// <summary>
            /// Copy constructor.
            /// </summary>
            /// <param name="other">Aggregate to be copied.</param>
            SimpleAggregate(const SimpleAggregate & other);

            /// <summary>
            /// Constructor for copying when the aggregate is nested.
            /// 
            /// This constructor is used when this aggregate is being nested inside a parent aggregate and the parent aggregate
            /// is being copied. The parent aggregate copy uses this constuctor to give this aggregate the parent's address.
            /// </summary>
            /// <param name="other">The object being copied</param>
            /// <param name="parent">The parent of this nested aggregate.</param>
            SimpleAggregate(const SimpleAggregate & other, BaseAggregate * const parent);


            /// <summary>
            /// Assignment operator. 
            /// </summary>
            /// <param name="other">Object being copied.</param>
            /// <returns>Reference to new object.</returns>
            SimpleAggregate & operator=(const SimpleAggregate &other);

            /// <summary>
            /// Equal operator.
            /// </summary>
            /// <param name="fld">Other field to compare to</param>
            /// <returns>True if the two field's values are equal.</returns>
            bool operator ==(const SimpleAggregate &other) const;

            /// <summary>
            /// Not equal operator.
            /// </summary>
            /// <param name="fld">Other field to compare to.</param>
            /// <returns>True if the two field's values are not equal.</returns>
            bool operator !=(const SimpleAggregate &other) const;

            /// <summary>
            /// Virtual destructor
            /// </summary>
            virtual ~SimpleAggregate();

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


