AddSourceDirectoryRecursive(filelist "src" "Source")
CreatePrecompiledHeader(RADONFRAMEWORK_UNITTEST "precompiled.hpp" "src/precompiled.cpp" filelist)

set(RADONFRAMEWORK_UNITTEST_FILES ${filelist})
if(NOT RADONFRAMEWORK_EXPERIMENTAL_HASHLIST)
    list(REMOVE_ITEM RADONFRAMEWORK_UNITTEST_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/Collections/HashList.cpp)
endif()

Generate(EXECUTABLE RADONFRAMEWORK_UNITTEST UnitTest "Framework")
target_include_directories(UnitTest PRIVATE src/)
AddDependency(RADONFRAMEWORK_UNITTEST RadonFramework)
Finalize(RADONFRAMEWORK_UNITTEST)