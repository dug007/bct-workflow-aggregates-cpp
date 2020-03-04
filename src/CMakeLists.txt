cmake_minimum_required(VERSION 3.0.0)
project(Bct.Workflow.Aggregates.CPP.Test)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_subdirectory(Bct.Workflow.Aggregates.CPPLib)

add_subdirectory(Bct.Workflow.Aggregates.CPP.GeneratedCode)

enable_testing()

add_subdirectory(Bct.Workflow.Aggregates.CPP.Test)




