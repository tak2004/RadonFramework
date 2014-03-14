#
# This file will help you to integrate a Radon CMake framework based project into your project.
# http://www.radonframework.org/projects/rf/wiki/UserManualCMakeFramework
# http://www.radonframework.org/projects/rf/wiki/DeveloperManualCMakeFramework
#
macro(ConfigureCompilerAndLinkerGCC projectid buildtype)
	if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_COMPILER_IS_GNUCC)
		SET(CMAKE_BUILD_TYPE Release)
		SET(CMAKE_CXX_FLAGS_RELEASE "-Wall -s -O2")
		SET(CMAKE_C_FLAGS_RELEASE "-Wall -s -O2")

		SET(CMAKE_BUILD_TYPE MinSizeRel)
		SET(CMAKE_CXX_FLAGS_MINSIZEREL "-Wall -s -O1")
		SET(CMAKE_C_FLAGS_MINSIZEREL "-Wall -s -O1")

		SET(CMAKE_BUILD_TYPE RelWithDebInfo)
		SET(CMAKE_CXX_FLAGS_RELWITHDEBINFO "-Wall -O2")
		SET(CMAKE_C_FLAGS_RELWITHDEBINFO "-Wall -O2")

		SET(CMAKE_BUILD_TYPE Debug)
		SET(CMAKE_CXX_FLAGS_DEBUG "-Wall -g")
		SET(CMAKE_C_FLAGS_DEBUG "-Wall -g")
	endif()
endmacro()