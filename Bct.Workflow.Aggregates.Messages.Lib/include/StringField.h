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
            /// <param name="fieldName">Name of this field.</param>
            /// <param name="aggregate">The associated aggregate this field is a member of.</param>
            StringField(std::string const &fieldName, AbstractAggregate *aggregate);

            virtual ~StringField()
            {
            }

            virtual void initMetaData(int16_t ver);
            /// <summary>
            /// Sets the value of this field using its string representation. This function is not public and is only needed for RPN computations.
            /// </summary>
            /// <param name="val">String representation of this field.</param>
            virtual void ComputedValueString(const std::string & val);

            /// <summary>
            /// Assignment operator.
            /// </summary>
            /// <param name="val"></param>
            /// <returns>The underlying value of the field.</returns>
            std::string operator=(std::string const &val)
            {
               this->Value(val);
               return *this;
            }
         };
      }
   }
}
