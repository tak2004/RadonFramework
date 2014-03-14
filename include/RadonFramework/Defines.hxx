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
    #ifndef RF_MACOS
        #define RF_MACOS 1
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
#if defined(RF_WINDOWS)          //
    //Visual Studio C++ compiler //
    #if defined(_MSC_VER)        //
        #define RF_VISUALCPP     //
    #endif                       //
#endif                           //
                                 //
//MinGW compiler                 //
#if defined(__MINGW32__)         //
    #define RF_MINGW32           //
#endif                           //
                                 //
//GCC                            //
#if defined(__GNUC__)            //
    #define RF_GCC               //
#endif                           //
//-------------------------------//

//--------detect debug mode--------//
#if defined(DEBUG)||defined(_DEBUG)//
    #define RF_DEBUG               //
#endif                             //
//---------------------------------//

// detect architecture
#if defined(_LP64) && _LP64==1 || defined(_WIN64) // gcc, VS
    #define RF_64BIT           
#else                          
    #define RF_32BIT           
#endif  

// detect 64bit integer support
#if defined(_MSC_VER) || defined(__SIZEOF_LONG_LONG__) // VS, gcc
    #define RF_HAVE_LONG_LONG    
#endif  

//defines for cmake
@USEOPENGL@
@USEX11@
@USEGDI@
@OSTHREADSERVICE_INCLUDE@
@RADONFRAMEWORK_PRECOMPILED_PIMPL@
@RADONFRAMEWORK_MICROCRT@

#endif
