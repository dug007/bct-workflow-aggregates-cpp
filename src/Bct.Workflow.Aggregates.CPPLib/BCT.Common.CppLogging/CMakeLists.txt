cmake_minimum_required(VERSION 3.0.0)
project(BCT.Common.CppLogging)


#This Cmakefile expects to be above the source file folders
set(LOGTST ${CMAKE_CURRENT_SOURCE_DIR}/test)
set(LOGINC ${CMAKE_CURRENT_SOURCE_DIR}/include)


add_library(BCT.Common.CppLogging SHARED 
            ${LOGTST}/IBctLoggerUnitTests.cpp
            ${LOGTST}/TestLogger.cpp
            ${LOGTST}/TestLogger.h

            ${LOGINC}/IBctLogger.h
            ${LOGINC}/NullLogger.h
            )


target_include_directories(BCT.Common.CppLogging 
  PUBLIC ${LOGINC}
  PUBLIC ${LOGTST}
  PRIVATE ${CMAKE_SOURCE_DIR}/catch
  )


target_link_libraries(BCT.Common.CppLogging)
