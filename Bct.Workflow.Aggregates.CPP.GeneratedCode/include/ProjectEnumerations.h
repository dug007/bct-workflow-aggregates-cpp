
#pragma once
#include "BaseAggregate.h"
#include "BaseField.h"
#include "AggregateMetaData.h"
#include "AbstractAggregate.h"
#include "EnumField.h"
#include "StringField.h"
#include "VectorField.h"

using namespace Bct::Workflow::Aggregates;


namespace Bct
{
   namespace Workflow
   {
      namespace Implementation
      {

         namespace SimpleReferenceEnum
         {
            enum SimpleReference
            {
               /// <summary>very good reference</summary>
               VeryGood = 0, 
               /// <summary>good reference</summary>
               Good = 1, 
               /// <summary>average reference</summary>
               Average = 2, 
               /// <summary>below average reference</summary>
               BelowAverage = 4, 
               /// <summary>poor reference</summary>
               Poor = 8, 
               /// <summary>very poor reference</summary>
               VeryPoor = 16
            };
         }

         /// <summary>
         /// ProjectEnumerations
         /// </summary>
         class ProjectEnumerations : public BaseAggregate
         {
         private:
            void pushFields();

         public:
            /// <summary>
            /// 
            /// </summary>
            EnumField<int32_t, SimpleReferenceEnum::SimpleReference>                     simpleReferenceEnumGenerator;
            
            /// <summary>
            /// Default constructor. Creates the most recent version.
            /// </summary>
            ProjectEnumerations();

            /// <summary>
            /// Version constructor. Creates the specified version.
            /// </summary>
            /// <param name="version">Version to construct such as "1.2.0"</param>
            ProjectEnumerations(const std::string &version);

            /// <summary>
            /// Constructor for nested aggregate.
            /// </summary>
            /// <param name="fieldId">Field id of this nested aggregate.</param>
            /// <param name="parent">Parent aggregate of this nested aggregate</param>
            ProjectEnumerations(int32_t fieldId, BaseAggregate * const parent);

            /// <summary>
            /// Copy constructor.
            /// </summary>
            /// <param name="other">Aggregate to be copied.</param>
            ProjectEnumerations(const ProjectEnumerations & other);

            /// <summary>
            /// Constructor for copying when the aggregate is nested.
            /// 
            /// This constructor is used when this aggregate is being nested inside a parent aggregate and the parent aggregate
            /// is being copied. The parent aggregate copy uses this constuctor to give this aggregate the parent's address.
            /// </summary>
            /// <param name="other">The object being copied</param>
            /// <param name="parent">The parent of this nested aggregate.</param>
            ProjectEnumerations(const ProjectEnumerations & other, BaseAggregate * const parent);


            /// <summary>
            /// Assignment operator. 
            /// </summary>
            /// <param name="other">Object being copied.</param>
            /// <returns>Reference to new object.</returns>
            ProjectEnumerations & operator=(const ProjectEnumerations &other);

            /// <summary>
            /// Equal operator.
            /// </summary>
            /// <param name="fld">Other field to compare to</param>
            /// <returns>True if the two field's values are equal.</returns>
            bool operator ==(const ProjectEnumerations &other) const;

            /// <summary>
            /// Not equal operator.
            /// </summary>
            /// <param name="fld">Other field to compare to.</param>
            /// <returns>True if the two field's values are not equal.</returns>
            bool operator !=(const ProjectEnumerations &other) const;

            /// <summary>
            /// Virtual destructor
            /// </summary>
            virtual ~ProjectEnumerations();

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


