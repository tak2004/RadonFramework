/*
*
* THIS FILE IS GENERATED FROM build/code_templates/Defines.hxx !!!
*
*/
#ifndef RF_DEFINES_HPP
#define RF_DEFINES_HPP

//-------------------------------------------------------detect OS-----------//
#if defined(__WINDOWS__) || defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(WIN64) || defined(_WIN64)
    #ifndef RF_WINDOWS
        #define RF_WINDOWS 1
    #endif
#endif

#if defined(linux) || defined(__linux)
    #ifndef RF_LINUX
        #define RF_LINUX 1
    #endif
    #ifndef RF_UNIX
        #define RF_UNIX 1
    #endif
#endif

#if defined(__APPLE__)
    #ifndef RF_OSX
        #define RF_OSX 1
    #endif
    #ifndef RF_UNIX
        #define RF_UNIX 1
    #endif
#endif

#if defined(__unix)
    #ifndef RF_UNIX
        #define RF_UNIX 1
    #endif
#endif

//---------------------------------------------------------------------------//

//-------detect compiler---------//
#if defined(RF_WINDOWS)          
    //Visual Studio C++ compiler
    #if defined(_MSC_VER) && !defined(__clang__)
        #define RF_VISUALCPP    
		#if _MSC_VER <= 1600
			#define RF_VISUALCPP_OLDER_2012
		#endif
    #endif                      
#endif                          

//Clang compiler
#if defined(__clang__)
    #define RF_CLANG
#endif
                                
//MinGW compiler                
#if defined(__MINGW32__)        
    #define RF_MINGW32          
#endif                          
                                
//GCC                           
#if defined(__GNUC__)           
    #define RF_GCC              
#endif                          
//-------------------------------//

// detect architecture
#if defined __LP64__ || defined _M_X64 || defined __MING64__ || defined _LP64
    #define RF_64BIT
#else
    #define RF_32BIT
#endif  

//defines for cmake
@USEOPENGL@
@USEX11@
@USEGDI@
@USEWDM@
@OSTHREADSERVICE_INCLUDE@
@RADONFRAMEWORK_MICROCRT@
@RADONFRAMEWORK_BUILD_INTRINSIC_MMX@
@RADONFRAMEWORK_BUILD_INTRINSIC_SSE@
@RADONFRAMEWORK_BUILD_INTRINSIC_SSE2@
@RADONFRAMEWORK_BUILD_INTRINSIC_SSE3@
@RADONFRAMEWORK_BUILD_INTRINSIC_SSSE3@
@RADONFRAMEWORK_BUILD_INTRINSIC_SSE41@
@RADONFRAMEWORK_BUILD_INTRINSIC_SSE42@
@RADONFRAMEWORK_BUILD_INTRINSIC_SSE4A@
@RADONFRAMEWORK_BUILD_INTRINSIC_AVX@
@RADONFRAMEWORK_BUILD_INTRINSIC_AVX2@
@RADONFRAMEWORK_BUILD_INTRINSIC_AVX512@
@RADONFRAMEWORK_BUILD_INTRINSIC_FMA3@
@RADONFRAMEWORK_BUILD_INTRINSIC_FMA4@
@RADONFRAMEWORK_BUILD_INTRINSIC_NEON@
@RADONFRAMEWORK_BUILD_INTRINSIC_AES@
@RADONFRAMEWORK_BUILD_INTRINSIC_XOP@
@RADONFRAMEWORK_BUILD_INTRINSIC_SHA@
@RADONFRAMEWORK_BUILD_INTRINSIC_CPUID@

#endif
