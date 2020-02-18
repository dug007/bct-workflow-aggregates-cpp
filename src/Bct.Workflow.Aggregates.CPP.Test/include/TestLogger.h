#pragma once
#include "IBctLogger.h"

#include <iostream>
#include <fstream>
#include <sstream>

using namespace Bct::Common::CppLogging;


namespace Bct
{
   namespace Workflow
   {
      namespace Implementation
      {
         
         class TestLogger : public IBctLogger
         {
         public:
            TestLogger() : _file(NULL), _line(0)
            {
            }
            virtual~TestLogger()
            {             
            }

            virtual void logDebug(const std::string& msg, const char* file, int line)
            {
               _stringOutput.push_back("logDebug call successful");
            }

            virtual void logInfo(const std::string& msg, const char* file, int line)
            {
               _stringOutput.push_back("logInfo call successful");
            }

            virtual void logWarning(const std::string& msg, const char* file, int line)
            {
               _stringOutput.push_back("logWarning call successful");
            }

            virtual void logError(const std::string& msg, const char* file, int line)
            {
               _stringOutput.push_back("logError call successful");
            }

            /// <summary>
            /// GetStringOutput returns the stringoutput for testing purposes
            /// </summary>
            /// <returns>The string output variable</returns>
            const std::vector<std::string> getStringOutput() const
            {
               return _stringOutput;
            }

         private:
            const char* _file;
            int _line;
            std::vector<std::string> _stringOutput;
         };
      }
   }
}