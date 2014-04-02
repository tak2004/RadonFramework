#
# This file will help you to integrate a Radon CMake framework based project into your project.
# http://www.radonframework.org/projects/rf/wiki/UserManualCMakeFramework
# http://www.radonframework.org/projects/rf/wiki/DeveloperManualCMakeFramework
#

# Obtain Radon CMake framework root path to call the other scripts from there.
# At this point the projectid is not set yet but the name of the cmake project
# is available and all macros called in it's scope. 
set(${CMAKE_PROJECT_NAME}_PATH "${CMAKE_CURRENT_LIST_DIR}/../..")
# The following includes are the only exception where an other variable than
# ${${projectid}_LOCATION} is used to access files of the framework.
include("${${CMAKE_PROJECT_NAME}_PATH}/cmake/util/Macros.cmake")
include("${${CMAKE_PROJECT_NAME}_PATH}/cmake/extern/Integrate.cmake")

macro(GenerateModule projectid)
	add_library(${${projectid}_NAME} STATIC ${${projectid}_FILES})
	target_link_libraries(${${projectid}_NAME} ${${projectid}_LIBS})
	set(${projectid}_ISMODULE ON CACHE INTERNAL "Project is a module.")
endmacro()

macro(GenerateSharedLibrary projectid)
	add_library(${${projectid}_NAME} SHARED ${${projectid}_FILES})
	target_link_libraries(${${projectid}_NAME} ${${projectid}_LIBS})
	set(${projectid}_ISLIBRARY ON CACHE INTERNAL "Project is a shared library.")
endmacro()

macro(GenerateExecutable projectid)
	add_executable(${${projectid}_NAME} ${${projectid}_FILES})
	target_link_libraries(${${projectid}_NAME} ${${projectid}_LIBS})
	set(${projectid}_ISEXECUTABLE ON CACHE INTERNAL "Project is an executable.")
endmacro()

macro(Generate what projectid projectname foldergroup)
	set(${projectid}_LOCATION "${${CMAKE_PROJECT_NAME}_PATH}")
	include("${${projectid}_LOCATION}/cmake/intern/CompilerAndLinkerSettings.cmake")	
	
	# Activate solution directory feature
	set_property(GLOBAL PROPERTY USE_FOLDERS ON)

	set(${projectname}_ID ${projectid} CACHE INTERNAL "Projectid of ${projectname}")
	set(${projectid}_NAME ${projectname} CACHE INTERNAL "Projectname of ${projectid}")
	# binary output get D as postfix
	set(CMAKE_DEBUG_POSTFIX D)	
	
	if(${what} STREQUAL "MODULE")
		GenerateModule(${projectid})
	elseif(${what} STREQUAL "SHARED")
		GenerateSharedLibrary(${projectid})
	else()
		GenerateExecutable(${projectid})
	endif()	
	
	ConfigureCompilerAndLinker(${projectid} ${what})
	set_property(TARGET ${projectname} PROPERTY FOLDER ${foldergroup})
endmacro()

macro(Finalize projectid)
	include("${${projectid}_LOCATION}/cmake/intern/CompilerAndLinkerSettings.cmake")
	FinalizeCompilerAndLinkerSettings(${projectid})
	# Remove all spaces, tabs, return and carriage return at the beginning of the string.
	string(REGEX REPLACE "^[ \t\r\n]+" "" deps "${${CMAKE_PROJECT_NAME}_INTEGRATED}")
	# Remove all spaces, tabs, return and carriage return at the end of the string.
	string(REGEX REPLACE "[ \t\r\n]+$" "" deps "${${CMAKE_PROJECT_NAME}_INTEGRATED}")
	message(STATUS "Finalized project: ${${projectid}_NAME} Depends on: ${deps}")	
	add_dependencies(${${projectid}_NAME} "${deps}")
	foreach(dep ${deps})
		if(DEFINED ${${dep}_ID}_ISLIBRARY OR DEFINED ${${dep}_ID}_ISMODULE)
			target_link_libraries(${${projectid}_NAME} ${dep})
		endif()
	endforeach()
	set(${projectid}_FINALIZED ON)
endmacro()