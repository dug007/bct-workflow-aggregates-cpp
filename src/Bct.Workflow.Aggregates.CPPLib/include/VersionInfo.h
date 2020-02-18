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
            VersionInfo();

            /// <summary>
            /// Sets the string value of the version.
            /// </summary>
            /// <param name="version">Version string.</param>
            VersionInfo(const std::string &version);

            /// <summary>
            /// Gets the string value of the version.
            /// </summary>
            /// <returns></returns>
            std::string Version();

         private:
            std::string _version;
         };
      }
   }
}