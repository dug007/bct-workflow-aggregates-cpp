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
               sscanf_s(version.c_str(), "%d.%d.%d", &_major, &_minor, &_patch);
            }

            VersionInfo(const int16_t major, const int16_t minor, const int16_t patch) : _major(major), _minor(minor), _patch(patch)
            {
               std::stringstream ss;
               ss << _major << '.' << _minor << '.' << _patch;
               _version = ss.str();
            }

            const std::string Version()
            {
               return _version;
            }

            const int16_t Major()
            {
               return _major;
            };

            const int16_t Minor()
            {
               return _minor;
            }

            const int16_t Patch()
            {
               return _patch;
            }

         private:
            std::string _version;
            int16_t _major;
            int16_t _minor;
            int16_t _patch;
         };
      }
   }
}