#pragma once

#include <string>
#include <stdint.h>
#include "TypeEnum.h"

namespace Bct
{
   namespace Workflow
   {
      namespace Aggregates
      {
         /// <summary>
         /// Stores field metadata.
         /// </summary>
         class FieldInfo
         {
         public:
            /// <summary>
            /// Constructor.
            /// </summary>
            /// <param name="fieldId">Field id.</param>
            /// <param name="fieldName">Field name.</param>
            /// <param name="fieldType">Field type.</param>
            FieldInfo(int16_t fieldId, std::string const &fieldName, TypeEnum::Type const &fieldType);

            /// <summary>
            /// Constructor.
            /// </summary>
            /// <param name="fieldId">Field id.</param>
            /// <param name="fieldName">Field name.</param>
            /// <param name="fieldType">Field type.</param>
            /// <param name="fieldSubType">Field subtype.</param>
            FieldInfo(int16_t fieldId, std::string const &fieldName, TypeEnum::Type const &fieldType, TypeEnum::Type const &fieldSubtype);

            /// <summary>
            /// Returns the field id.
            /// </summary>
            /// <returns>Field id.</returns>
            int16_t fieldId() const;
            /// <summary>
            /// Returns field name.
            /// </summary>
            /// <returns>Field name.</returns>
            std::string fieldName() const;
            /// <summary>
            /// Returns field type.
            /// </summary>
            /// <returns>Field type.</returns>
            TypeEnum::Type FieldType() const;

            /// <summary>
            /// Returns field subtype.
            /// </summary>
            /// <returns>Field subtype.</returns>
            TypeEnum::Type FieldSubtype() const;

         private:
            int16_t _fieldId;
            std::string _fieldName;
            TypeEnum::Type _fieldType;
            TypeEnum::Type _fieldSubtype;

         };
      }
   }
}
