cmake_minimum_required(VERSION 4.0)
project(rf_tests VERSION 2.0.0 LANGUAGES CXX)

file(GLOB_RECURSE RF_CONFORMANCE_FILES "${RF_LOCATION}/tests/conformance/*.cpp")
add_executable(conformance_test ${RF_CONFORMANCE_FILES})
target_include_directories(conformance_test PUBLIC doctest)
target_compile_features(conformance_test PRIVATE cxx_std_20)
target_link_libraries(conformance_test PRIVATE rf::core)

file(GLOB_RECURSE RF_SMOKETEST_FILES "${RF_LOCATION}/tests/smoketest/*.cpp")
add_executable(smoke_test ${RF_SMOKETEST_FILES})
target_include_directories(smoke_test PUBLIC doctest)
target_compile_features(smoke_test PRIVATE cxx_std_20)
target_link_libraries(smoke_test PRIVATE rf::core)
