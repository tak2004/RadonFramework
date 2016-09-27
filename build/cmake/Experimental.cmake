if(RADONFRAMEWORK_ENABLE_EXPERIMENTAL_CODE)
    OPTION(RADONFRAMEWORK_EXPERIMENTAL_HTTP "Enable HTTP namespace." OFF)
    OPTION(RADONFRAMEWORK_EXPERIMENTAL_ALLOCATOR "Enable Allocator class." OFF)
    OPTION(RADONFRAMEWORK_EXPERIMENTAL_JIT "Enable JIT support." OFF)
    OPTION(RADONFRAMEWORK_EXPERIMENTAL_GRAMMAR "Enables the new grammar and VM api." OFF)
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