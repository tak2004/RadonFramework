#
# This file will help you to integrate a Radon CMake framework based project into your project.
# http://www.radonframework.org/projects/rf/wiki/UserManualCMakeFramework
# http://www.radonframework.org/projects/rf/wiki/DeveloperManualCMakeFramework
#
macro(ConfigureCompilerAndLinker projectid buildtype)
	#
	# Options for general compiler features.
	#
	# To extensive use can slow down the program execution and bloat up the memory usage.
	option(${projectid}_COMPILER_USE_RTTI "Activate runtime type information(Default: off)" OFF)
	# One of the easiest ways to produce memory leaks if used not correctly. Even then there are still rare cases when a memleak can be produced.
	option(${projectid}_COMPILER_USE_EXCEPTION "Activate exceptions(Default: off)" OFF)
	# Most compiler support a couple of intrinsic functions which will replace standard C routines(e.g. memcpy).
	option(${projectid}_COMPILER_USE_INTRINSIC "Activate intrinsic functions(Default: on)" ON)
	# Many bugs exists because this switch is turned off.
	option(${projectid}_COMPILER_TREAT_WARNINGS_AS_ERROR "Treat warnings as error(Default: on)" ON)
	# A project which use dynamic linking need the libcrt.so/msvcrt.dll shared library on the target system to run.
	# Static linking increase the size of the binary but don't need further shared libraries.
	option(${projectid}_COMPILER_STATIC_LINKED_CRT "Told the compiler to compile the C runtime library functions or link them." OFF)
	#
	#option(${projectid}_COMPILER_WARNING)
	
	#
	# Options for general linker features.
	#
	if(${buildtype} STREQUAL "EXECUTABLE")
		# This option mostly used for the demo scene and embedded systems as like consoles.
		option(${projectid}_LINKER_USE_DEFAULTLIB "Use C runtime library and other system specific default libraries(Default: on)" ON)
		# Mostly used in combination with DEFAULTLIB=OFF to build ultra small binaries.
		option(${projectid}_LINKER_USE_DEFAULTENTRYPOINT "Use the target system default entry point(Default: on)" ON)
		if(NOT ${${projectid}_LINKER_USE_DEFAULTENTRYPOINT})
			set(${projectid}_LINKER_ENTRYPOINT "entrypoint" CACHE STRING "Custom entry point(Default: entry")
		endif()
	endif()
	
	# This allow to add and compile asm files commonly named with .s as extension
	enable_language(ASM)
	
	#
	# Initialize compiler flags.
	#
	# This flags will be merged into all compiler targets.
	set(${projectid}_COMPILER_FLAGS "")
	# This flags will be used for Debug target.
	set(${projectid}_COMPILER_FLAGS_DEBUG "")
	# This flags will be used for Release target.
	set(${projectid}_COMPILER_FLAGS_RELEASE "")
	# This flags will be used for "minimized Release" target.
	set(${projectid}_COMPILER_FLAGS_RELMINSIZE "")
	# This flags will be used for "Release with debug infos" target.
	set(${projectid}_COMPILER_FLAGS_RELWITHDEBINFO "")

	#
	# Initialize assembler compiler flags.
	#
	# This flags will be merged into all compiler targets.
	set(${projectid}_ASM_COMPILER_FLAGS "")
	# This flags will be used for Debug target.
	set(${projectid}_ASM_COMPILER_FLAGS_DEBUG "")
	# This flags will be used for Release target.
	set(${projectid}_ASM_COMPILER_FLAGS_RELEASE "")
	# This flags will be used for "minimized Release" target.
	set(${projectid}_ASM_COMPILER_FLAGS_RELMINSIZE "")
	# This flags will be used for "Release with debug infos" target.
	set(${projectid}_ASM_COMPILER_FLAGS_RELWITHDEBINFO "")
	
	#
	# Initialize linker flags.
	#
	if(${buildtype} STREQUAL "EXECUTABLE")
		# This flags will be merged into all linker targets.
		set(${projectid}_LINKER_FLAGS "")
		# This flags will be used for Debug target.
		set(${projectid}_LINKER_FLAGS_DEBUG "")
		# This flags will be used for Release target.
		set(${projectid}_LINKER_FLAGS_RELEASE "")
		# This flags will be used for "minimized Release" target.
		set(${projectid}_LINKER_FLAGS_RELMINSIZE "")
		# This flags will be used for "Release with debug infos" target.
		set(${projectid}_LINKER_FLAGS_RELWITHDEBINFO "")
	endif()
	
	#
	# Initialize necessary library list.
	#

	#
	# Include all compiler files.
	# Each include must handle it self.
	#
	include("${${projectid}_LOCATION}/cmake/intern/VisualStudio.cmake")
	ConfigureCompilerAndLinkerVS(${projectid} ${buildtype})
	include("${${projectid}_LOCATION}/cmake/intern/GCC.cmake")
	ConfigureCompilerAndLinkerGCC(${projectid} ${buildtype})
	include("${${projectid}_LOCATION}/cmake/intern/XCode.cmake")
	ConfigureCompilerAndLinkerXCode(${projectid} ${buildtype})
	include("${${projectid}_LOCATION}/cmake/intern/UnixMakefile.cmake")
	ConfigureCompilerAndLinkerUnixMakefile(${projectid} ${buildtype})

	#
	# gather hardware dependent information
	#
	# Figure out if the target architecture is 32Bit or 64Bit.
	if(CMAKE_SIZEOF_VOID_P EQUAL 4)
		set(${projectid}_COMPILEDFORARCHITECTURE "_32Bit")
	elseif(CMAKE_SIZEOF_VOID_P EQUAL 8)
		set(${projectid}_COMPILEDFORARCHITECTURE "_64Bit")
	else()
		set(${projectid}_COMPILEDFORARCHITECTURE "Unknown")
	endif()

	#endianness
	include(TestBigEndian)
	TEST_BIG_ENDIAN(ENDIANNESS)
	IF(${ENDIANNESS})
		set(${projectid}_ENDIANNESS "Big")
	else()
		set(${projectid}_ENDIANNESS "Little")
	endif()
endmacro()

macro(FinalizeCompilerAndLinkerSettings projectid)
	set(CMAKE_ASM_FLAGS ${${projectid}_ASM_COMPILER_FLAGS})
	set(CMAKE_ASM_FLAGS_DEBUG ${${projectid}_ASM_COMPILER_FLAGS_DEBUG})
	set(CMAKE_ASM_FLAGS_RELEASE ${${projectid}_ASM_COMPILER_FLAGS_RELEASE})
	set(CMAKE_ASM_FLAGS_RELWITHDEBINFO ${${projectid}_ASM_COMPILER_FLAGS_RELWITHDEBINFO})
	set(CMAKE_ASM_FLAGS_MINSIZEREL ${${projectid}_ASM_COMPILER_FLAGS_RELMINSIZE})
	
	set(CMAKE_CXX_FLAGS ${${projectid}_COMPILER_FLAGS})
	set(CMAKE_CXX_FLAGS_DEBUG ${${projectid}_COMPILER_FLAGS_DEBUG})
	set(CMAKE_CXX_FLAGS_RELEASE ${${projectid}_COMPILER_FLAGS_RELEASE})
	set(CMAKE_CXX_FLAGS_RELWITHDEBINFO ${${projectid}_COMPILER_FLAGS_RELWITHDEBINFO})
	set(CMAKE_CXX_FLAGS_MINSIZEREL ${${projectid}_COMPILER_FLAGS_RELMINSIZE})
	
	set(CMAKE_EXE_LINKER_FLAGS ${${projectid}_LINKER_FLAGS})
	set(CMAKE_EXE_LINKER_FLAGS_DEBUG ${${projectid}_LINKER_FLAGS} ${${projectid}_LINKER_FLAGS_DEBUG})
	set(CMAKE_EXE_LINKER_FLAGS_RELEASE ${${projectid}_LINKER_FLAGS} ${${projectid}_LINKER_FLAGS_RELEASE})
	set(CMAKE_EXE_LINKER_FLAGS_RELWITHDEBINFO ${${projectid}_LINKER_FLAGS} ${${projectid}_LINKER_FLAGS_RELWITHDEBINFO})
	set(CMAKE_EXE_LINKER_FLAGS_MINSIZEREL ${${projectid}_LINKER_FLAGS} ${${projectid}_LINKER_FLAGS_MINSIZEREL})
	
	set(CMAKE_MODULE_LINKER_FLAGS ${${projectid}_LINKER_FLAGS})
	set(CMAKE_MODULE_LINKER_FLAGS_DEBUG ${${projectid}_LINKER_FLAGS} ${${projectid}_LINKER_FLAGS_DEBUG})
	set(CMAKE_MODULE_LINKER_FLAGS_RELEASE ${${projectid}_LINKER_FLAGS} ${${projectid}_LINKER_FLAGS_RELEASE})
	set(CMAKE_MODULE_LINKER_FLAGS_RELWITHDEBINFO ${${projectid}_LINKER_FLAGS} ${${projectid}_LINKER_FLAGS_RELWITHDEBINFO})
	set(CMAKE_MODULE_LINKER_FLAGS_MINSIZEREL ${${projectid}_LINKER_FLAGS} ${${projectid}_LINKER_FLAGS_MINSIZEREL})

	set(CMAKE_SHARED_LINKER_FLAGS ${${projectid}_LINKER_FLAGS})
	set(CMAKE_SHARED_LINKER_FLAGS_DEBUG ${${projectid}_LINKER_FLAGS} ${${projectid}_LINKER_FLAGS_DEBUG})
	set(CMAKE_SHARED_LINKER_FLAGS_RELEASE ${${projectid}_LINKER_FLAGS} ${${projectid}_LINKER_FLAGS_RELEASE})
	set(CMAKE_SHARED_LINKER_FLAGS_RELWITHDEBINFO ${${projectid}_LINKER_FLAGS} ${${projectid}_LINKER_FLAGS_RELWITHDEBINFO})
	set(CMAKE_SHARED_LINKER_FLAGS_MINSIZEREL ${${projectid}_LINKER_FLAGS} ${${projectid}_LINKER_FLAGS_MINSIZEREL})
endmacro()