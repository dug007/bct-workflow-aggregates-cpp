#pragma once

#include "FieldMeta.h"
#include "AggregateMetaData.h"

namespace Bct
{
   namespace Workflow
   {
      namespace Aggregates
      {
         class AggregateMetaData;

         /// <summary>
         /// Helper class to simplify metadata definitions in code.
         /// </summary>
         class FluentMeta
         {
         public:
            /// <summary>
            /// Constructor.
            /// </summary>
            /// <param name="aggMeta">The AggregateMetaData involved in the fluent operation.</param>
            /// <param name="fieldMeta">The FieldMeta involved in the fluent operation.</param>
            /// <param name="position">The position of the metadata in the AggregateMetaData::fieldMetaData vector</param>
            FluentMeta(AggregateMetaData &aggMeta, FieldMeta &fieldMeta, size_t position);
            /// <summary>
            /// Given the version ver and the position _position of the existing metadata in the AggregateMetaData::fieldMetaData vector, 
            /// sets up the version vector to point to the metadata and sets the parent version in the metadata as appropriate.
            /// </summary>
            /// <param name="ver">Version of the parent.</param>
            /// <returns>The FluentMeta for continued fluent operations.</returns>
            FluentMeta &toVersion(int16_t ver);
         private:
            FieldMeta &_fieldMeta;
            AggregateMetaData &_aggMeta;
            size_t _position;
         };
      }
   }
}