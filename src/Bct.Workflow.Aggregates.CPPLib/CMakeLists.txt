cmake_minimum_required(VERSION 3.0.0)
project(BCT.Workflow.Aggregates.CPPLib)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_subdirectory(BCT.Common.CppLogging)

add_subdirectory(BCT.RPNEvaluator.CPP)

#This Cmakefile expects to be above the source file folders
set(AGGSRC ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(AGGINC ${CMAKE_CURRENT_SOURCE_DIR}/include)


add_library(BCT.Workflow.Aggregates.CPPLib SHARED 
            ${AGGSRC}/AggregateMetaData.cpp
            ${AGGSRC}/AggregateNotFound.cpp
            ${AGGSRC}/AssessmentResult.cpp
            ${AGGSRC}/AssessmentRule.cpp
            ${AGGSRC}/BaseAggregate.cpp
            ${AGGSRC}/CannotConvertScalar.cpp
            ${AGGSRC}/ComputeRule.cpp
            ${AGGSRC}/FieldInfo.cpp
            ${AGGSRC}/FieldMeta.cpp
            ${AGGSRC}/FluentAssessmentRule.cpp
            ${AGGSRC}/FluentComputeRule.cpp
            ${AGGSRC}/FluentMeta.cpp
            ${AGGSRC}/FluentVersionChangeRule.cpp
            ${AGGSRC}/NoSuchVersion.cpp
            ${AGGSRC}/NotAbleToGet.cpp
            ${AGGSRC}/NotAbleToSet.cpp
            ${AGGSRC}/StringField.cpp
            ${AGGSRC}/StringFieldRo.cpp
            ${AGGSRC}/VersionChangeRule.cpp
            ${AGGSRC}/VersionInfo.cpp

            ${AGGINC}/AbstractAggregate.h
            ${AGGINC}/AbstractField.h
            ${AGGINC}/AggregateMetaData.h
            ${AGGINC}/AggregateNotFound.h 
            ${AGGINC}/AssessmentResult.h 
            ${AGGINC}/AssessmentRule.h 
            ${AGGINC}/BaseAggregate.h
            ${AGGINC}/BaseField.h
            ${AGGINC}/CannotConvertScalar.h
            ${AGGINC}/ComputeRule.h
            ${AGGINC}/EnumField.h
            ${AGGINC}/EnumFieldRo.h
            ${AGGINC}/FieldInfo.h
            ${AGGINC}/FieldMeta.h
            ${AGGINC}/FluentAssessmentRule.h
            ${AGGINC}/FluentComputeRule.h
            ${AGGINC}/FluentMeta.h
            ${AGGINC}/FluentVersionChangeRule.h
            ${AGGINC}/NoSuchVersion.h
            ${AGGINC}/NotAbleToGet.h
            ${AGGINC}/NotAbleToSet.h
            ${AGGINC}/StringField.h
            ${AGGINC}/StringFieldRo.h
            ${AGGINC}/VectorField.h
            ${AGGINC}/VersionChangeRule.h
            ${AGGINC}/VersionInfo.h
            ${AGGINC}/VersionMetaData.h
            )


target_include_directories(BCT.Workflow.Aggregates.CPPLib
  PUBLIC ${AGGINC}
  PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/BCT.Workflow.Util.Cpp/include
  PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/rapidjson
  PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/BCT.Common.CppLogging/include
  PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/BCT.RPNEvaluator.CPP/include
  )


target_link_libraries(BCT.Workflow.Aggregates.CPPLib)
