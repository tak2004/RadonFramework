message(STATUS "Generate ${RadonFramework_SOURCE_DIR}/include/RadonFramework/RadonInline.hpp")

macro(GenerateIncludes variable files)
	foreach(includefile ${files})
		STRING(REGEX REPLACE "${CMAKE_CURRENT_SOURCE_DIR}/include/" "" escaped_includefile ${includefile}) 
		set(${variable} "${${variable}}\n#include <${escaped_includefile}>")
	endforeach()
endmacro()

AddHeaderDirectoryRecursive(filelist "include/RadonFramework/Reflection" "Includes\\Reflection")
list(REMOVE_ITEM filelist ${RADONFRAMEWORK_BLACKLIST})
GenerateIncludes(INCLUDES_REFLECTION "${filelist}")

AddHeaderDirectoryRecursive(filelist "include/RadonFramework/Collections" "Includes\\Collections")
list(REMOVE_ITEM filelist ${RADONFRAMEWORK_BLACKLIST})
GenerateIncludes(INCLUDES_COLLECTIONS "${filelist}")

AddHeaderDirectoryRecursive(filelist "include/RadonFramework/Core" "Includes\\Core")
list(REMOVE_ITEM filelist ${RADONFRAMEWORK_BLACKLIST})
GenerateIncludes(INCLUDES_CORE "${filelist}")

AddHeaderDirectoryRecursive(filelist "include/RadonFramework/Diagnostics" "Includes\\Diagnostics")
list(REMOVE_ITEM filelist ${RADONFRAMEWORK_BLACKLIST})
GenerateIncludes(INCLUDES_DIAGNOSTICS "${filelist}")

AddHeaderDirectoryRecursive(filelist "include/RadonFramework/Math" "Includes\\Math")
list(REMOVE_ITEM filelist ${RADONFRAMEWORK_BLACKLIST})
GenerateIncludes(INCLUDES_MATH "${filelist}")

AddHeaderDirectoryRecursive(filelist "include/RadonFramework/IO" "Includes\\IO")
list(REMOVE_ITEM filelist ${RADONFRAMEWORK_BLACKLIST})
GenerateIncludes(INCLUDES_IO "${filelist}")

AddHeaderDirectoryRecursive(filelist "include/RadonFramework/Memory" "Includes\\Memory")
list(REMOVE_ITEM filelist ${RADONFRAMEWORK_BLACKLIST})
GenerateIncludes(INCLUDES_MEMORY "${filelist}")

AddHeaderDirectoryRecursive(filelist "include/RadonFramework/System" "Includes\\System")
list(REMOVE_ITEM filelist ${RADONFRAMEWORK_BLACKLIST})
GenerateIncludes(INCLUDES_SYSTEM "${filelist}")

AddHeaderDirectoryRecursive(filelist "include/RadonFramework/Threading" "Includes\\Threading")
list(REMOVE_ITEM filelist ${RADONFRAMEWORK_BLACKLIST})
GenerateIncludes(INCLUDES_THREADING "${filelist}")

AddHeaderDirectoryRecursive(filelist "include/RadonFramework/Time" "Includes\\Time")
list(REMOVE_ITEM filelist ${RADONFRAMEWORK_BLACKLIST})
GenerateIncludes(INCLUDES_TIME "${filelist}")

AddHeaderDirectoryRecursive(filelist "include/RadonFramework/Net" "Includes\\Net")
list(REMOVE_ITEM filelist ${RADONFRAMEWORK_BLACKLIST})
GenerateIncludes(INCLUDES_NET "${filelist}")

AddHeaderDirectoryRecursive(filelist "include/RadonFramework/Drawing" "Includes\\Drawing")
list(REMOVE_ITEM filelist ${RADONFRAMEWORK_BLACKLIST})
GenerateIncludes(INCLUDES_DRAWING "${filelist}")

AddHeaderDirectoryRecursive(filelist "include/RadonFramework/Text" "Includes\\Text")
list(REMOVE_ITEM filelist ${RADONFRAMEWORK_BLACKLIST})
GenerateIncludes(INCLUDES_TEXT "${filelist}")

AddHeaderDirectoryRecursive(filelist "include/RadonFramework/Util" "Includes\\Util")
list(REMOVE_ITEM filelist ${RADONFRAMEWORK_BLACKLIST})
GenerateIncludes(INCLUDES_UTIL "${filelist}")
configure_file("build/code_templates/RadonInline.hxx" "${RadonFramework_SOURCE_DIR}/include/RadonFramework/RadonInline.hpp" @ONLY)

message(STATUS "Generate include/RadonFramework/Defines.hpp")
configure_file("build/code_templates/Defines.hxx" "include/RadonFramework/Defines.hpp" @ONLY)
set(RADONFRAMEWORK_ENDIANNESS ${RadonFramework_ENDIANNESS})
set(RADONFRAMEWORK_COMPILEDFORARCHITECTURE ${RadonFramework_COMPILEDFORARCHITECTURE})
message(STATUS "Generate src/System/CompilerConfig.cpp")
configure_file("build/code_templates/CompilerConfig.cxx" "src/System/CompilerConfig.cpp" @ONLY)

message(STATUS "Generate include/RadonFramework/Math/Geometry/QuatF32.hpp")
set(GuardName "QUATF32")
set(ClassName "QuatF32")
set(ClassType "RF_Type::Float32")
set(MathType "Float32")
configure_file("build/code_templates/Quaternion.hxx" "include/RadonFramework/Math/Geometry/QuatF32.hpp" @ONLY)
configure_file("build/code_templates/Quaternion.cxx" "src/Math/Geometry/QuatF32.cpp" @ONLY)

message(STATUS "Generate include/RadonFramework/Math/Geometry/QuatF64.hpp")
set(GuardName "QUATF64")
set(ClassName "QuatF64")
set(ClassType "RF_Type::Float64")
set(MathType "Float64")
configure_file("build/code_templates/Quaternion.hxx" "include/RadonFramework/Math/Geometry/QuatF64.hpp" @ONLY)
configure_file("build/code_templates/Quaternion.cxx" "src/Math/Geometry/QuatF64.cpp" @ONLY)