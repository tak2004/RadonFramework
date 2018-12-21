if(RADONFRAMEWORK_ENABLE_EXPERIMENTAL_CODE)
    OPTION(RADONFRAMEWORK_EXPERIMENTAL_HTTP "Enable HTTP namespace." OFF)
    OPTION(RADONFRAMEWORK_EXPERIMENTAL_ALLOCATOR "Enable Allocator class." OFF)
    OPTION(RADONFRAMEWORK_EXPERIMENTAL_JIT "Enable JIT support." OFF)
    OPTION(RADONFRAMEWORK_EXPERIMENTAL_GRAMMAR "Enables the new grammar and VM api." OFF)
    OPTION(RADONFRAMEWORK_EXPERIMENTAL_MODULES "Enables the new modules of C++20." OFF)
endif()

if(NOT RADONFRAMEWORK_EXPERIMENTAL_HTTP)
    AddSourceDirectoryRecursive(src "src/Net/HTTP" "Sources\\Net\\HTTP")
    AddHeaderDirectoryRecursive(headers "include/RadonFramework/Net/HTTP" "Includes\\Net\\HTTP")
    list(APPEND RADONFRAMEWORK_BLACKLIST ${headers} ${src})
endif()

if(NOT RADONFRAMEWORK_EXPERIMENTAL_ALLOCATOR)
    list(APPEND RADONFRAMEWORK_BLACKLIST ${CMAKE_CURRENT_SOURCE_DIR}/include/RadonFramework/Memory/Allocator.hpp ${CMAKE_CURRENT_SOURCE_DIR}/src/Memory/Allocator.cpp)
endif()

if(NOT RADONFRAMEWORK_EXPERIMENTAL_GRAMMAR)
    list(APPEND RADONFRAMEWORK_BLACKLIST ${CMAKE_CURRENT_SOURCE_DIR}/include/RadonFramework/System/VM/ByteCodeInstructions.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/include/RadonFramework/System/VM/CppVM.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/include/RadonFramework/Text/Grammar.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/include/RadonFramework/Text/GrammarExpression.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/include/RadonFramework/Text/LogicElement.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/Text/Grammar.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/Text/GrammarExpression.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/Text/LogicElement.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/System/VM/CppVM.cpp)
endif()

if(RADONFRAMEWORK_EXPERIMENTAL_MODULES)
    set(RADONFRAMEWORK_SYSTEM_MODULE_COMPILER_EXPORT_AS_MODULE ON CACHE BOOL "Generate the project as module(Default: off)" FORCE)
    rcf_generate(module RADONFRAMEWORK_SYSTEM_MODULE RadonFrameworkSystemModule "Framework/RadonFramework Modules" ${CMAKE_CURRENT_SOURCE_DIR}/src/Modules/RadonFramework.System.mpp)
    rcf_endgenerate()

    set(RADONFRAMEWORK_CORE_COMMON_MODULE_COMPILER_EXPORT_AS_MODULE ON CACHE BOOL "Generate the project as module(Default: off)" FORCE)
    rcf_generate(module RADONFRAMEWORK_CORE_COMMON_MODULE RadonFrameworkCoreCommonModule "Framework/RadonFramework Modules" ${CMAKE_CURRENT_SOURCE_DIR}/src/Modules/RadonFramework.Core.Common.mpp)
    rcf_endgenerate()

    set(RADONFRAMEWORK_CORE_TYPES_MODULE_COMPILER_EXPORT_AS_MODULE ON CACHE BOOL "Generate the project as module(Default: off)" FORCE)
    rcf_generate(module RADONFRAMEWORK_CORE_TYPES_MODULE RadonFrameworkCoreTypesModule "Framework/RadonFramework Modules" ${CMAKE_CURRENT_SOURCE_DIR}/src/Modules/RadonFramework.Core.Types.mpp)
    rcf_endgenerate()

    set(RADONFRAMEWORK_COLLECTIONS_MODULE_COMPILER_EXPORT_AS_MODULE ON CACHE BOOL "Generate the project as module(Default: off)" FORCE)
    rcf_generate(module RADONFRAMEWORK_COLLECTIONS_MODULE RadonFrameworkCollectionsModule "Framework/RadonFramework Modules" ${CMAKE_CURRENT_SOURCE_DIR}/src/Modules/RadonFramework.Collections.mpp)
    rcf_endgenerate()

    set(RADONFRAMEWORK_CORE_MODULE_COMPILER_EXPORT_AS_MODULE ON CACHE BOOL "Generate the project as module(Default: off)" FORCE)
    rcf_generate(module RADONFRAMEWORK_CORE_MODULE RadonFrameworkCoreModule "Framework/RadonFramework Modules" ${CMAKE_CURRENT_SOURCE_DIR}/src/Modules/RadonFramework.Core.mpp)
        rcf_dependencies(RadonFrameworkCoreCommonModule RadonFrameworkCoreTypesModule)
    rcf_endgenerate()

    set(RADONFRAMEWORK_DIAGNOSTICS_TEST_MODULE_COMPILER_EXPORT_AS_MODULE ON CACHE BOOL "Generate the project as module(Default: off)" FORCE)
    rcf_generate(module RADONFRAMEWORK_DIAGNOSTICS_TEST_MODULE RadonFrameworkDiagnosticsTestModule "Framework/RadonFramework Modules" ${CMAKE_CURRENT_SOURCE_DIR}/src/Modules/RadonFramework.Diagnostics.Test.mpp)
        rcf_dependencies(RadonFrameworkCollectionsModule RadonFrameworkCoreTypesModule)
    rcf_endgenerate()

    set(RADONFRAMEWORK_IO_MODULE_COMPILER_EXPORT_AS_MODULE ON CACHE BOOL "Generate the project as module(Default: off)" FORCE)
    rcf_generate(module RADONFRAMEWORK_IO_MODULE RadonFrameworkIOModule "Framework/RadonFramework Modules" ${CMAKE_CURRENT_SOURCE_DIR}/src/Modules/RadonFramework.IO.mpp)
    rcf_endgenerate()

    set(RADONFRAMEWORK_MODULE_COMPILER_EXPORT_AS_MODULE ON CACHE BOOL "Generate the project as module(Default: off)" FORCE)
    rcf_generate(module RADONFRAMEWORK_MODULE RadonFrameworkModule "Framework/RadonFramework Modules" ${CMAKE_CURRENT_SOURCE_DIR}/src/Modules/RadonFramework.mpp)
        rcf_dependencies(RadonFrameworkSystemModule RadonFrameworkCoreModule)
    rcf_endgenerate()
endif()