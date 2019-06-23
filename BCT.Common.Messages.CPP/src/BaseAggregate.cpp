#include "BaseAggregate.h"

namespace Bct
{
   namespace Workflow
   {
      namespace Aggregates
      {
         BaseAggregate::BaseAggregate(const int16_t ver)
            : _ver(ver)
         {
         }
         /**
          * Destructor
          */
         BaseAggregate::~BaseAggregate() {};

         const std::string& BaseAggregate::getVersion()
         {
            // TODO: remove _version?
            _version = std::to_string(_major) + '.' + std::to_string(_minor) + '.' + std::to_string(_patch);
            return _version;
         };
         const int16_t BaseAggregate::Major()
         {
            return _major;
         }
         const int16_t BaseAggregate::Minor()
         {
            return _minor;
         }
         const int16_t BaseAggregate::Patch()
         {
            return _patch;
         }
      }
   }
}