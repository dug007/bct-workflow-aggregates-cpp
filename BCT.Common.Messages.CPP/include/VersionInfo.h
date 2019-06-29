#pragma once

#include <string>
#include <sstream>

namespace Bct
{
   namespace Workflow
   {
      namespace Aggregates
      {
         class VersionInfo
         {
         public:
            VersionInfo()
            {

            }
            VersionInfo(const std::string version) : _version(version)
            {
            }

            const std::string Version()
            {
               return _version;
            }

         private:
            std::string _version;
         };
      }
   }
}