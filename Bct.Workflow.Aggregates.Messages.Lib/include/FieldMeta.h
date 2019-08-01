#pragma once

#include <string>
#include "FieldStateEnum.h"

namespace Bct
{
   namespace Workflow
   {
      namespace Aggregates
      {
         /// <summary>
         /// Metadata for a single field.
         /// </summary>
         class FieldMeta
         {
         public:
            /// <summary>
            /// Constructor.
            /// </summary>
            /// <param name="fieldName">Field name of associated field for this metadata.</param>
            /// <param name="fieldState">Initial state of associated field.</param>
            /// <param name="def">Default value of associated field.</param>
            /// <param name="parentVer">Version of the parent metadata is associated with or BaseAggregate::InAllVersions if the metadata is in every version. If BaseAggregate::InAllVersions, then the metadata only needs to placed in version 0 vector.</param>
            FieldMeta(std::string const &fieldName, FieldStateEnum::FieldState const &fieldState, std::string const &def, int16_t ver);
            /// <summary>
            /// Constructor.
            /// </summary>
            /// <param name="fieldName">Field name of associated field for this metadata.</param>
            /// <param name="fieldState">Initial state of associated field.</param>
            /// <param name="parentVer">Version of the parent metadata is associated with or BaseAggregate::InAllVersions if the metadata is in every version. If BaseAggregate::InAllVersions, then the metadata only needs to placed in version 0 vector.</param>
            /// <param name="childVer">Version of the child</param>
            FieldMeta(const std::string fieldName, const FieldStateEnum::FieldState fieldState, int16_t parentVer, int16_t childVer);

            /// <summary>
            /// Provides the field name of the associated field.
            /// </summary>
            /// <returns></returns>
            std::string FieldName();

            /// <summary>
            /// The default of the field.
            /// </summary>
            std::string _default;
            /// <summary>
            /// The field state of the field.
            /// </summary>
            FieldStateEnum::FieldState _fieldState;

            /// <summary>
            /// The parent version.
            /// </summary>
            int16_t _parentVer;

            /// <summary>
            /// The child version.
            /// </summary>
            int16_t _childVer;

         private:
            std::string _fieldName;
         };

      }
   }
}

