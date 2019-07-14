#pragma once

#include <string>
#include <sstream>

namespace Bct
{
   namespace Workflow
   {
      namespace Aggregates
      {
         /// <summary>
         /// Version information.
         /// </summary>
         class VersionInfo
         {
         public:
            /// <summary>
            /// Constructor.
            /// </summary>
            VersionInfo()
            {

            }
            /// <summary>
            /// Sets the string value of the version.
            /// </summary>
            /// <param name="version"></param>
            VersionInfo(const std::string version) : _version(version)
            {
            }

            /// <summary>
            /// Gets the string value of the version.
            /// </summary>
            /// <returns></returns>
            std::string Version()
            {
               return _version;
            }

         private:
            std::string _version;
         };
      }
   }
}