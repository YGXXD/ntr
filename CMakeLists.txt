cmake_minimum_required(VERSION 3.20)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(ntr)

add_executable(ntr 
    ${CMAKE_CURRENT_SOURCE_DIR}/src/ntr.cpp 
    ${CMAKE_CURRENT_SOURCE_DIR}/inc/field/nfield.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/inc/field/neitem.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/inc/field/nproperty.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/inc/field/nfunction.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/inc/type/ntype.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/inc/type/nnumeric.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/inc/type/nenum.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/inc/type/nclass.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/inc/nephren.cpp
) 