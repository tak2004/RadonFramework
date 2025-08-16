cmake_minimum_required(VERSION 4.0)
project(rf_examples VERSION 2.0.0 LANGUAGES CXX)

file(GLOB_RECURSE RF_MEMORY_FILES "${RF_LOCATION}/examples/memory/*.cpp")
add_executable(memory_example ${RF_MEMORY_FILES})
target_compile_features(memory_example PRIVATE cxx_std_20)
target_link_libraries(memory_example PRIVATE rf::core)

file(GLOB_RECURSE RF_NETWORK_FILES "${RF_LOCATION}/examples/network/*.cpp")
add_executable(network_example ${RF_NETWORK_FILES})
target_compile_features(network_example PRIVATE cxx_std_20)
target_link_libraries(network_example PRIVATE rf::core IPHLPAPI.lib Ws2_32.lib)

file(GLOB_RECURSE RF_THREADING_FILES "${RF_LOCATION}/examples/threading/*.cpp")
add_executable(threading_example ${RF_THREADING_FILES})
target_compile_features(threading_example PRIVATE cxx_std_20)
target_link_libraries(threading_example PRIVATE rf::core)

file(GLOB_RECURSE RF_FILESYSTEM_FILES "${RF_LOCATION}/examples/filesystem/*.cpp")
add_executable(filesystem_example ${RF_FILESYSTEM_FILES})
target_compile_features(filesystem_example PRIVATE cxx_std_20)
target_link_libraries(filesystem_example PRIVATE rf::core)

file(GLOB_RECURSE RF_FORMS_FILES "${RF_LOCATION}/examples/forms/*.cpp")
add_executable(forms_example ${RF_FORMS_FILES})
target_compile_features(forms_example PRIVATE cxx_std_20)
target_link_libraries(forms_example PRIVATE rf::core rf::ui rf::pixels)