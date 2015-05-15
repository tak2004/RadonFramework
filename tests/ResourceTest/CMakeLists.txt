project(ResourceTest)
cmake_minimum_required(VERSION 2.8)

Integrate(RADONFRAMEWORK "Radon framework" "RADONFRAMEWORK_HOME")

AddSourceDirectoryRecursive(filelist "src" "Source")
CreatePrecompiledHeader(RADONFRAMEWORK_RESOURCETEST "precompiled.hpp" "src/precompiled.cpp" filelist)
set(RADONFRAMEWORK_RESOURCETEST_FILES ${filelist})
Generate(EXECUTABLE RADONFRAMEWORK_RESOURCETEST ResourceTest "Framework")
target_include_directories(ResourceTest PRIVATE src/)
AddDependency(RADONFRAMEWORK_RESOURCETEST RadonFramework)
Finalize(RADONFRAMEWORK_RESOURCETEST)