#pragma once
#include "IBctLogger.h"

namespace Bct
{
   namespace Common
   {
      namespace CppLogging
      {
         /// <summary>
         /// NullLogger that derives from IBctLogger class to be used if no logging is desired.
         /// Functions implemented from IBctLogger does not provide any functionality.
         /// </summary>
         class NullLogger : public IBctLogger
         {
         public:
            /// <summary>
            /// Constructor
            /// </summary>
            NullLogger() {};

            /// <summary>
            /// Destructor
            /// </summary>
            ~NullLogger() {};

            /// <summary>
            /// LogDebug function used to do logging at the debug level
            /// </summary>
            /// <param name="buffer">String message for logging.</param>
            /// <param name="file">File the log message came from.</param>
            /// <param name="line">Line number the log message came from.</param>
            void logDebug(const std::string& buffer, const char* file, int line) {};

            /// <summary>
            /// LogInfo function used to do logging at the info level
            /// </summary>
            /// <param name="buffer">String message for logging.</param>
            /// <param name="file">File the log message came from.</param>
            /// <param name="line">Line number the log message came from.</param>
            void logInfo(const std::string& buffer, const char* file, int line) {};

            /// <summary>
            /// LogWarning function used to do logging at the warning level
            /// </summary>
            /// <param name="buffer">String message for logging.</param>
            /// <param name="file">File the log message came from.</param>
            /// <param name="line">Line number the log message came from.</param>
            void logWarning(const std::string& buffer, const char* file, int line) {};

            /// <summary>
            /// LogError function used to do logging at the error level
            /// </summary>
            /// <param name="buffer">String message for logging.</param>
            /// <param name="file">File the log message came from.</param>
            /// <param name="line">Line number the log message came from.</param>
            void logError(const std::string& buffer, const char* file, int line) {};
         };

      }
   }
}
