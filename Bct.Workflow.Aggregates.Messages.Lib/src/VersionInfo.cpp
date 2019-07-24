#include "VersionInfo.h"
#include <string>
#include <sstream>

namespace Bct
{
   namespace Workflow
   {
      namespace Aggregates
      {
         VersionInfo::VersionInfo()
         {
         }

         VersionInfo::VersionInfo(const std::string &version)
            : _version(version)
         {
         }

         std::string VersionInfo::Version()
         {
            return _version;
         }
      };
   }
}
