FIND_PROGRAM(VSGDB_EXECUTABLE VisualGDB PATHS "C:/Program Files (x86)/Sysprogs/VisualGDB/" DOC "VisualGDB.exe")
set(VSGDB_REMOTESERVER CACHE STRING "IP or hostname of the build server")
set(VSGDB_BIN_DIRECTORY "/usr/bin" CACHE STRING "Directory where the GCC executable is located.")
set(VSGDB_GCC ${VSGDB_BIN_DIRECTORY}/gcc CACHE STRING "Directory where the GCC executable is located.")
set(VSGDB_GPP ${VSGDB_BIN_DIRECTORY}/g++ CACHE STRING "Directory where the GCC executable is located.")
set(VSGDB_GDB ${VSGDB_BIN_DIRECTORY}/gdb CACHE STRING "Directory where the GCC executable is located.")
set(VSGDB_MAKE ${VSGDB_BIN_DIRECTORY}/make CACHE STRING "Directory where the GCC executable is located.")
# forward local options to remote system
set(VSGDB_OPTIONS 
	"-DWITH_DRAWING=${WITH_DRAWING} -DWITH_TIFF=${WITH_TIFF} -DWITH_PNG=${WITH_PNG} -DWITH_DRAWING_FORMS=${WITH_DRAWING_FORMS} -DWITH_NET=${WITH_NET} -DWITH_DIAGNOSTICS_PROFILING_PROCESS=${WITH_DIAGNOSTICS_PROFILING_PROCESS} -DWITH_DIAGNOSTICS_PROFILING_SMBIOS=${WITH_DIAGNOSTICS_PROFILING_SMBIOS} -DWITH_DIAGNOSTICS_DEBUGGING_UNITTEST=${WITH_DIAGNOSTICS_DEBUGGING_UNITTEST} -DWITH_REFLECTION=${WITH_REFLECTION}	-DWITH_VISUALGDB=OFF")

configure_file("Debug.vgdbsettings.template" "Debug.vgdbsettings" @ONLY)

add_custom_target(RadonFramework_VisualGDB 
	${VSGDB_EXECUTABLE} "Debug.vgdbsettings"
	WORKING_DIRECTORY ${PROJECT_BINARY_DIR}
	SOURCES 
		${LIBSRCFILES} ${LIBHDRFILES} ${LIBBACKENDHDRFILES} 
		${LIBBACKENDSRCFILES} ${MODULES_SRC} ${MODULES_HDRS} 
		"libRadonFramework.cmake" "libRadonFramework_VGDB.cmake")