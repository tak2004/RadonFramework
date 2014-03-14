#
# This file will help you to integrate a Radon CMake framework based project into your project.
# http://www.radonframework.org/projects/rf/wiki/UserManualCMakeFramework
# http://www.radonframework.org/projects/rf/wiki/DeveloperManualCMakeFramework
#
# It will be included by cmake/extern/Integrate.cmake 
# and move most of the configuration into Radon CMake framework scope.
#
macro(ConfigureProject projectid path)
	set(${projectid}_LOCATION "${path}")
	set(${projectid}_PUBLIC_INCLUDES "" CACHE INTERNAL "include directories")
	if ((DEFINED ${projectid}_FINALIZED AND NOT ${${projectid}_FINALIZED}) OR
		NOT DEFINED ${projectid}_FINALIZED)
		add_subdirectory(${${projectid}_LOCATION} "${PROJECT_BINARY_DIR}/${projectid}/")
	endif()
endmacro()