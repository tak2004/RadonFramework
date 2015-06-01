#
# This file will help you to integrate a Radon CMake framework based project into your project.
# http://www.radonframework.org/projects/rf/wiki/UserManualCMakeFramework
# http://www.radonframework.org/projects/rf/wiki/DeveloperManualCMakeFramework
#
if (NOT DEFINED ${CMAKE_PROJECT_NAME}_INCLUDED)

cmake_minimum_required(VERSION 2.8)
set(${CMAKE_PROJECT_NAME}_INCLUDED "")
set(${CMAKE_PROJECT_NAME}_INTEGRATED "" CACHE INTERNAL "Integrated projects")

find_package(Git REQUIRED)
set(repo "https://github.com/tak2004/RadonCMakeFramework.git")
set(outdir "${PROJECT_BINARY_DIR}/DownloadedDependencies/RadonCMakeFramework")
if(NOT EXISTS ${outdir})
	message(STATUS "Download ${repo} into ${outdir}")
	execute_process(COMMAND "${GIT_EXECUTABLE}" "clone" "${repo}" "${outdir}")
endif()
include("${outdir}/extern/ConfigurationHook.cmake")
include("${outdir}/extern/Generate.cmake")

endif()