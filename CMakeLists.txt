cmake_minimum_required(VERSION 2.8.11)
project(RadonFramework)
INCLUDE (CheckFunctionExists)

include("Integrate.cmake")

OPTION(RADONFRAMEWORK_WITH_VISUALGDB "Generate a VisualGDB target for remote build." OFF)
mark_as_advanced(RADONFRAMEWORK_WITH_VISUALGDB)

OPTION(RADONFRAMEWORK_COMPILER_PRECOMPILED_PIMPL "PImpl template will be included into the precompiled.hpp." ON)
mark_as_advanced(RADONFRAMEWORK_COMPILER_PRECOMPILED_PIMPL)

OPTION(RADONFRAMEWORK_USE_MICROCRT "Radon framework will provide code for running without crt and std functions." OFF)
mark_as_advanced(RADONFRAMEWORK_USE_MICROCRT)

OPTION(RADONFRAMEWORK_BUILD_UNITTEST "Enable the unit test" ON)
OPTION(RADONFRAMEWORK_BUILD_RESOURCETEST "Enable the resource test" ON)
OPTION(RADONFRAMEWORK_BUILD_SYSTEMTEST "Enable the system test" ON)

OPTION(RADONFRAMEWORK_USE_OPENGL "Activate OpenGL" ON)

#
# set destination directory for all binaries
#
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${RadonFramework_SOURCE_DIR}/dist)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${RadonFramework_SOURCE_DIR}/dist)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${RadonFramework_SOURCE_DIR}/dist)

FIND_PACKAGE ( Threads REQUIRED )
set(OSLIBS ${OSLIBS} ${CMAKE_THREAD_LIBS_INIT})    
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
				set(OSLIBS ${OSLIBS} X11)
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
			message(STATUS "GDI support: Yes")
            set(USEWDM "#ifndef RF_USE_WDM\n#define RF_USE_WDM\n#endif")
            message(STATUS "WDM support: Yes")
			set(OSLIBS ${OSLIBS} OpenGL32)            
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

OPTION(RADONFRAMEWORK_ENABLE_EXPERIMENTAL_CODE "Enable code which is still in development." OFF)
if(RADONFRAMEWORK_ENABLE_EXPERIMENTAL_CODE)
    OPTION(RADONFRAMEWORK_EXPERIMENTAL_HTTP "Enable HTTP namespace." OFF)
    OPTION(RADONFRAMEWORK_EXPERIMENTAL_HASHTABLE "Enable HashTable class." OFF)
    OPTION(RADONFRAMEWORK_EXPERIMENTAL_HASHLIST "Enable HashList class." OFF)
    OPTION(RADONFRAMEWORK_EXPERIMENTAL_ALLOCATOR "Enable Allocator class." OFF)
    OPTION(RADONFRAMEWORK_EXPERIMENTAL_SIMD "Enable SIMD classes." OFF)
    OPTION(RADONFRAMEWORK_EXPERIMENTAL_OGLVM "Enable OpenGL VM." OFF)
endif()

if(NOT RADONFRAMEWORK_EXPERIMENTAL_HTTP)
    AddSourceDirectoryRecursive(src "src/Net/HTTP" "Sources\\Net\\HTTP")
    AddHeaderDirectoryRecursive(headers "include/RadonFramework/Net/HTTP" "Includes\\Net\\HTTP")
    list(APPEND RADONFRAMEWORK_BLACKLIST ${headers} ${src})
endif()
if(NOT RADONFRAMEWORK_EXPERIMENTAL_HASHTABLE)
    list(APPEND RADONFRAMEWORK_BLACKLIST ${CMAKE_CURRENT_SOURCE_DIR}/include/RadonFramework/Collections/Hashtable.hpp ${CMAKE_CURRENT_SOURCE_DIR}/src/Collections/Hashtable.cpp)
endif()
if(NOT RADONFRAMEWORK_EXPERIMENTAL_ALLOCATOR)
    list(APPEND RADONFRAMEWORK_BLACKLIST ${CMAKE_CURRENT_SOURCE_DIR}/include/RadonFramework/Memory/Allocator.hpp ${CMAKE_CURRENT_SOURCE_DIR}/src/Memory/Allocator.cpp)
endif()
if(NOT RADONFRAMEWORK_EXPERIMENTAL_SIMD)
    AddHeaderDirectoryRecursive(headers "include/RadonFramework/Core/SIMD" "Includes\\Core\\SIMD")
    list(APPEND RADONFRAMEWORK_BLACKLIST ${headers} ${CMAKE_CURRENT_SOURCE_DIR}/include/RadonFramework/Core/SIMD.hpp)
endif()
if(NOT RADONFRAMEWORK_EXPERIMENTAL_OGLVM)
    
    list(APPEND RADONFRAMEWORK_BLACKLIST ${CMAKE_CURRENT_SOURCE_DIR}/include/RadonFramework/Drawing/OpenGLMachine.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/Drawing/OpenGLMachine.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/include/RadonFramework/Drawing/Text2D.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/include/RadonFramework/Drawing/Path2D.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/Drawing/Path2D.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/include/RadonFramework/Drawing/NativeShape.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/Drawing/NativeShape.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/include/RadonFramework/Forms/Label.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/Drawing/Forms/Label.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/include/RadonFramework/Drawing/Draw2D.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/Drawing/Draw2D.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/include/RadonFramework/Drawing/CommandBuffer.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/Drawing/CommandBuffer.cpp)
endif()
if(NOT RADONFRAMEWORK_EXPERIMENTAL_HASHLIST)
    list(APPEND RADONFRAMEWORK_BLACKLIST ${CMAKE_CURRENT_SOURCE_DIR}/include/RadonFramework/Collections/HashList.hpp ${CMAKE_CURRENT_SOURCE_DIR}/src/Collections/HashList.cpp )
endif()

CHECK_FUNCTION_EXISTS(posix_fallocate RF_HAVE_POSIX_FALLOCATE)
if(RF_HAVE_POSIX_FALLOCATE)
    add_definitions(-DRF_HAVE_POSIX_FALLOCATE)
endif()
CHECK_FUNCTION_EXISTS(posix_fadvise RF_HAVE_POSIX_FADVISE)
if(RF_HAVE_POSIX_FADVISE)
    add_definitions(-DRF_HAVE_POSIX_FADVISE)
endif()

include(libRadonFramework.cmake)

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

message(STATUS "Generate ${RadonFramework_SOURCE_DIR}/include/RadonFramework/RadonInline.hpp")
configure_file("${RadonFramework_SOURCE_DIR}/include/RadonFramework/RadonInline.hxx" "${RadonFramework_SOURCE_DIR}/include/RadonFramework/RadonInline.hpp" @ONLY)
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

if(RADONFRAMEWORK_BUILD_UNITTEST)
	add_subdirectory(tests/UnitTest)
endif()
if(RADONFRAMEWORK_BUILD_SYSTEMTEST)
	add_subdirectory(tests/SystemTest)
endif()
if(RADONFRAMEWORK_BUILD_RESOURCETEST)
	add_subdirectory(tests/ResourceTest)
endif()

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