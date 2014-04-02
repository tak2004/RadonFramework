AddHeaderDirectory(filelist "include/RadonFramework" "Includes")
set(HDRS_ROOT ${filelist})
	
AddSourceDirectory(filelist "src" "Sources")
set(SRC_ROOT ${filelist})
	
AddSourceDirectory(filelist "src/Drawing" "Sources\\Drawing")
set(SRC_DRAWING ${filelist})

AddHeaderDirectory(filelist "include/RadonFramework/Drawing" "Includes\\Drawing")
set(HDRS_DRAWING ${filelist})

AddSourceDirectory(filelist "src/Drawing/Forms" "Sources\\Drawing\\Forms")
set(SRC_DRAWING_FORMS ${filelist})

AddHeaderDirectory(filelist "include/RadonFramework/Drawing/Forms" "Includes\\Drawing\\Forms")
set(HDRS_DRAWING_FORMS ${filelist})

set(LIBSRCFILES
	${SRC_ROOT}
    ${SRC_DRAWING}
	${SRC_DRAWING_FORMS})

set(LIBHDRFILES
    ${HDRS_ROOT}
    ${HDRS_DRAWING}
	${HDRS_DRAWING_FORMS})

set(HDRS_BACKEND
    include/RadonFramework/backend/FastDelegate.h
    include/RadonFramework/backend/FastDelegateBind.h)
	
if(OPENGL_FOUND)
	set(SRC_BACKEND_GLEW backend/Glew/glew.c)
        
    set_source_files_properties(backend/Glew/glew.c PROPERTIES LANGUAGE CXX)

	set(HDRS_BACKEND_GL
		include/RadonFramework/backend/GL/glew.h
		include/RadonFramework/backend/GL/glxew.h
		include/RadonFramework/backend/GL/wglew.h)
endif(OPENGL_FOUND)

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

if(OPENGL_FOUND)
	set(SRC_BACKEND_OPENGL
		backend/OpenGL/OpenGLCanvas.cpp
		backend/OpenGL/GraphicDriverInformationOpenGL.cpp)

	set(HDRS_BACKEND_OPENGL
		include/RadonFramework/backend/OpenGL/OpenGLCanvas.hpp
		include/RadonFramework/backend/OpenGL/GraphicDriverInformationOpenGL.hpp)
endif(OPENGL_FOUND)

AddSourceDirectory(filelist "backend/stringcoders" "Sources\\backend\\stringcoders")
set(SRC_BACKEND_STRINGCODERS ${filelist})
set_source_files_properties(${SRC_BACKEND_STRINGCODERS} PROPERTIES LANGUAGE CXX)

AddHeaderDirectory(filelist "include/RadonFramework/backend/stringcoders" "Includes\\backend\\stringcoders")
set(HDRS_BACKEND_STRINGCODERS ${filelist})
	
if(OPENGL_FOUND)
set(SRC_BACKEND_WINDOWS_DRAWING
    backend/Windows/Drawing/GDIOpenGL1Canvas3D.cpp
    backend/Windows/Drawing/GDIOpenGL1Canvas3DService.cpp
    backend/Windows/Drawing/GDIOpenGL2Canvas3D.cpp
    backend/Windows/Drawing/GDIOpenGL2Canvas3DService.cpp
    backend/Windows/Drawing/GDIOpenGL3Canvas3D.cpp
    backend/Windows/Drawing/GDIOpenGL3Canvas3DService.cpp)

set(HDRS_BACKEND_WINDOWS_DRAWING
    include/RadonFramework/backend/Windows/Drawing/GDIOpenGL1Canvas3D.hpp
    include/RadonFramework/backend/Windows/Drawing/GDIOpenGL1Canvas3DService.hpp
    include/RadonFramework/backend/Windows/Drawing/GDIOpenGL2Canvas3D.hpp
    include/RadonFramework/backend/Windows/Drawing/GDIOpenGL2Canvas3DService.hpp
    include/RadonFramework/backend/Windows/Drawing/GDIOpenGL3Canvas3D.hpp
    include/RadonFramework/backend/Windows/Drawing/GDIOpenGL3Canvas3DService.hpp)
endif()

set(SRC_BACKEND_WINDOWS_FORMS
    backend/Windows/Forms/WindowsApplication.cpp
    backend/Windows/Forms/WindowsWindow.cpp
    backend/Windows/Forms/WindowsWindowService.cpp)

set(HDRS_BACKEND_WINDOWS_FORMS
    include/RadonFramework/backend/Windows/Forms/WindowsApplication.hpp
    include/RadonFramework/backend/Windows/Forms/WindowsWindow.hpp
    include/RadonFramework/backend/Windows/Forms/WindowsWindowService.hpp)

if(OPENGL_FOUND)
set(SRC_BACKEND_X11_DRAWING
	backend/X11/Drawing/X11OpenGL1Canvas3D.cpp
	backend/X11/Drawing/X11OpenGL1Canvas3DService.cpp
	backend/X11/Drawing/X11OpenGL2Canvas3D.cpp
	backend/X11/Drawing/X11OpenGL2Canvas3DService.cpp
	backend/X11/Drawing/X11OpenGL3Canvas3D.cpp
	backend/X11/Drawing/X11OpenGL3Canvas3DService.cpp)

set(HDRS_BACKEND_X11_DRAWING
	include/RadonFramework/backend/X11/Drawing/X11OpenGL1Canvas3D.hpp
	include/RadonFramework/backend/X11/Drawing/X11OpenGL1Canvas3DService.hpp
	include/RadonFramework/backend/X11/Drawing/X11OpenGL2Canvas3D.hpp
	include/RadonFramework/backend/X11/Drawing/X11OpenGL2Canvas3DService.hpp
	include/RadonFramework/backend/X11/Drawing/X11OpenGL3Canvas3D.hpp
	include/RadonFramework/backend/X11/Drawing/X11OpenGL3Canvas3DService.hpp)
endif()

set(SRC_BACKEND_X11_FORMS
	backend/X11/Forms/X11Application.cpp
	backend/X11/Forms/X11Window.cpp
	backend/X11/Forms/X11WindowService.cpp)

set(HDRS_BACKEND_X11_FORMS
	include/RadonFramework/backend/X11/Forms/X11Application.hpp
	include/RadonFramework/backend/X11/Forms/X11Window.hpp
	include/RadonFramework/backend/X11/Forms/X11WindowService.hpp)

set(LIBBACKENDGENERALSRCFILES
    ${SRC_BACKEND_GLEW}
    ${SRC_BACKEND_HASHLIBPP}
    ${SRC_BACKEND_MURMURHASH}
    ${SRC_BACKEND_OPENGL}
    ${SRC_BACKEND_STRINGCODERS}
	)

set(LIBBACKENDGENERALHDRFILES
    ${HDRS_BACKEND}
    ${HDRS_BACKEND_GL}
    ${HDRS_BACKEND_GOOGLE}
    ${HDRS_BACKEND_GOOGLE_SPARSEHASH}
    ${HDRS_BACKEND_HASHLIBPP}
    ${HDRS_BACKEND_LIBPNG}
    ${HDRS_BACKEND_LIBTIFF}
    ${HDRS_BACKEND_MURMURHASH}
    ${HDRS_BACKEND_OPENGL}
    ${HDRS_BACKEND_RADONDDS}
    ${HDRS_BACKEND_STRINGCODERS}
	)

set(LIBBACKENDSRCFILES_WINDOWS
    ${SRC_BACKEND_WINDOWS}
    ${SRC_BACKEND_WINDOWS_DRAWING}
    ${SRC_BACKEND_WINDOWS_FORMS})

set(LIBBACKENDHDRFILES_WINDOWS
    ${HDRS_BACKEND_WINDOWS}
    ${HDRS_BACKEND_WINDOWS_DRAWING}
    ${HDRS_BACKEND_WINDOWS_FORMS})

set(LIBBACKENDSRCFILES_LINUX
    ${SRC_BACKEND_LINUX}
    ${SRC_BACKEND_X11_DRAWING}
    ${SRC_BACKEND_X11_FORMS})

set(LIBBACKENDHDRFILES_LINUX
    ${HDRS_BACKEND_LINUX}
    ${HDRS_BACKEND_X11_DRAWING}
    ${HDRS_BACKEND_X11_FORMS})
	
# these files are excluded on other platforms
set(LIBSRCFILES_WINDOW
	src/System/EnvironmentWindows.cpp
	src/System/MemoryWindows.cpp
	src/System/IO/FileSystemWindows.cpp
	src/System/StringWindows.cpp
	src/System/TimeWindows.cpp
	src/System/ProcessWindows.cpp
	src/System/HardwareWindows.cpp)
	
set(LIBSRCFILES_LINUX
	src/System/TimeLinux.cpp
	src/System/EnvironmentLinux.cpp
	src/System/MemoryLinux.cpp
	src/System/StringLinux.cpp
	src/System/IO/FileSystemLinux.cpp
	src/System/HardwareLinux.cpp)
	
set(LIBSRCFILES_UNIX
	src/System/TimeUnix.cpp
	src/System/ProcessUnix.cpp)
	
set(LIBSRCFILES_OSX
	src/System/TimeOSX.cpp)
	
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
source_group("Sources\\backend\\Glew" FILES ${SRC_BACKEND_GLEW})
source_group("Sources\\backend\\Hashlib++" FILES ${SRC_BACKEND_HASHLIBPP})
source_group("Sources\\backend\\MurmurHash" FILES ${SRC_BACKEND_MURMURHASH})
source_group("Sources\\backend\\OpenGL" FILES ${SRC_BACKEND_OPENGL})
source_group("Sources\\backend\\StringCoders" FILES ${SRC_BACKEND_STRINGCODERS})

# Radon Framework header
source_group("Includes" FILES ${HDRS_ROOT})
source_group("Includes\\backend" FILES ${HDRS_BACKEND})
source_group("Includes\\backend\\GL" FILES ${HDRS_BACKEND_GL})
source_group("Includes\\backend\\Google" FILES ${HDRS_BACKEND_GOOGLE})
source_group("Includes\\backend\\Google\\SparseHash" FILES ${HDRS_BACKEND_GOOGLE_SPARSEHASH})
source_group("Includes\\backend\\Hashlib++" FILES ${HDRS_BACKEND_HASHLIBPP})
source_group("Includes\\backend\\MurmurHash" FILES ${HDRS_BACKEND_MURMURHASH})
source_group("Includes\\backend\\OpenGL" FILES ${HDRS_BACKEND_OPENGL})
source_group("Includes\\backend\\StringCoders" FILES ${HDRS_BACKEND_STRINGCODERS})

# Windows specific source code
source_group("Sources\\backend\\Windows" FILES ${SRC_BACKEND_WINDOWS})
source_group("Sources\\backend\\Windows\\Drawing" FILES ${SRC_BACKEND_WINDOWS_DRAWING})
source_group("Sources\\backend\\Windows\\Forms" FILES ${SRC_BACKEND_WINDOWS_FORMS})

# Windows specific headers
source_group("Includes\\backend\\Windows" FILES ${HDRS_BACKEND_WINDOWS})
source_group("Includes\\backend\\Windows\\Drawing" FILES ${HDRS_BACKEND_WINDOWS_DRAWING})
source_group("Includes\\backend\\Windows\\Forms" FILES ${HDRS_BACKEND_WINDOWS_FORMS})

# Linux specific source code
source_group("Sources\\backend\\Linux" FILES ${SRC_BACKEND_LINUX})
source_group("Sources\\backend\\X11\\Drawing" FILES ${SRC_BACKEND_X11_DRAWING})
source_group("Sources\\backend\\X11\\Forms" FILES ${SRC_BACKEND_X11_FORMS})

# Linux specific headers
source_group("Includes\\backend\\Linux" FILES ${HDRS_BACKEND_LINUX})
source_group("Includes\\backend\\X11\\Drawing" FILES ${HDRS_BACKEND_X11_DRAWING})
source_group("Includes\\backend\\X11\\Forms" FILES ${HDRS_BACKEND_X11_FORMS})

AddSourceDirectoryRecursive(filelist "src/Collections" "Sources\\Collections")
list(APPEND LIBSRCFILES ${filelist})
AddSourceDirectoryRecursive(filelist "src/Core" "Sources\\Core")
list(APPEND LIBSRCFILES ${filelist})
AddSourceDirectoryRecursive(filelist "src/Diagnostics" "Sources\\Diagnostics")
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

AddHeaderDirectoryRecursive(filelist "include/RadonFramework/Reflection" "Includes\\Reflection")
list(APPEND LIBHDRFILES ${filelist})	
AddHeaderDirectoryRecursive(filelist "include/RadonFramework/Collections" "Includes\\Collections")
list(APPEND LIBHDRFILES ${filelist})
AddHeaderDirectoryRecursive(filelist "include/RadonFramework/Core" "Includes\\Core")
list(APPEND LIBHDRFILES ${filelist})
AddHeaderDirectoryRecursive(filelist "include/RadonFramework/Diagnostics" "Includes\\Diagnostics")
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
	
set_source_files_properties(${LIBBACKENDHDRFILES} ${LIBHDRFILES} ${MODULES_HDRS} PROPERTIES HEADER_FILE_ONLY ON)

#
# setup precompiled header
#
CreatePrecompiledHeader(RADONFRAMEWORK "RadonFramework/precompiled.hpp" "src/precompiled.cpp" SourceList)

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

