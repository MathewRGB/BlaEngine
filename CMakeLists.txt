cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

project(BlaEngine VERSION 0.0.0)

#-------------------------------------------------------------------------------
# Required preconditions
#-------------------------------------------------------------------------------
#
file(TO_CMAKE_PATH "${PROJECT_BINARY_DIR}/CMakeLists.txt" LOC_PATH)
if(EXISTS "${LOC_PATH}")
    message(FATAL_ERROR "You cannot build in a source directory (or any directory with a CMakeLists.txt file).\
        Please make a build subdirectory. Feel free to remove CMakeCache.txt and CMakeFiles.")
endif()

#-------------------------------------------------------------------------------
# CMAKE Options
#-------------------------------------------------------------------------------
#
if(NOT ${CMAKE_SYSTEM_PROCESSOR} MATCHES "x86_64")
    message(WARNING "No different architecture than x86_64 are currently supported.")
endif()

if (NOT ${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    message(WARNING "No cross-compiling supported yet (only Linux).")
endif()

message(STATUS "System: ${CMAKE_SYSTEM_NAME}" )
message(STATUS "Processor: ${CMAKE_SYSTEM_PROCESSOR}" )

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
list(APPEND CMAKE_MODULE_PATH "/usr/local/lib/cmake")

#-------------------------------------------------------------------------------
# Compiler options
#-------------------------------------------------------------------------------
#
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED YES)

set(GENERAL_COMPILER_FLAGS "\
-pedantic \
-Wall \
-Wextra \
-Wredundant-decls \
-Wcast-align \
-Wmissing-declarations \
-Wmissing-include-dirs \
-Wswitch-enum \
-Wswitch-default \
-Winvalid-pch \
-Wredundant-decls \
-Wformat=2 \
-Wmissing-format-attribute \
-Wformat-nonliteral \
-std=c++17")

set(CMAKE_CXX_FLAGS_DEBUG "\
-g \
-O0 \
-ansi \
${GENERAL_COMPILER_FLAGS} \
-DVERBOSE \
-DDEBUG")

set(CMAKE_CXX_FLAGS_RELEASE "\
-g \
-O3 \
-ansi \
-Werror \
${GENERAL_COMPILER_FLAGS} \
-DNDEBUG")

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG}")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE}") 

find_package(GTest REQUIRED)

include_directories(${GTEST_INCLUDE_DIRS})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include/)
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

#-------------------------------------------------------------------------------
# BLAENGINE system version information
#-------------------------------------------------------------------------------
#
# Get the current working branch
execute_process(
    COMMAND git rev-parse --abbrev-ref HEAD
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    OUTPUT_VARIABLE GIT_BRANCH
    OUTPUT_STRIP_TRAILING_WHITESPACE
  )
  
# Get the latest abbreviated commit hash of the working branch
execute_process(
    COMMAND git log -1 --format=%h
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    OUTPUT_VARIABLE GIT_COMMIT_HASH
    OUTPUT_STRIP_TRAILING_WHITESPACE)

add_definitions(-DBLAENGINE_BUILD_COMMIT_STRING="${GIT_COMMIT_HASH}")
add_definitions(-D_PROJECT_VERSION="${CMAKE_PROJECT_VERSION}")

#-------------------------------------------------------------------------------
# Output targets
#-------------------------------------------------------------------------------
#
add_library(libblaengine SHARED
    source/blaengine.cpp
    source/communication/uci.cpp
    source/calculation/calculator.cpp
    source/calculation/game_state_controller.cpp
    source/calculation/move_generator.cpp)

target_link_libraries(libblaengine
    ${GTEST_LIBRARIES}
    pthread)

set_target_properties(libblaengine
    PROPERTIES SUFFIX ".so")

add_executable(BlaEngine
    source/main.cpp)

target_link_libraries(BlaEngine 
    libblaengine)

#-------------------------------------------------------------------------------
# Documentation build
#-------------------------------------------------------------------------------
#
find_package (Doxygen)
option(BUILD_DOCUMENTATION "Create and install the HTML based \
API documentation (requires Doxygen)" ${DOXYGEN_FOUND})

if(BUILD_DOCUMENTATION)
    if(NOT DOXYGEN_FOUND)
        message(FATAL_ERROR "Doxygen is needed to build the documentation.")
    endif()

    set(doxyfile_in ${CMAKE_CURRENT_SOURCE_DIR}/docs/Doxyfile.in)
    set(doxyfile ${CMAKE_CURRENT_BINARY_DIR}/docs/Doxyfile)

    configure_file(${doxyfile_in} ${doxyfile} @ONLY)

    add_custom_target(doc
        COMMAND ${DOXYGEN_EXECUTABLE} ${doxyfile}
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        COMMENT "Generating API documentation with Doxygen"
        VERBATIM)

    install(DIRECTORY ${CMAKE_SOURCE_DIR}/docs/html DESTINATION share/doc)
endif(BUILD_DOCUMENTATION)

#-------------------------------------------------------------------------------
# Unit Tests
#-------------------------------------------------------------------------------
#
if(CMAKE_BUILD_TYPE MATCHES "^(Release)$")
    message(STATUS "Release mode no tests compiled!")
    return()
endif()

# Locate GTest
message(STATUS "Debug mode tests will be compiled!")
enable_testing()
 
# Link runTests with what we want to test and the GTest and pthread library
add_executable(runTests
    tests/test_main.cpp)

target_link_libraries(runTests 
    libblaengine 
    ${GTEST_LIBRARIES} 
    pthread)

add_test(main_tests runTests)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/tests/mock_data
     DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
