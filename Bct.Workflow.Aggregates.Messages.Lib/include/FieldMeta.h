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
            FieldMeta(std::string const &fieldName, FieldStateEnum::FieldState const &fieldState, std::string const &def, int16_t ver) :
               _fieldName(fieldName), _fieldState(fieldState), _default(def), _parentVer(ver)
            {
            };

            FieldMeta(const std::string fieldName, const FieldStateEnum::FieldState fieldState, int16_t parentVer, int16_t childVer) :
               _fieldName(fieldName), _fieldState(fieldState), _parentVer(parentVer), _childVer(childVer)
            {
            };

            std::string FieldName();


            std::string _default;
            FieldStateEnum::FieldState _fieldState;
            int16_t _parentVer;
            int16_t _childVer;

         private:
            std::string _fieldName;
         };

      }
   }
}

