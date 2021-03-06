AddHeaderDirectory(filelist "include/RadonFramework" "Includes")
set(HDRS_ROOT ${filelist})
	
AddSourceDirectory(filelist "src" "Sources")
set(SRC_ROOT ${filelist})
	
set(LIBSRCFILES ${SRC_ROOT})

set(LIBHDRFILES ${HDRS_ROOT})

set(HDRS_BACKEND
    include/RadonFramework/backend/FastDelegate.h
    include/RadonFramework/backend/FastDelegateBind.h)
	
set(HDRS_BACKEND_GOOGLE
    include/RadonFramework/backend/google/dense_hash_map
    include/RadonFramework/backend/google/dense_hash_set
    include/RadonFramework/backend/google/sparse_hash_map
    include/RadonFramework/backend/google/sparse_hash_set
    include/RadonFramework/backend/google/sparsetable
    include/RadonFramework/backend/google/type_traits.h)

set(HDRS_BACKEND_GOOGLE_SPARSEHASH
    include/RadonFramework/backend/google/sparsehash/densehashtable.h
    include/RadonFramework/backend/google/sparsehash/libc_allocator_with_realloc.h
    include/RadonFramework/backend/google/sparsehash/sparseconfig.h
    include/RadonFramework/backend/google/sparsehash/sparseconfig_vsc.h
    include/RadonFramework/backend/google/sparsehash/sparseconfig_win.h
    include/RadonFramework/backend/google/sparsehash/sparsehashtable.h)

set(SRC_BACKEND_HASHLIBPP
    backend/hashlib++/src/HashlibHashfunctionService.cpp
    backend/hashlib++/src/hl_md5.cpp
    backend/hashlib++/src/hl_md5wrapper.cpp
    backend/hashlib++/src/hl_sha1.cpp
    backend/hashlib++/src/hl_sha1wrapper.cpp
    backend/hashlib++/src/hl_sha2ext.cpp
    backend/hashlib++/src/hl_sha256.cpp
    backend/hashlib++/src/hl_sha256wrapper.cpp
    backend/hashlib++/src/hl_sha384wrapper.cpp
    backend/hashlib++/src/hl_sha512wrapper.cpp)

set(HDRS_BACKEND_HASHLIBPP
    include/RadonFramework/backend/hashlib++/HashlibHashfunctionService.hpp
    include/RadonFramework/backend/hashlib++/hashlibpp.h
    include/RadonFramework/backend/hashlib++/hl_exception.h
    include/RadonFramework/backend/hashlib++/hl_hashwrapper.h
    include/RadonFramework/backend/hashlib++/hl_md5.h
    include/RadonFramework/backend/hashlib++/hl_md5wrapper.h
    include/RadonFramework/backend/hashlib++/hl_sha1.h
    include/RadonFramework/backend/hashlib++/hl_sha1wrapper.h
    include/RadonFramework/backend/hashlib++/hl_sha2ext.h
    include/RadonFramework/backend/hashlib++/hl_sha2mac.h
    include/RadonFramework/backend/hashlib++/hl_sha256.h
    include/RadonFramework/backend/hashlib++/hl_sha256wrapper.h
    include/RadonFramework/backend/hashlib++/hl_sha384wrapper.h
    include/RadonFramework/backend/hashlib++/hl_sha512wrapper.h
    include/RadonFramework/backend/hashlib++/hl_types.h)

set(SRC_BACKEND_MURMURHASH
    backend/MurmurHash/MurmurHash2_64.cpp
    backend/MurmurHash/MurmurHashHashfunctionService.cpp)

set(HDRS_BACKEND_MURMURHASH
    include/RadonFramework/backend/MurmurHash/MurmurHashHashfunctionService.hpp)

AddSourceDirectory(filelist "backend/stringcoders" "Sources\\backend\\stringcoders")
set(SRC_BACKEND_STRINGCODERS ${filelist})
set_source_files_properties(${SRC_BACKEND_STRINGCODERS} PROPERTIES LANGUAGE CXX)

AddHeaderDirectory(filelist "include/RadonFramework/backend/stringcoders" "Includes\\backend\\stringcoders")
set(HDRS_BACKEND_STRINGCODERS ${filelist})
	
set(LIBBACKENDGENERALSRCFILES
    ${SRC_BACKEND_HASHLIBPP}
    ${SRC_BACKEND_MURMURHASH}
    ${SRC_BACKEND_STRINGCODERS}
	)

set(LIBBACKENDGENERALHDRFILES
    ${HDRS_BACKEND}
    ${HDRS_BACKEND_GOOGLE}
    ${HDRS_BACKEND_GOOGLE_SPARSEHASH}
    ${HDRS_BACKEND_HASHLIBPP}
    ${HDRS_BACKEND_MURMURHASH}
    ${HDRS_BACKEND_STRINGCODERS}
	)

set(LIBBACKENDSRCFILES_LINUX
    ${SRC_BACKEND_LINUX})

set(LIBBACKENDHDRFILES_LINUX
    ${HDRS_BACKEND_LINUX})
	
# these files are excluded on other platforms
set(LIBSRCFILES_WINDOW
	src/System/EnvironmentWindows.cpp
	src/System/MemoryWindows.cpp
	src/System/IO/FileSystemWindows.cpp
	src/System/StringWindows.cpp
	src/System/TimeWindows.cpp
	src/System/ProcessWindows.cpp
	src/System/Hardware/HardwareWindows.cpp
    src/System/Threading/ThreadWindows.cpp
    src/System/SecurityWindows.cpp)
	
set(LIBSRCFILES_LINUX
	src/System/TimeLinux.cpp
	src/System/EnvironmentLinux.cpp
	src/System/StringLinux.cpp
	src/System/IO/FileSystemLinux.cpp
	src/System/Hardware/HardwareLinux.cpp
    src/System/Threading/ThreadLinux.cpp)
	
set(LIBSRCFILES_UNIX
	src/System/TimeUnix.cpp
    src/System/EnvironmentUnix.cpp
	src/System/StringUnix.cpp
	src/System/MemoryUnix.cpp
	src/System/ProcessUnix.cpp
	src/System/IO/FileSystemUnix.cpp
    src/System/Threading/ThreadUnix.cpp)
	
set(LIBSRCFILES_OSX
    src/System/EnvironmentOSX.cpp
	src/System/TimeOSX.cpp
    src/System/IO/FileSystemOSX.cpp
    src/System/Hardware/HardwareOSX.cpp
    src/System/Threading/ThreadOSX.cpp)
	
set(LIBSRCFILES_MICROCRT
	src/System/MicroRuntimeLibrary/CommandLine.cpp
	src/System/MicroRuntimeLibrary/File.cpp
	src/System/MicroRuntimeLibrary/InitializeAndTerminate.cpp
	src/System/MicroRuntimeLibrary/Math.cpp
	src/System/MicroRuntimeLibrary/Memory.cpp
	src/System/MicroRuntimeLibrary/SharedLibrary.cpp
	src/System/MicroRuntimeLibrary/Window.cpp)

# Radon Framework source code
source_group("Sources" FILES ${SRC_ROOT})
source_group("Sources\\backend\\Hashlib++" FILES ${SRC_BACKEND_HASHLIBPP})
source_group("Sources\\backend\\MurmurHash" FILES ${SRC_BACKEND_MURMURHASH})
source_group("Sources\\backend\\StringCoders" FILES ${SRC_BACKEND_STRINGCODERS})

# Radon Framework header
source_group("Includes" FILES ${HDRS_ROOT})
source_group("Includes\\backend" FILES ${HDRS_BACKEND})
source_group("Includes\\backend\\Google" FILES ${HDRS_BACKEND_GOOGLE})
source_group("Includes\\backend\\Google\\SparseHash" FILES ${HDRS_BACKEND_GOOGLE_SPARSEHASH})
source_group("Includes\\backend\\Hashlib++" FILES ${HDRS_BACKEND_HASHLIBPP})
source_group("Includes\\backend\\MurmurHash" FILES ${HDRS_BACKEND_MURMURHASH})
source_group("Includes\\backend\\StringCoders" FILES ${HDRS_BACKEND_STRINGCODERS})

AddSourceDirectoryRecursive(filelist "src/Collections" "Sources\\Collections")
list(APPEND LIBSRCFILES ${filelist})
AddSourceDirectoryRecursive(filelist "src/Core" "Sources\\Core")
list(APPEND LIBSRCFILES ${filelist})
AddSourceDirectoryRecursive(filelist "src/Math" "Sources\\Math")
list(APPEND LIBSRCFILES ${filelist})
AddSourceDirectoryRecursive(filelist "src/IO" "Sources\\IO")
list(APPEND LIBSRCFILES ${filelist})
AddSourceDirectoryRecursive(filelist "src/Memory" "Sources\\Memory")
list(APPEND LIBSRCFILES ${filelist})
AddSourceDirectoryRecursive(filelist "src/System" "Sources\\System")
list(APPEND LIBSRCFILES ${filelist})
AddSourceDirectoryRecursive(filelist "src/Threading" "Sources\\Threading")
list(APPEND LIBSRCFILES ${filelist})
AddSourceDirectoryRecursive(filelist "src/Time" "Sources\\Time")
list(APPEND LIBSRCFILES ${filelist})
AddSourceDirectoryRecursive(filelist "src/Net" "Sources\\Net")
list(APPEND LIBSRCFILES ${filelist})
AddSourceDirectoryRecursive(filelist "src/Reflection" "Sources\\Reflection")
list(APPEND LIBSRCFILES ${filelist})
AddSourceDirectoryRecursive(filelist "src/Drawing" "Sources\\Drawing")
list(APPEND LIBSRCFILES ${filelist})
AddSourceDirectoryRecursive(filelist "src/Text" "Sources\\Text")
list(APPEND LIBSRCFILES ${filelist})

AddHeaderDirectoryRecursive(filelist "include/RadonFramework/Reflection" "Includes\\Reflection")
list(APPEND LIBHDRFILES ${filelist})	
AddHeaderDirectoryRecursive(filelist "include/RadonFramework/Collections" "Includes\\Collections")
list(APPEND LIBHDRFILES ${filelist})
AddHeaderDirectoryRecursive(filelist "include/RadonFramework/Core" "Includes\\Core")
list(APPEND LIBHDRFILES ${filelist})
AddHeaderDirectoryRecursive(filelist "include/RadonFramework/Math" "Includes\\Math")
list(APPEND LIBHDRFILES ${filelist})
AddHeaderDirectoryRecursive(filelist "include/RadonFramework/IO" "Includes\\IO")
list(APPEND LIBHDRFILES ${filelist})
AddHeaderDirectoryRecursive(filelist "include/RadonFramework/Memory" "Includes\\Memory")
list(APPEND LIBHDRFILES ${filelist})
AddHeaderDirectoryRecursive(filelist "include/RadonFramework/System" "Includes\\System")
list(APPEND LIBHDRFILES ${filelist})
AddHeaderDirectoryRecursive(filelist "include/RadonFramework/Threading" "Includes\\Threading")
list(APPEND LIBHDRFILES ${filelist})
AddHeaderDirectoryRecursive(filelist "include/RadonFramework/Time" "Includes\\Time")
list(APPEND LIBHDRFILES ${filelist})
AddHeaderDirectoryRecursive(filelist "include/RadonFramework/Net" "Includes\\Net")
list(APPEND LIBHDRFILES ${filelist})
AddHeaderDirectoryRecursive(filelist "include/RadonFramework/Drawing" "Includes\\Drawing")
list(APPEND LIBHDRFILES ${filelist})
AddHeaderDirectoryRecursive(filelist "include/RadonFramework/Text" "Includes\\Text")
list(APPEND LIBHDRFILES ${filelist})

# custom CMake files
source_group("cmake" FILES "libRadonFramework.cmake")

# merge OS specific files into backend files
set(LIBBACKENDSRCFILES ${LIBBACKENDGENERALSRCFILES}	
	${LIBBACKENDSRCFILES_WINDOWS}
	${LIBBACKENDSRCFILES_LINUX})
set(LIBBACKENDHDRFILES 
	${LIBBACKENDHDRFILES_WINDOWS}
	${LIBBACKENDHDRFILES_LINUX})

# uri++ compiler define for compiling a static library
ADD_DEFINITIONS(-DURIPP_STATIC)

set(SourceList ${LIBSRCFILES} ${LIBHDRFILES} ${LIBBACKENDHDRFILES} ${LIBBACKENDSRCFILES} 
	${MODULES_SRC} ${MODULES_HDRS} "libRadonFramework.cmake")

LIST(LENGTH RADONFRAMEWORK_BLACKLIST RADONFRAMEWORK_BLACKLISTCOUNT)
if(${RADONFRAMEWORK_BLACKLISTCOUNT} GREATER 0)
    list(REMOVE_ITEM SourceList ${RADONFRAMEWORK_BLACKLIST})
endif()
	
set_source_files_properties(${LIBBACKENDHDRFILES} ${LIBHDRFILES} ${MODULES_HDRS} PROPERTIES HEADER_FILE_ONLY ON)

#
# setup precompiled header
#
if(${RADONFRAMEWORK_COMPILER_EXPORT_AS_MODULE})
    set(RADONFRAMEWORK_COMPILER_USE_PRECOMPILED_HEADER OFF CACHE BOOL "Activate precompiled header(Default: on)" FORCE)
    AddPrivateDefine(RF_SKIP_PRECOMPILED_HEADER)
else()
    option(RADONFRAMEWORK_COMPILER_USE_PRECOMPILED_HEADER "Activate precompiled header(Default: on)" ON)
endif()
if(${RADONFRAMEWORK_COMPILER_USE_PRECOMPILED_HEADER})
	CreatePrecompiledHeader(RADONFRAMEWORK "RadonFramework/precompiled.hpp" "src/precompiled.cpp" SourceList)
endif()

set(RADONFRAMEWORK_FILES ${SourceList})
set(RADONFRAMEWORK_LIBS ${OSLIBS})

# Following lines disable the processing of source code for the specified files but
# they will be visible in the source tree.
if(NOT RADONFRAMEWORK_USE_MICROCRT)
	set_source_files_properties(${LIBSRCFILES_MICROCRT} PROPERTIES HEADER_FILE_ONLY ON)
endif()

if(WIN32)
	SET_SOURCE_FILES_PROPERTIES(${LIBBACKENDHDRFILES_LINUX} ${LIBBACKENDSRCFILES_LINUX} ${LIBSRCFILES_LINUX}
		PROPERTIES HEADER_FILE_ONLY ON)	
	SET_SOURCE_FILES_PROPERTIES(${LIBSRCFILES_UNIX} PROPERTIES HEADER_FILE_ONLY ON)	
	SET_SOURCE_FILES_PROPERTIES(${LIBSRCFILES_OSX} PROPERTIES HEADER_FILE_ONLY ON)	
endif(WIN32)

if(UNIX)
	SET_SOURCE_FILES_PROPERTIES(${LIBBACKENDHDRFILES_WINDOWS} ${LIBBACKENDSRCFILES_WINDOWS} ${LIBSRCFILES_WINDOW}
		PROPERTIES HEADER_FILE_ONLY ON)	
	if(APPLE)
		SET_SOURCE_FILES_PROPERTIES(${LIBBACKENDHDRFILES_LINUX} ${LIBBACKENDSRCFILES_LINUX} ${LIBSRCFILES_LINUX}
			PROPERTIES HEADER_FILE_ONLY ON)
	else()
		SET_SOURCE_FILES_PROPERTIES(${LIBSRCFILES_OSX} PROPERTIES HEADER_FILE_ONLY ON)
	endif()
endif(UNIX)	

