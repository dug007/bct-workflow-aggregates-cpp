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
         class StringField : public BaseField<std::string>
         {
         public:
            /// <summary>
            /// Constructor.
            /// </summary>
            /// <param name="fieldName">Name of this field.</param>
            /// <param name="aggregate">The associated aggregate this field is a member of.</param>
            StringField(std::string const &fieldName, AbstractAggregate *aggregate);

            virtual void initMetaData(int16_t ver);
            /// <summary>
            /// Sets the value of this field using its string representation. This function is not public and is only needed for RPN computations.
            /// </summary>
            /// <param name="val">String representation of this field.</param>
            virtual void ComputedValueString(const std::string & val);

            //std::string operator=(const std::string &val)
            //{
            //   this->Value(val);
            //   return *this;
            //}

            /// <summary>
            /// Conversion operator.
            /// </summary>
            /// <returns>The value of this field.</returns>
            operator const std::string&() const
            {
               return this->Value();
            }
         };
      }
   }
}
