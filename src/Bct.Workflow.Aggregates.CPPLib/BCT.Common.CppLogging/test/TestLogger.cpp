#include "TestLogger.h"


namespace Bct
{
   namespace Common
   {
      namespace CppLogging
      {
         TestLogger::TestLogger()
         {
         }

         TestLogger::~TestLogger()
         {
         }

         const std::vector<std::string> TestLogger::getStringOutput() const
         {
            return _stringOutput;
         }

         void TestLogger::logDebug(const std::string & buffer, const char * file, int line)
         {
            _stringOutput.push_back("logDebug call successful");
         }

         void TestLogger::logInfo(const std::string & buffer, const char * file, int line)
         {
            _stringOutput.push_back("logInfo call successful");
         }

         void TestLogger::logWarning(const std::string & buffer, const char * file, int line)
         {
            _stringOutput.push_back("logWarning call successful");
         }

         void TestLogger::logError(const std::string & buffer, const char * file, int line)
         {
            _stringOutput.push_back("logError call successful");
         }

      }
   }
}