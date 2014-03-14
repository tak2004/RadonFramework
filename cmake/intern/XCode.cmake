#
# This file will help you to integrate a Radon CMake framework based project into your project.
# http://www.radonframework.org/projects/rf/wiki/UserManualCMakeFramework
# http://www.radonframework.org/projects/rf/wiki/DeveloperManualCMakeFramework
#
macro(ConfigureCompilerAndLinkerXCode projectid buildtype)
	if(CMAKE_GENERATOR STREQUAL Xcode)
		set(${projectid}_COMPILER_FLAGS "${${projectid}_COMPILER_FLAGS} -msse4.2")		
	endif()
endmacro()