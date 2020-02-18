#pragma once

#include "StringField.h"

namespace Bct
{
   namespace Workflow
   {
      namespace Aggregates
      {
         /// <summary>
         /// Class for read-only string fields.
         /// </summary>
         class StringFieldRo : public StringField
         {
         private:
            using StringField::value; // hide value set/get
            using StringField::unset;
         public:
            /// <summary>
            /// Constructor.
            /// </summary>
            /// <param name="fieldId">Id of this field.</param>
            /// <param name="aggregate">The associated aggregate this field is a member of.</param>
            StringFieldRo(int32_t fieldId, AbstractAggregate * const aggregate);

            /// <summary>
            /// Constructor for copying but not copy constructor.
            /// </summary>
            /// <param name="other">The object being copied.</param>
            /// <param name="aggregate">The associated aggregate this field is a member of.</param>
            StringFieldRo(const StringFieldRo &other, AbstractAggregate * const aggregate);

            /// <summary>
            /// Destructor.
            /// </summary>
            virtual ~StringFieldRo();

            /// <summary>
            /// Assignment operator.
            /// </summary>
            /// <param name="fld">Other to assign from.</param>
            /// <returns>Reference to assigned.</returns>
            StringFieldRo & operator=(const StringFieldRo & fld);

            /// <summary>
            /// Gets the read-only value.
            /// </summary>
            /// <returns>Value.</returns>
            const std::string value();
         };
      }
   }
}


