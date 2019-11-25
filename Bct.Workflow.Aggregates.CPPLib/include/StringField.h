#pragma once
#include <string>

#include "BaseAggregate.h"
#include "BaseField.h"
#include "TypeEnum.h"

namespace Bct
{
   namespace Workflow
   {
      namespace Aggregates
      {
         /// <summary>
         /// Field of type string. This field derives from BaseField to simplify serialization.
         /// </summary>
         class StringField : public BaseField<std::string>
         {

         public:
            /// <summary>
            /// Constructor.
            /// </summary>
            /// <param name="fieldId">Id of this field.</param>
            /// <param name="aggregate">The associated aggregate this field is a member of.</param>
            StringField(int32_t fieldId, AbstractAggregate * const aggregate);

            /// <summary>
            /// Constructor for copying when owner is nested aggregate.
            /// </summary>
            /// <param name="fieldId">Object being copied</param>
            /// <param name="aggregate">The associated nested aggregate this field is a member of.</param>
            StringField(const StringField &other, AbstractAggregate * const aggregate);

            /// <summary>
            /// Virtual destructor.
            /// </summary>
            virtual ~StringField();

            /// <summary>
            /// Assignment operator.
            /// </summary>
            /// <param name="fld">Other assigning from.</param>
            /// <returns>Reference to assigned.</returns>
            StringField & operator=(const StringField & fld);

            /// <summary>
            /// Assignment operator.
            /// </summary>
            /// <param name="val"></param>
            /// <returns>The underlying value of the field.</returns>
            std::string operator=(std::string const &val);

            /// <summary>
            /// Conversion operator.
            /// </summary>
            /// <returns>The value of this field.</returns>
            operator std::string() const
            {
               return BaseField<std::string>::ComputedValueString();
            }

            /// <summary>
            /// Returns value as a string.
            /// </summary>
            /// <returns>Value as a string.</returns>
            virtual std::string ComputedValueString() const;

            virtual void initMetaData(int16_t ver);
            /// <summary>
            /// Sets the value of this field using its string representation. This function is not public and is only needed for RPN computations.
            /// </summary>
            /// <param name="val">String representation of this field.</param>
            virtual void ComputedValueString(const std::string & val);

         };
      }
   }
}
