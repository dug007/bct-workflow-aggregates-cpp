#pragma once
#include "IBctLogger.h"
#include <vector>
#include <iostream>

//using namespace Bct::Common::CppLogging;
namespace Bct
{
   namespace Common
   {
      namespace CppLogging
      {
         /// <summary>
         /// Test Logger that derives from IBctLogger class.
         /// </summary>
         class TestLogger : public IBctLogger
         {
         public:
            /// <summary>
            /// Constructor
            /// </summary>
            TestLogger();

            /// <summary>
            /// Virtual destructor
            /// </summary>
            virtual ~TestLogger();

            /// <summary>
            /// LogDebug function used to do logging at the debug level
            /// </summary>
            /// <param name="buffer">String message for logging.</param>
            /// <param name="file">File the log message came from.</param>
            /// <param name="line">Line number the log message came from.</param>
            void logDebug(const std::string& buffer, const char* file, int line);

            /// <summary>
            /// LogInfo function used to do logging at the info level
            /// </summary>
            /// <param name="buffer">String message for logging.</param>
            /// <param name="file">File the log message came from.</param>
            /// <param name="line">Line number the log message came from.</param>
            void logInfo(const std::string& buffer, const char* file, int line);

            /// <summary>
            /// LogWarning function used to do logging at the warning level
            /// </summary>
            /// <param name="buffer">String message for logging.</param>
            /// <param name="file">File the log message came from.</param>
            /// <param name="line">Line number the log message came from.</param>
            void logWarning(const std::string& buffer, const char* file, int line);

            /// <summary>
            /// LogError function used to do logging at the error level
            /// </summary>
            /// <param name="buffer">String message for logging.</param>
            /// <param name="file">File the log message came from.</param>
            /// <param name="line">Line number the log message came from.</param>
            void logError(const std::string& buffer, const char* file, int line);

            /// <summary>
            /// GetStringOutput returns the stringoutput for testing purposes
            /// </summary>
            /// <returns>The string output variable</returns>
            const std::vector<std::string> getStringOutput() const;

         private:
            std::vector<std::string> _stringOutput;
         };
      }
   }
}

