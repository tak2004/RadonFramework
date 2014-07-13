cmake_minimum_required(VERSION 2.8.11)
project(RadonFramework)

include("${CMAKE_CURRENT_LIST_DIR}/cmake/util/git.cmake")

OPTION(RADONFRAMEWORK_WITH_VISUALGDB "Generate a VisualGDB target for remote build." OFF)
mark_as_advanced(RADONFRAMEWORK_WITH_VISUALGDB)

OPTION(RADONFRAMEWORK_COMPILER_PRECOMPILED_PIMPL "PImpl template will be included into the precompiled.hpp." ON)
mark_as_advanced(RADONFRAMEWORK_COMPILER_PRECOMPILED_PIMPL)

OPTION(RADONFRAMEWORK_USE_MICROCRT "Radon framework will provide code for running without crt and std functions." OFF)
mark_as_advanced(RADONFRAMEWORK_USE_MICROCRT)

OPTION(RADONFRAMEWORK_USE_OPENGL "Activate OpenGL" ON)

#
# set destination directory for all binaries
#
	set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${RadonFramework_SOURCE_DIR}/dist)
	set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${RadonFramework_SOURCE_DIR}/dist)
	set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${RadonFramework_SOURCE_DIR}/dist)

#
# OS specific includes
#

#	
# OS specific libs
#
	if(WIN32)
			# for socket, IP and DNS api you have to link ws2_32.lib and Iphlpapi.lib
			set(OSLIBS ${OSLIBS} ws2_32 Iphlpapi)
			# for using the process api you have to link psapi.lib
			set(OSLIBS ${OSLIBS} psapi)
	endif(WIN32)

	if(UNIX)
		# for loading a dynamic library you have to link libdl.so
		set(OSLIBS ${OSLIBS} dl rt)
		# for using threads you have to link libpthread.so
		if(PTHREADS_FOUND)
			set(OSLIBS ${OSLIBS} pthread)
		endif()
	endif(UNIX)

#
# setup graphic
#
	#find_package(OpenGL)
	if(RADONFRAMEWORK_USE_OPENGL)
		set(USEOPENGL "#ifndef RF_USE_OPENGL\n#define RF_USE_OPENGL\n#endif")
		if(UNIX)
			set(OSLIBS ${OSLIBS} GL GLU)
			find_package(X11)
			if(X11_FOUND)
				set(USEX11 "#ifndef RF_USE_X11\n#define RF_USE_X11\n#endif")
				set(OSLIBS ${OSLIBS} X11 Xrandr)
				find_path(X11_Xmu_INCLUDE_PATH X11/Xmu/Xmu.h ${X11_INC_SEARCH_PATH})
				find_library(X11_Xmu_LIB Xmu ${X11_LIB_SEARCH_PATH})
				if(X11_Xmu_INCLUDE_PATH AND X11_Xmu_LIB)
					set(X11_Xmu_FOUND TRUE)
					message(STATUS "X11 support: Yes")
				endif(X11_Xmu_INCLUDE_PATH AND X11_Xmu_LIB)
			endif(X11_FOUND)
		endif(UNIX)
		
		if(WIN32)
            set(USEGDI "#ifndef RF_USE_GDI\n#define RF_USE_GDI\n#endif")
			set(OSLIBS ${OSLIBS} OpenGL32)
			message(STATUS "GDI support: Yes")
		endif(WIN32)
		
		include_directories(${OPENGL_INCLUDE_DIR})
		add_definitions(-DGLEW_STATIC)    
		message(STATUS "OpenGL support: Yes")
	else(RADONFRAMEWORK_USE_OPENGL)
		message(STATUS "OpenGL support: No")
	endif(RADONFRAMEWORK_USE_OPENGL)

find_package(Doxygen)
if (DOXYGEN_FOUND)
    add_subdirectory(doxygen)
    message(STATUS "Doxygen found: Documentation could generate.")
else()
    message(STATUS "Doxygen wasn't found: Documentation couldn't generate.")
endif()

link_directories(${RadonFramework_BINARY_DIR}/dist/)

include("cmake/util/Macros.cmake")
include(libRadonFramework.cmake)
include("${CMAKE_CURRENT_LIST_DIR}/cmake/extern/Generate.cmake")
Generate(MODULE RADONFRAMEWORK RadonFramework "Framework")

AddPublicInclude(RADONFRAMEWORK ${RadonFramework_SOURCE_DIR}/include/)
target_include_directories(RadonFramework PRIVATE ${RadonFramework_SOURCE_DIR}/include/RadonFramework/backend/)
target_include_directories(RadonFramework PRIVATE ${RadonFramework_SOURCE_DIR}/include/RadonFramework/backend/uripp/)

Finalize(RADONFRAMEWORK)

#
# generate config file
#
if(${RADONFRAMEWORK_COMPILER_PRECOMPILED_PIMPL})
	set(RADONFRAMEWORK_PRECOMPILED_PIMPL "#ifndef RF_PRECOMPILED_PIMPL\n    #define RF_PRECOMPILED_PIMPL 1\n#endif")
else()
	set(RADONFRAMEWORK_PRECOMPILED_PIMPL "")
endif()

if(${RADONFRAMEWORK_USE_MICROCRT})
	set(RADONFRAMEWORK_MICROCRT "#ifndef RF_MICROCRT\n    #define RF_MICROCRT 1\n#endif")
else()
	set(RADONFRAMEWORK_MICROCRT "")
endif()

GIT_GET_REVISION(${RadonFramework_SOURCE_DIR} ProjectRevision)
set(RADONFRAMEWORK_MAJORNUMBER "0")
set(RADONFRAMEWORK_MINORNUMBER "3")
set(RADONFRAMEWORK_REVISIONNUMBER "${ProjectRevision}")
if (NOT DEFINED RADONFRAMEWORK_BUILDNUMBER )
	set(RADONFRAMEWORK_BUILDNUMBER "0")
endif ()

message(STATUS "Generate ${RadonFramework_SOURCE_DIR}/include/RadonFramework/Defines.hpp")
configure_file("${RadonFramework_SOURCE_DIR}/include/RadonFramework/Defines.hxx" "${RadonFramework_SOURCE_DIR}/include/RadonFramework/Defines.hpp" @ONLY)
message(STATUS "Generate ${RadonFramework_SOURCE_DIR}/src/System/CompilerConfig.cpp")
configure_file("${RadonFramework_SOURCE_DIR}/src/System/CompilerConfig.cxx" "${RadonFramework_SOURCE_DIR}/src/System/CompilerConfig.cpp" @ONLY)

#
# radon framework modules
#
option(RADONFRAMEWORK_USE_MODULES "This option will include all modules in the specified directory to be compiled into the Radon Framework." Off)
if(RADONFRAMEWORK_USE_MODULES)
	set(RADONFRAMEWORK_MODULES_DIR CACHE PATH "Path to where the modules of Radon Framework are located.")
	if(RADONFRAMEWORK_MODULES_DIR)
		include("${RADONFRAMEWORK_MODULES_DIR}/CMakeLists.txt")
	else()
		message(FATAL_ERROR "Please specify with RADONFRAMEWORK_MODULES_DIR the location of the modules directory.")
	endif()
endif()

add_subdirectory(tests/SystemTest)
add_subdirectory(tests/UnitTest)
add_subdirectory(tests/ResourceTest)

#
#
#	
install(DIRECTORY ${RadonFramework_SOURCE_DIR}/include/RadonFramework 
		DESTINATION "include" 
		FILES_MATCHING PATTERN "*" PATTERN ".svn" EXCLUDE)
install(TARGETS RadonFramework
		EXPORT RadonFramework
		LIBRARY DESTINATION lib
		ARCHIVE DESTINATION lib)
install(EXPORT RadonFramework
		DESTINATION .
		FILE RadonFrameworkDependencies.cmake)

#
#
#
if(RADONFRAMEWORK_WITH_VISUALGDB)
	include(libRadonFramework_VGDB.cmake)
endif()