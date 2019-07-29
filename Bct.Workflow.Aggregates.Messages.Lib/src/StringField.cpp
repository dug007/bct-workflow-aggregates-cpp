#include "StringField.h"

namespace Bct
{
   namespace Workflow
   {
      namespace Aggregates
      {
            void StringField::initMetaData(int16_t ver)
            {
               _ver = ver;

               // search for the metadata for corresponding version and field name, then initialize this field
               // with that located metadata instance
               FieldMeta &fm = findFieldMeta();
               const FieldStateEnum::FieldState &state = fm._fieldState;
               _state = state;

               if (state == FieldStateEnum::Constant || state == FieldStateEnum::Default)
               {
                  SetDefault(DefaultStr());
               }
            }

            /// <summary>
            /// Sets the value of this field using its string representation. This function is not public and is only needed for RPN computations.
            /// </summary>
            /// <param name="val">String representation of this field.</param>
            void StringField::ComputedValueString(const std::string & val)
            {
               ValueInternal(val, true);
            }
         };
      }
   }
}
