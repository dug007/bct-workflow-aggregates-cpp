#pragma once
#include <string>

namespace Bct
{
   namespace Common
   {
      namespace CppLogging
      {       
         /// <summary>
         /// Interface for supporing c++ logging.
         /// </summary>
         class IBctLogger
         {
         public:
            /// <summary>
            /// virtual destructor
            /// </summary>
            virtual ~IBctLogger() {};

            /// <summary>
            ///   log debug information
            /// </summary>
            /// <param name="buffer"></param>
            /// <param name="file"></param>
            /// <param name="line"></param>
            virtual void logDebug(const std::string& buffer, const char* file, int line) = 0;

            /// <summary>
            ///   log information
            /// </summary>
            /// <param name="buffer"></param>
            /// <param name="file"></param>
            /// <param name="line"></param>
            virtual void logInfo(const std::string& buffer, const char* file, int line) = 0;

            /// <summary>
            ///   log warning information
            /// </summary>
            /// <param name="buffer"></param>
            /// <param name="file"></param>
            /// <param name="line"></param>
            virtual void logWarning(const std::string& buffer, const char* file, int line) = 0;

            /// <summary>
            ///   log errors
            /// </summary>
            /// <param name="buffer"></param>
            /// <param name="file"></param>
            /// <param name="line"></param>
            virtual void logError(const std::string& buffer, const char* file, int line) = 0;
         };
      }
   }
}
