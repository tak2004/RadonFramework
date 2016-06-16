# Defines
CHECK_FUNCTION_EXISTS(posix_fallocate RF_HAVE_POSIX_FALLOCATE)
if(RF_HAVE_POSIX_FALLOCATE)
    AddPublicDefine(RADONFRAMEWORK RF_HAVE_POSIX_FALLOCATE)
endif()

CHECK_FUNCTION_EXISTS(posix_fadvise RF_HAVE_POSIX_FADVISE)
if(RF_HAVE_POSIX_FADVISE)
    AddPublicDefine(RADONFRAMEWORK RF_HAVE_POSIX_FADVISE)
endif()

if(RADONFRAMEWORK_USE_MICROCRT)
	set(RADONFRAMEWORK_MICROCRT "#ifndef RF_MICROCRT\n    #define RF_MICROCRT 1\n#endif")
else()
	set(RADONFRAMEWORK_MICROCRT "")
endif()

foreach(ext MMX SSE SSE2 SSE3 SSSE3 SSE41 SSE42 SSE4A AVX AVX2 AVX512 FMA3 FMA4 NEON AES XOP SHA CPUID)
    if(${RADONFRAMEWORK_COMPILER_USE_INTRINSIC_${ext}})
        set(RADONFRAMEWORK_BUILD_INTRINSIC_${ext} "#ifndef RF_BUILD_INTRINSIC_${ext}\n    #define RF_BUILD_INTRINSIC_${ext} 1\n#endif")
    endif()
endforeach()

FIND_PACKAGE ( Threads REQUIRED )
set(OSLIBS ${OSLIBS} ${CMAKE_THREAD_LIBS_INIT})

# Windows specific options, libs and includes.
if(WIN32)
    # For socket, IP and DNS api you have to link ws2_32.lib and Iphlpapi.lib.
    set(OSLIBS ${OSLIBS} ws2_32 Iphlpapi)
    # For using the process api you have to link psapi.lib.
    set(OSLIBS ${OSLIBS} psapi)    
endif(WIN32)

# UNIX specific options, libs and includes.
if(UNIX)
    # RaspberryPi2b hardware is known at compile time.
    option(RADONFRAMEWORK_HOST_IS_RASPBERRYPI2B "Specify that the host is a RaspberryPi2b" OFF)
    if(RADONFRAMEWORK_HOST_IS_RASPBERRYPI2B)
        add_definitions(-DRF_IS_RASPI2B)
    endif()
    # To load a dynamic library you have to link libdl.so.
    set(OSLIBS ${OSLIBS} dl)
    IF(NOT APPLE)
        set(OSLIBS ${OSLIBS} rt)
    endif()
endif()