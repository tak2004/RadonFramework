#
# This file will help you to integrate a Radon CMake framework based project into your project.
# http://www.radonframework.org/projects/rf/wiki/UserManualCMakeFramework
# http://www.radonframework.org/projects/rf/wiki/DeveloperManualCMakeFramework
#
if (RCF_INCLUDED)
    return()
endif()

set(RCF_INCLUDED true)
set(RCF_INTEGRATED "" CACHE INTERNAL "Integrated projects")

find_package(Git REQUIRED)
set(repo "https://github.com/tak2004/RadonCMakeFramework.git")
set(outdir "${PROJECT_BINARY_DIR}/DownloadedDependencies/RadonCMakeFramework")
if(NOT EXISTS ${outdir})
	message(STATUS "Download ${repo} into ${outdir}")
	execute_process(COMMAND "${GIT_EXECUTABLE}" "clone" "${repo}" "${outdir}")
endif()
include("${outdir}/extern/ConfigurationHook.cmake")
include("${outdir}/extern/Generate.cmake")