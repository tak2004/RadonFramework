#
# This file will help you to integrate a Radon CMake framework based project into your project.
# http://www.radonframework.org/projects/rf/wiki/UserManualCMakeFramework
# http://www.radonframework.org/projects/rf/wiki/DeveloperManualCMakeFramework
#
if (NOT DEFINED ${CMAKE_PROJECT_NAME}_INCLUDED)

cmake_minimum_required(VERSION 2.8)
set(${CMAKE_PROJECT_NAME}_INCLUDED "")
set(${CMAKE_PROJECT_NAME}_INTEGRATED "" CACHE INTERNAL "Integrated projects")

# everything went right :)
macro(FoundProject projectid projectname path)
	STRING(REGEX REPLACE "//" "/" confighook "${path}/cmake/extern/ConfigurationHook.cmake") 	
	if(EXISTS "${confighook}")
		mark_as_advanced(${projectid}_DIR)
		set(${projectid}_FOUND ON)
		mark_as_advanced(${projectid}_FOUND)
		include("${confighook}")	
		ConfigureProject(${projectid} ${path})
	else()
		message(FATAL_ERROR "${projectname} is not made with Radon CMake framework. Can't integrate it.")
	endif()
endmacro()

# everything gone wrong :(
macro(NoProjectFound projectid projectname)
	set(${projectid}_FOUND OFF)
	mark_as_advanced(${projectid}_FOUND)
	message(FATAL_ERROR "Couldn't find or integrate ${projectname}. Please use ${projectid}_DIR to specify the location.")
endmacro()

# first try failed this is the backup
macro(FailSafe projectid projectname)
	if(NOT DEFINED ${projectid}_DIR)
		set(${projectid}_DIR "-NOTFOUND" CACHE PATH "Path to ${projectname} directory.")
	endif()
	if(EXISTS "${${projectid}_DIR}")
		if(NOT IS_ABSOLUTE "${${projectid}_DIR}")
			get_filename_component(absolute_path "${${projectid}_DIR}" ABSOLUTE)
			set(${projectid}_DIR "${absolute_path}" CACHE PATH "Path to ${projectname} directory." FORCE)
			message(STATUS "Convert relative path into a absolute one ${${projectid}_DIR}")
		endif()
		# on windows there are some cases where we have to encounter backslashes
		STRING(REGEX REPLACE "\\\\" "/" ${projectid}_DIR ${${projectid}_DIR}) 	
		FoundProject(${projectid} ${projectname} "${${projectid}_DIR}")
	else()
		NoProjectFound(${projectid} ${projectname})
	endif()
endmacro()

# projectid = will be used as pre-name for all variables
# projectname = will be used as output in the option description
# environmentname = will be used as key for the search in the environment variables
macro(Integrate projectid projectname environmentname)
	# check if initialization order is valid
	if(DEFINED ${projectid}_FOUND AND NOT DEFINED ${projectid}_FINALIZED)
		message(FATAL_ERROR "${projectname} is involved in an circular dependency. Please track the project which call Integrate() for ${projectname} and move it behind Finalize().")
	endif()
	
	if(NOT DEFINED ${projectid}_FOUND)
		option(${projectid}_USE "Include ${projectname} into the project." ON)	
		
		if(${projectid}_USE)
			# does an environment variable exist
			if(WIN32)
				if(EXISTS "$ENV{${environmentname}}/cmake/")
					FoundProject(${projectid} ${projectname} $ENV{${environmentname}})
				else()		
					message(AUTHOR_WARNING "Add user or system environment variable ${environmentname} !")
					FailSafe(${projectid} ${projectname})
				endif()
			else()
				FailSafe(${projectid} ${projectname})
			endif()
		endif()
	endif()
	
	string(REGEX MATCH "${${projectid}_NAME}" match "${${CMAKE_PROJECT_NAME}_INTEGRATED}")
	if ("${match}" STREQUAL "")
		set(${CMAKE_PROJECT_NAME}_INTEGRATED "${${projectid}_NAME} ${${CMAKE_PROJECT_NAME}_INTEGRATED}" CACHE INTERNAL "Integrated projects")	
	endif()	
	include_directories(${${projectid}_PUBLIC_INCLUDES})
endmacro()

endif()