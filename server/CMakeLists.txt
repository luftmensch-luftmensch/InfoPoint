# Minimum version of CMake required to build this project
cmake_minimum_required(VERSION 3.0 FATAL_ERROR)

#
# FAQS
#
# Define compiler https://gitlab.kitware.com/cmake/community/-/wikis/FAQ#how-do-i-use-a-different-compiler


# In order to generate the compile_commands.json to make clangd able to find mongoc lib:
# 1. cmake -S . -B build/  -DCMAKE_EXPORT_COMPILE_COMMANDS=1
# 2. In the build folder run
#   1. make clean
#   2. bear -- make
# 3. cmake --build build
# DONE!

#
# Project details
#

project("SERVER"
    LANGUAGES C
    VERSION 1.0
    DESCRIPTION "InfoPoint server w/ C"
    HOMEPAGE_URL "https://github.com/lufthmensch-luftmensch/InfoPoint")

# If enabled, generates a compile_commands.json file containing the exact compiler calls for all translation units of the project in machine-readable form
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_C_STANDARD 17)


include(cmake/StandardSettings.cmake)
include(cmake/Utils.cmake)
include(cmake/SourcesAndHeaders.cmake)
include(cmake/CompilerBuildFlags.cmake)
include(cmake/Colors.cmake)
include(GNUInstallDirs)

#
# Set project options
#
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE "Debug")
endif()
message(STATUS "${magenta} Started CMake for ${PROJECT_NAME} v${PROJECT_VERSION}...${reset}\n")

if (UNIX)
    add_compile_options("$<$<CONFIG:DEBUG>:-D_DEBUG>")    #this will allow to use same _DEBUG macro available in both Linux as well as Windows - MSCV environment. Easy to put Debug specific code.
endif (UNIX)

#
# Prevent building in the source directory
#
if(PROJECT_SOURCE_DIR STREQUAL PROJECT_BINARY_DIR)
  message(FATAL_ERROR "In-source builds not allowed. Please make a new directory (called a build directory) and run CMake from there.\n")
endif()


#
# Create library, setup header and source files
#

# Find all headers and implementation files

## Logging sources & headers file
message("${green}Found the following sources: ${reset}")
foreach(source ${sources})
  message(STATUS "* ${blue} ${source} ${reset}")
endforeach()

message("\n${green}Found the following headers: ${reset}")
foreach(header ${headers})
  message(STATUS "* ${blue} ${header} ${reset}")
endforeach()

add_executable(${PROJECT_EXECUTABLE})

#
# Database setup
#


# Find driver needed for mongodb connection
find_package(mongoc-1.0 1.7 REQUIRED)
target_link_libraries(${PROJECT_EXECUTABLE} PRIVATE mongo::mongoc_shared)


target_sources(${PROJECT_EXECUTABLE} PRIVATE ${sources} ${headers})

#
# Set the project standard and warnings
#
message("\nApplied compiler warnings. Using standard ${CMAKE_C_STANDARD}.\n")

set_project_build_flags(${PROJECT_EXECUTABLE})

install(TARGETS ${PROJECT_EXECUTABLE})

message(STATUS "Added all header and implementation files.\n")
