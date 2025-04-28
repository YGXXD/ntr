cmake_minimum_required(VERSION 3.20)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(ntr)

file(GLOB_RECURSE NTR_SOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)

add_library(ntr STATIC ${NTR_SOURCE_FILES})
target_include_directories(ntr PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/inc>
    $<INSTALL_INTERFACE:include>
)

install(DIRECTORY inc/ DESTINATION include/ntr)
install(TARGETS ntr
    EXPORT ntr-targets
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    RUNTIME DESTINATION bin
    INCLUDES DESTINATION include
)
install(EXPORT ntr-targets
    NAMESPACE ntr::
    DESTINATION lib/cmake/ntr
)

include(CMakePackageConfigHelpers)
configure_package_config_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/cmake/ntr-config.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/ntr-config.cmake
    INSTALL_DESTINATION lib/cmake/ntr
)
install(FILES
    ${CMAKE_CURRENT_BINARY_DIR}/ntr-config.cmake
    DESTINATION lib/cmake/ntr
)

if(NOT TARGET uninstall)
    configure_file(
        "${CMAKE_CURRENT_SOURCE_DIR}/cmake/cmake_uninstall.cmake.in"
        "${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake"
        IMMEDIATE @ONLY)

    add_custom_target(uninstall
        COMMAND ${CMAKE_COMMAND} -P ${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake)
endif()