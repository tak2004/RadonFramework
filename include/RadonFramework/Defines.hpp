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
    #if defined(_MSC_VER)       
        #define RF_VISUALCPP    
		#if _MSC_VER <= 1600
			#define RF_VISUALCPP_OLDER_2012
		#endif
    #endif                      
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

//--------detect debug mode--------//
#if defined(DEBUG)||defined(_DEBUG)//
    #define RF_DEBUG               //
#endif                             //
//---------------------------------//

// detect architecture
#if defined __LP64__ || defined _M_X64 || defined __MING64__ || defined _LP64
    #define RF_64BIT
#else
    #define RF_32BIT
#endif  

// detect 64bit integer support
#if defined(_MSC_VER) || defined(__SIZEOF_LONG_LONG__) // VS, gcc
    #define RF_HAVE_LONG_LONG
#endif

//defines for cmake
#ifndef RF_USE_OPENGL
#define RF_USE_OPENGL
#endif

#ifndef RF_USE_GDI
#define RF_USE_GDI
#endif
#ifndef RF_USE_WDM
#define RF_USE_WDM
#endif


#ifndef RF_BUILD_INTRINSIC_MMX
    #define RF_BUILD_INTRINSIC_MMX 1
#endif
#ifndef RF_BUILD_INTRINSIC_SSE
    #define RF_BUILD_INTRINSIC_SSE 1
#endif
#ifndef RF_BUILD_INTRINSIC_SSE2
    #define RF_BUILD_INTRINSIC_SSE2 1
#endif
#ifndef RF_BUILD_INTRINSIC_SSE3
    #define RF_BUILD_INTRINSIC_SSE3 1
#endif
#ifndef RF_BUILD_INTRINSIC_SSSE3
    #define RF_BUILD_INTRINSIC_SSSE3 1
#endif
#ifndef RF_BUILD_INTRINSIC_SSE41
    #define RF_BUILD_INTRINSIC_SSE41 1
#endif
#ifndef RF_BUILD_INTRINSIC_SSE42
    #define RF_BUILD_INTRINSIC_SSE42 1
#endif

#ifndef RF_BUILD_INTRINSIC_AVX
    #define RF_BUILD_INTRINSIC_AVX 1
#endif
#ifndef RF_BUILD_INTRINSIC_AVX2
    #define RF_BUILD_INTRINSIC_AVX2 1
#endif

#ifndef RF_BUILD_INTRINSIC_FMA3
    #define RF_BUILD_INTRINSIC_FMA3 1
#endif
#ifndef RF_BUILD_INTRINSIC_FMA4
    #define RF_BUILD_INTRINSIC_FMA4 1
#endif

#ifndef RF_BUILD_INTRINSIC_AES
    #define RF_BUILD_INTRINSIC_AES 1
#endif
#ifndef RF_BUILD_INTRINSIC_XOP
    #define RF_BUILD_INTRINSIC_XOP 1
#endif

#ifndef RF_BUILD_INTRINSIC_CPUID
    #define RF_BUILD_INTRINSIC_CPUID 1
#endif

#endif
