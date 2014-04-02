#
# This file will help you to integrate a Radon CMake framework based project into your project.
# http://www.radonframework.org/projects/rf/wiki/UserManualCMakeFramework
# http://www.radonframework.org/projects/rf/wiki/DeveloperManualCMakeFramework
#
macro(ConfigureCompilerAndLinkerGCC projectid buildtype)
	if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_COMPILER_IS_GNUCC)
		set(${projectid}_COMPILER_FLAGS "${${projectid}_COMPILER_FLAGS} -Wall -std=c++0x -msse4.2")		
	endif()
endmacro()