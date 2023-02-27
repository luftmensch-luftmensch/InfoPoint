# Minimum version of CMake required to build this project
cmake_minimum_required(VERSION 3.0 FATAL_ERROR)

#
# FAQS
#
# Define compiler https://gitlab.kitware.com/cmake/community/-/wikis/FAQ#how-do-i-use-a-different-compiler

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

#
# Set project options
#

include(cmake/StandardSettings.cmake)
include(cmake/Utils.cmake)
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE "Debug")
endif()
message(STATUS "Started CMake for ${PROJECT_NAME} v${PROJECT_VERSION}...\n")

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
include(cmake/SourcesAndHeaders.cmake)

## Logging sources & headers file
#verbose_message("Found the following sources:")
verbose_message_info(${sources} ${headers})

add_executable(${PROJECT_EXECUTABLE})
target_sources(${PROJECT_EXECUTABLE} PRIVATE ${sources} ${headers})

include(cmake/CompilerWarnings.cmake)
set_project_warnings(${PROJECT_EXECUTABLE})

include(GNUInstallDirs)
install(TARGETS ${PROJECT_EXECUTABLE})

#
# Target properties
#
#set_target_properties(
#  ${PROJECT_NAME}
#  PROPERTIES
#  ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib/${CMAKE_BUILD_TYPE}"
#  LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib/${CMAKE_BUILD_TYPE}"
#  RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/${CMAKE_BUILD_TYPE}"
#)

message(STATUS "Added all header and implementation files.\n")

#
# Set the project standard and warnings
#

verbose_message("Applied compiler warnings. Using standard ${CMAKE_CXX_STANDARD}.\n")
