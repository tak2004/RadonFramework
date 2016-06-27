# Define a project if this file wasn't included.
if(NOT CMAKE_PROJECT_NAME OR "${CMAKE_PROJECT_NAME}" MATCHES "^RadonFramework$")
    cmake_minimum_required(VERSION 2.8.11)
    project(RadonFramework C CXX)
    set(RADONFRAMEWORK_LOCATION ${CMAKE_SOURCE_DIR})
    set(RADONFRAMEWORK_ADD_TESTS ON CACHE BOOL "" FORCE)
    set(RADONFRAMEWORK_ADD_DOCUMENTATION ON CACHE BOOL "" FORCE)
    endif()

# Add additional CMake macros and functions.
INCLUDE (CheckFunctionExists)
include("Integrate.cmake")

# General framework options.
OPTION(RADONFRAMEWORK_ADD_DOCUMENTATION "Add the framework documentation generation to the build." OFF)
OPTION(RADONFRAMEWORK_ADD_TESTS "Add the framework specific tests." OFF)
OPTION(RADONFRAMEWORK_USE_OPENGL "Activate OpenGL canvas support" ON)

# Advanced framework options.
OPTION(RADONFRAMEWORK_ENABLE_EXPERIMENTAL_CODE "Enable code which is still in development." OFF)
mark_as_advanced(RADONFRAMEWORK_ENABLE_EXPERIMENTAL_CODE)
OPTION(RADONFRAMEWORK_WITH_VISUALGDB "Generate a VisualGDB target for remote build." OFF)
mark_as_advanced(RADONFRAMEWORK_WITH_VISUALGDB)
OPTION(RADONFRAMEWORK_USE_MICROCRT "Radon framework will provide code for running without crt and std functions." OFF)
mark_as_advanced(RADONFRAMEWORK_USE_MICROCRT)
if(RADONFRAMEWORK_ADD_TESTS)
    OPTION(RADONFRAMEWORK_BUILD_UNITTEST "Enable the unit test" ON)
    mark_as_advanced(RADONFRAMEWORK_BUILD_UNITTEST)
    OPTION(RADONFRAMEWORK_BUILD_RESOURCETEST "Enable the resource test" ON)
    mark_as_advanced(RADONFRAMEWORK_BUILD_RESOURCETEST)
    OPTION(RADONFRAMEWORK_BUILD_SYSTEMTEST "Enable the system test" ON)
    mark_as_advanced(RADONFRAMEWORK_BUILD_SYSTEMTEST)
endif()

# Radon version
GIT_GET_REVISION(${RADONFRAMEWORK_LOCATION} ProjectRevision)
set(RADONFRAMEWORK_MAJORNUMBER "0")
set(RADONFRAMEWORK_MINORNUMBER "4")
set(RADONFRAMEWORK_REVISIONNUMBER "${ProjectRevision}")
set(RADONFRAMEWORK_BUILDNUMBER "0")

# Set default destination directory for all binaries.
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${RADONFRAMEWORK_LOCATION}/dist)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${RADONFRAMEWORK_LOCATION}/dist)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${RADONFRAMEWORK_LOCATION}/dist)
link_directories(${RadonFramework_BINARY_DIR}/dist/)

if(RADONFRAMEWORK_USE_OPENGL)
    include(build/cmake/OpenGL.cmake)
endif()

if(RADONFRAMEWORK_ADD_DOCUMENTATION)
    find_package(Doxygen)
    if (DOXYGEN_FOUND)
        add_subdirectory(doxygen)
    endif()
endif()

# Experimental code could need additional 3rd party code.
# Check and add experimental code.
include(build/cmake/Experimental.cmake)
# Check and add 3rd party code.
include(build/cmake/3rdParty.cmake)
# Do platform specific logic.
include(build/cmake/Build.cmake)
# Code generation.
include(build/code_templates/CMakeLists.txt)
# Include radon framework files
include(libRadonFramework.cmake)

Generate(MODULE RADONFRAMEWORK RadonFramework "Framework")
AddPublicInclude(RADONFRAMEWORK ${RADONFRAMEWORK_LOCATION}/include/)
target_include_directories(RadonFramework PRIVATE ${RADONFRAMEWORK_LOCATION}/include/RadonFramework/backend/)
target_include_directories(RadonFramework PRIVATE ${RADONFRAMEWORK_LOCATION}/include/RadonFramework/backend/uripp/)
Finalize(RADONFRAMEWORK)

if(RADONFRAMEWORK_BUILD_UNITTEST)
	add_subdirectory(tests/UnitTest)
endif()
if(RADONFRAMEWORK_BUILD_SYSTEMTEST)
	add_subdirectory(tests/SystemTest)
endif()
if(RADONFRAMEWORK_BUILD_RESOURCETEST)
	add_subdirectory(tests/ResourceTest)
endif()