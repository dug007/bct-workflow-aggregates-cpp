cmake_minimum_required(VERSION 3.0.0)
project(BCT.RPNEvaluator.CPPLib)

#restated here to support independent RPNEvaluator builds
set(CMAKE_CXX_STANDARD 98)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)


#This Cmakefile expects to be above the source file folders
set(RPNSRC ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(RPNINC ${CMAKE_CURRENT_SOURCE_DIR}/include)


add_library(BCT.RPNEvaluator.CPPLib SHARED 
            ${RPNSRC}/FuncOper.cpp 
            ${RPNINC}/FuncOper.h
            ${RPNSRC}/Token.cpp 
            ${RPNINC}/Token.h
            ${RPNSRC}/RPNEvaluator.cpp 
            ${RPNINC}/RPNEvaluator.h 
            ${RPNINC}/TokenClass.h 
            ${RPNINC}/FunctionMap.h 
            ${RPNINC}/RPNResult.h)


target_include_directories(BCT.RPNEvaluator.CPPLib
  PUBLIC ${RPNINC}
  PRIVATE ${CMAKE_SOURCE_DIR}/Bct.Workflow.Aggregates.CPPLib/BCT.Workflow.Util.Cpp/include)


target_link_libraries(BCT.RPNEvaluator.CPPLib)
