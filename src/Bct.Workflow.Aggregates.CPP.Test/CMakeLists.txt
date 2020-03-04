cmake_minimum_required(VERSION 3.0.0)


#This Cmakefile expects to be above the source file folders
set(AGGSRC ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(AGGTST ${CMAKE_CURRENT_SOURCE_DIR}/test)
set(AGGINC ${CMAKE_CURRENT_SOURCE_DIR}/include)


add_executable(BCT.Workflow.Aggregates.CPP.Test 
            ${AGGSRC}/AggAssess.cpp
            ${AGGSRC}/AggNested.cpp
            ${AGGSRC}/AssessMetaData.cpp
            ${AGGTST}/AggLoggingUnitTests.cpp
            ${AGGTST}/AggNestedUnitTests.cpp
            ${AGGTST}/AssessUnitTests.cpp
            ${AGGTST}/CodeGenerationUnitTests.cpp
            ${AGGTST}/ComputeFieldUnitTests.cpp
            ${AGGTST}/EnumFieldUnitTests.cpp
            ${AGGTST}/GeneralUnitTests.cpp
            ${AGGTST}/MetaUnitTests.cpp
            ${AGGTST}/QAComprehensiveUnitTests.cpp
            ${AGGTST}/ReferenceAggregateUnitTests.cpp
            ${AGGTST}/TestHelperBaseField.h
            ${AGGTST}/VectorFieldUnitTests.cpp
            ${AGGTST}/VersionChangeRuleUnitTests.cpp

            ${AGGINC}/AggAssess.h
            ${AGGINC}/AggNested.h
            ${AGGINC}/AssessMetaData.h
            ${AGGINC}/TestLogger.h 
            )


include_directories(BCT.Workflow.Aggregates.CPP.Test 
  PUBLIC ${AGGINC}
  PRIVATE ${CMAKE_SOURCE_DIR}/Bct.Workflow.Aggregates.CPP.GeneratedCode/include
  PRIVATE ${CMAKE_SOURCE_DIR}/Bct.Workflow.Aggregates.CPPLib/BCT.Workflow.Util.Cpp/include
  PRIVATE ${CMAKE_SOURCE_DIR}/Bct.Workflow.Aggregates.CPPLib/rapidjson
  PRIVATE ${CMAKE_SOURCE_DIR}/Bct.Workflow.Aggregates.CPPLib/BCT.Common.CppLogging/include
  PRIVATE ${CMAKE_SOURCE_DIR}/Bct.Workflow.Aggregates.CPPLib/BCT.RPNEvaluator.CPP/include
  INTERFACE ${CMAKE_SOURCE_DIR}/catch
  )

target_link_libraries(BCT.Workflow.Aggregates.CPP.Test
     BCT.Workflow.Aggregates.CPPLib
     BCT.Workflow.Aggregates.CPP.GeneratedCode
     BCT.RPNEvaluator.CPPLib)


add_test(NAME WorkflowAggregateTests 
        COMMAND BCT.Workflow.Aggregates.CPP.Test)