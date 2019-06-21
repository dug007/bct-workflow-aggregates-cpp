// BCT.Common.DevComm.Messages.CPPVxWorks.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "test/Test.hpp"
#include <iostream>

int main()
{

      // Various overrides for changing how to output the logging.
#if 0
      TEST_OVERRIDE_LOG(CustomLogger, new CustomLogger("unit_test_log.txt"));
#endif

#if 0 // Enable when logging only to file
      TEST_OVERRIDE_FILE_LOG("unit_test_log.txt");
#endif

#if 1 // Enable when logging to file and stdout
      TEST_OVERRIDE_STDIO_FILE_LOG("unit_test_log.txt");
#endif

      // Return from main success or failure.
      bool test_has_failed = TEST_HAS_FAILED;

      return test_has_failed ? 1 : 0;
}