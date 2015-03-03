#
# This file will help you to integrate a Radon CMake framework based project into your project.
# http://www.radonframework.org/projects/rf/wiki/UserManualCMakeFramework
# http://www.radonframework.org/projects/rf/wiki/DeveloperManualCMakeFramework
#
if (NOT DEFINED ${CMAKE_PROJECT_NAME}_INCLUDED)

cmake_minimum_required(VERSION 2.8)
set(${CMAKE_PROJECT_NAME}_INCLUDED "")
set(${CMAKE_PROJECT_NAME}_INTEGRATED "" CACHE INTERNAL "Integrated projects")

macro(InitializeRadonCMakeFramework)
	find_package(Git)
	if (GIT_FOUND)
		set("${CMAKE_PROJECT_NAME}_REPOTYPEMAP_git" "${GIT_EXECUTABLE}")
		set("${CMAKE_PROJECT_NAME}_REPOTYPEMAP_git_get" "clone")
		mark_as_advanced(GIT_EXECUTABLE)
	endif()
	
	find_package(Subversion)
	if (SUBVERSION_FOUND)
		set("${CMAKE_PROJECT_NAME}_REPOTYPEMAP_svn" "${Subversion_SVN_EXECUTABLE}")
		set("${CMAKE_PROJECT_NAME}_REPOTYPEMAP_svn_get" "co")
		mark_as_advanced(Subversion_SVN_EXECUTABLE)
	endif()	
	
endmacro()

macro(GeneratePath targetdir variable)
	SET(${variable} "${PROJECT_BINARY_DIR}/RadonCMakeFramework_DownloadedDependencies/${targetdir}")
endmacro()

macro(GetRepo repo type targetdir)
	if (DEFINED ${CMAKE_PROJECT_NAME}_REPOTYPEMAP_${type})		
		message(STATUS "Download ${repo}")
		GeneratePath(${targetdir} outdir)
		EXECUTE_PROCESS(COMMAND "${${CMAKE_PROJECT_NAME}_REPOTYPEMAP_${type}}" "${${CMAKE_PROJECT_NAME}_REPOTYPEMAP_${type}_get}" "${repo}" "${outdir}")
	endif()
endmacro()

macro(GetRadonCMakeFramework)
	if (NOT DEFINED ${CMAKE_PROJECT_NAME}_OVERIDE_INTEGRATION_REPO)
		set(${CMAKE_PROJECT_NAME}_OVERIDE_INTEGRATION_REPO "https://github.com/tak2004/RadonCMakeFramework.git")
	endif()
	if (NOT DEFINED ${CMAKE_PROJECT_NAME}_OVERIDE_INTEGRATION_REPOTYPE)
		set(${CMAKE_PROJECT_NAME}_OVERIDE_INTEGRATION_REPOTYPE "git")
	endif()
	
	GetRepo(${${CMAKE_PROJECT_NAME}_OVERIDE_INTEGRATION_REPO} ${${CMAKE_PROJECT_NAME}_OVERIDE_INTEGRATION_REPOTYPE} "RadonCMakeFramework")
endmacro()

macro(SetupRadonCMakeFramework)
	GeneratePath("RadonCMakeFramework" outdir)
	include("${outdir}/extern/ConfigurationHook.cmake")
	include("${outdir}/extern/Generate.cmake")
endmacro()

# Initialize and load RadonCMakeFramework
InitializeRadonCMakeFramework()
GetRadonCMakeFramework()
SetupRadonCMakeFramework()

endif()