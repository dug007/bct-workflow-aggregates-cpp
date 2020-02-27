#pragma once

#ifdef __GNUG__
#include <cstdlib>
#include <string>
#include <cxxabi.h>
namespace Bct
{
   namespace Workflow
   {
      namespace Aggregates
      {
         struct handle
         {
            char* p;
            handle(char* ptr) : p(ptr) {}
            ~handle() { std::free(p); }
         };
         static std::string demangle(const char* name)
         {
            int status = -4; //some arbitrary value to eliminate the compiler warning
            handle result(abi::__cxa_demangle(name, NULL, NULL, &status));
            return (status == 0) ? result.p : name;
         }
      }
   }
}
#else
namespace Bct
{
   namespace Workflow
   {
      namespace Aggregates
      {
         static std::string demangle(const char* name)
         {
            return name;
         }
      }
   }
}
#endif

