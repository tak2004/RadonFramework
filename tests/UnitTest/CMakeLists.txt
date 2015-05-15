project(UnitTest)
cmake_minimum_required(VERSION 2.8)

Integrate(RADONFRAMEWORK "Radon framework" "RADONFRAMEWORK_HOME")

AddSourceDirectoryRecursive(filelist "src" "Source")
CreatePrecompiledHeader(RADONFRAMEWORK_UNITTEST "precompiled.hpp" "src/precompiled.cpp" filelist)
set(RADONFRAMEWORK_UNITTEST_FILES ${filelist})
Generate(EXECUTABLE RADONFRAMEWORK_UNITTEST UnitTest "Framework")
target_include_directories(UnitTest PRIVATE src/)
AddDependency(RADONFRAMEWORK_UNITTEST RadonFramework)
Finalize(RADONFRAMEWORK_UNITTEST)