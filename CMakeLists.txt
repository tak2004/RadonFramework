# Define a project if this file wasn't included.
if(NOT CMAKE_PROJECT_NAME OR "${CMAKE_PROJECT_NAME}" MATCHES "^RadonFramework$")
    cmake_minimum_required(VERSION 2.8.11)
    project(RadonFramework)
    set(RADONFRAMEWORK_LOCATION ${CMAKE_SOURCE_DIR})
    set(RADONFRAMEWORK_ADD_TESTS OFF CACHE BOOL "" FORCE)
    set(RADONFRAMEWORK_ADD_DOCUMENTATION ON CACHE BOOL "" FORCE)
endif()

# Add additional CMake macros and functions.
INCLUDE(CheckFunctionExists)
include("Integrate.cmake")

# General framework options.
OPTION(RADONFRAMEWORK_ADD_DOCUMENTATION "Add the framework documentation generation to the build." OFF)
OPTION(RADONFRAMEWORK_ADD_TESTS "Add the framework specific tests." OFF)
OPTION(RADONFRAMEWORK_ADD_EXAMPLES "Add the framework examples." OFF)
OPTION(RADONFRAMEWORK_ADD_XXHASH "Add the xxhash library and services." ON)

# Advanced framework options.
OPTION(RADONFRAMEWORK_ENABLE_EXPERIMENTAL_CODE "Enable code which is still in development." OFF)
mark_as_advanced(RADONFRAMEWORK_ENABLE_EXPERIMENTAL_CODE)
OPTION(RADONFRAMEWORK_USE_MICROCRT "Radon framework will provide code for running without crt and std functions." OFF)
mark_as_advanced(RADONFRAMEWORK_USE_MICROCRT)
if(RADONFRAMEWORK_ADD_TESTS)
    rcf_addpackage(rf_test)
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
if(NOT CMAKE_PROJECT_NAME OR "${CMAKE_PROJECT_NAME}" MATCHES "^RadonFramework$")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${RADONFRAMEWORK_LOCATION}/dist CACHE PATH
   "Single Directory for all Libraries")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${RADONFRAMEWORK_LOCATION}/dist CACHE PATH
   "Single Directory for all Libraries")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${RADONFRAMEWORK_LOCATION}/dist CACHE PATH
   "Single Directory for all Libraries")
FOREACH(i IN LISTS CMAKE_CONFIGURATION_TYPES ITEMS ${CMAKE_BUILD_TYPE})
    STRING(TOUPPER ${i} j)
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_${j} ${RADONFRAMEWORK_LOCATION}/dist CACHE PATH
        "Single Directory for all Libraries")
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_${j} ${RADONFRAMEWORK_LOCATION}/dist CACHE PATH
        "Single Directory for all Libraries")
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_${j} ${RADONFRAMEWORK_LOCATION}/dist CACHE PATH
        "Single Directory for all Libraries")
ENDFOREACH()   
link_directories(${RadonFramework_BINARY_DIR}/dist/)
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

rcf_generate(MODULE RADONFRAMEWORK RadonFramework "Framework")
AddPublicInclude(RADONFRAMEWORK ${RADONFRAMEWORK_LOCATION}/include/)
target_include_directories(RadonFramework PRIVATE ${RADONFRAMEWORK_LOCATION}/include/RadonFramework/backend/)
target_include_directories(RadonFramework PRIVATE ${RADONFRAMEWORK_LOCATION}/include/RadonFramework/backend/uripp/)
if(RADONFRAMEWORK_ADD_XXHASH)
    AddPublicDefine(RADONFRAMEWORK RF_USE_XXHASH)
    rcf_dependencies(xxHash_Static)
endif()
    rcf_dependencies(${RADONFRAMEWORK_MODULES})
rcf_endgenerate()

if(RADONFRAMEWORK_BUILD_UNITTEST)
	add_subdirectory(tests/UnitTest)
endif()
if(RADONFRAMEWORK_BUILD_SYSTEMTEST)
	add_subdirectory(tests/SystemTest)
endif()
if(RADONFRAMEWORK_BUILD_RESOURCETEST)
	add_subdirectory(tests/ResourceTest)
endif()