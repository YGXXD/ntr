cmake_minimum_required(VERSION 3.20)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(ntr_test)

file(GLOB_RECURSE NTR_SOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)
add_library(ntr SHARED ${NTR_SOURCE_FILES})

add_executable(ntr_test 
    ${CMAKE_CURRENT_SOURCE_DIR}/test/ntr.cpp 
) 

target_link_libraries(ntr_test PRIVATE ntr)