project(SystemTest)
cmake_minimum_required(VERSION 2.8)

include("../../cmake/extern/Generate.cmake")
Integrate(RADONFRAMEWORK "Radon framework" "RADONFRAMEWORK_HOME")

AddSourceDirectoryRecursive(filelist "src" "Source")
CreatePrecompiledHeader(RADONFRAMEWORK_SYSTEMTEST "precompiled.hpp" "src/precompiled.cpp" filelist)
set(RADONFRAMEWORK_SYSTEMTEST_FILES ${filelist})
Generate(EXECUTABLE RADONFRAMEWORK_SYSTEMTEST SystemTest "Framework")
target_include_directories(SystemTest PRIVATE src/)
Finalize(RADONFRAMEWORK_SYSTEMTEST)