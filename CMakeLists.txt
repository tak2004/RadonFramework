cmake_minimum_required(VERSION 4.0)    
project(RadonFramework VERSION 2.0.0 LANGUAGES CXX)
set(RF_LOCATION ${CMAKE_CURRENT_SOURCE_DIR})
set(RF_ADD_TESTS ON CACHE BOOL "" FORCE)
set(RF_ADD_EXAMPLES ON CACHE BOOL "" FORCE)

# General framework options.
option(RF_ADD_TESTS "Add the framework specific tests." OFF)
option(RF_ADD_EXAMPLES "Add the framework specific examples." OFF)

set(ASMJIT_STATIC TRUE)
set(ASMJIT_NO_FOREIGN TRUE)
set(ASMJIT_NO_AARCH64 TRUE)
set(ASMJIT_DIR "${RF_LOCATION}/3rdparty/asmjit")
add_subdirectory("${RF_LOCATION}/3rdparty/asmjit/")

add_library(rf_core)
file(GLOB_RECURSE RF_CORE_MODULES
    "${RF_LOCATION}/src/core/*.ixx")
target_sources(rf_core PUBLIC FILE_SET CXX_MODULES FILES "${RF_CORE_MODULES}")
add_library(rf::core ALIAS rf_core)
source_group(TREE ${RF_LOCATION}/src/ FILES ${RF_CORE_MODULES})
set_target_properties(rf_core PROPERTIES LINKER_LANGUAGE CXX)
target_compile_features(rf_core PRIVATE cxx_std_20)
target_include_directories(rf_core PUBLIC "${RF_LOCATION}/3rdparty/xxhash/")
target_include_directories(rf_core PUBLIC "${RF_LOCATION}/3rdparty/rapidhash/")

add_library(rf_ui)
file(GLOB_RECURSE RF_UI_MODULES
    "${RF_LOCATION}/src/ui/*.ixx")
target_sources(rf_ui PUBLIC FILE_SET CXX_MODULES FILES "${RF_UI_MODULES}")
add_library(rf::ui ALIAS rf_ui)
source_group(TREE ${RF_LOCATION}/src/ FILES ${RF_UI_MODULES})
set_target_properties(rf_ui PROPERTIES LINKER_LANGUAGE CXX)
target_compile_features(rf_ui PRIVATE cxx_std_20)
target_link_libraries(rf_ui PRIVATE rf::core setupapi.lib)

add_library(rf_pixels)
file(GLOB_RECURSE RF_PIXELS_MODULES
    "${RF_LOCATION}/src/pixels/*.ixx")
target_sources(rf_pixels PUBLIC FILE_SET CXX_MODULES FILES "${RF_PIXELS_MODULES}")
add_library(rf::pixels ALIAS rf_pixels)
source_group(TREE ${RF_LOCATION}/src/ FILES ${RF_PIXELS_MODULES})
set_target_properties(rf_pixels PROPERTIES LINKER_LANGUAGE CXX)
target_compile_features(rf_pixels PRIVATE cxx_std_20)
target_link_libraries(rf_pixels PRIVATE rf::core asmjit::asmjit)

if(RF_ADD_TESTS)
    add_subdirectory("${RF_LOCATION}/tests")
endif()
if(RF_ADD_EXAMPLES)
    add_subdirectory("${RF_LOCATION}/examples")
endif()