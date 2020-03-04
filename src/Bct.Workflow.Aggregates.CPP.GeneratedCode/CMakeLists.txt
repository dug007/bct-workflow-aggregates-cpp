cmake_minimum_required(VERSION 3.0.0)
project(BCT.Workflow.Aggregates.CPP.GeneratedCode)


#This Cmakefile expects to be above the source file folders
set(GENSRC ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(GENINC ${CMAKE_CURRENT_SOURCE_DIR}/include)


add_library(BCT.Workflow.Aggregates.CPP.GeneratedCode SHARED 
            ${GENSRC}/AggComputeField.cpp
            ${GENSRC}/NestedWithReference.cpp
            ${GENSRC}/PlateletConfigAggregate.cpp
            ${GENSRC}/PlateletTemplateAggregate.cpp
            ${GENSRC}/ProjectEnumerations.cpp
            ${GENSRC}/ReferenceAggregate.cpp
            ${GENSRC}/Sample1Aggregate.cpp
            ${GENSRC}/SimpleAggregate.cpp

            ${GENINC}/AggComputeField.h
            ${GENINC}/NestedWithReference.h
            ${GENINC}/PlateletConfigAggregate.h
            ${GENINC}/PlateletTemplateAggregate.h 
            ${GENINC}/ProjectEnumerations.h 
            ${GENINC}/ReferenceAggregate.h 
            ${GENINC}/Sample1Aggregate.h
            ${GENINC}/SimpleAggregate.h
            ${GENINC}/ReferenceEnum.h
            )


target_include_directories(BCT.Workflow.Aggregates.CPP.GeneratedCode
  PUBLIC ${GENINC}
  PRIVATE ${CMAKE_SOURCE_DIR}/Bct.Workflow.Aggregates.CPPLib/include
  PRIVATE ${CMAKE_SOURCE_DIR}/Bct.Workflow.Aggregates.CPPLib/rapidjson
  PRIVATE ${CMAKE_SOURCE_DIR}/Bct.Workflow.Aggregates.CPPLib/BCT.Common.CppLogging/include
  PRIVATE ${CMAKE_SOURCE_DIR}/Bct.Workflow.Aggregates.CPPLib/BCT.Workflow.Util.Cpp/include
  )

target_link_libraries(BCT.Workflow.Aggregates.CPPLib)
