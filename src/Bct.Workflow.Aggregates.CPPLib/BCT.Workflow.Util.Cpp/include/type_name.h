#pragma once

#ifndef _MSC_VER
#include <cxxabi.h>
#endif

#include <typeinfo>
#include <string>

template <class T>
std::string type_name(const T& t, int& status)
{
#ifdef _MSC_VER
   status = 0;
   const char* name = typeid(t).name();
   std::string result(name);
   return result;
#else
   char* realname = abi::__cxa_demangle(typeid (t).name(), NULL, NULL, &status);
   std::string result(realname);
   free(realname);
   return result;
#endif
}
