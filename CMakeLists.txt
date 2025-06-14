cmake_minimum_required(VERSION 4.0)    
project(RadonFramework VERSION 2.0.0 LANGUAGES CXX)
set(RF_LOCATION ${CMAKE_CURRENT_SOURCE_DIR})
set(RF_ADD_TESTS ON CACHE BOOL "" FORCE)
set(RF_ADD_EXAMPLES ON CACHE BOOL "" FORCE)

# General framework options.
option(RF_ADD_TESTS "Add the framework specific tests." OFF)
option(RF_ADD_EXAMPLES "Add the framework specific examples." OFF)

add_library(umash STATIC "${RF_LOCATION}/3rdparty/umash/umash.c")
set_target_properties(umash PROPERTIES LINKER_LANGUAGE CXX)
target_include_directories(umash PUBLIC "${RF_LOCATION}/3rdparty/umash/")

add_library(rf_core)
file(GLOB_RECURSE RF_CORE_MODULES
    "${RF_LOCATION}/src/core/*.ixx")
target_sources(rf_core PUBLIC FILE_SET CXX_MODULES FILES "${RF_CORE_MODULES}")
add_library(rf::core ALIAS rf_core)
source_group(TREE ${RF_LOCATION}/src/ FILES ${RF_CORE_MODULES})
set_target_properties(rf_core PROPERTIES LINKER_LANGUAGE CXX)
target_compile_features(rf_core PRIVATE cxx_std_20)
target_link_libraries(rf_core PRIVATE umash)

add_library(rf_ui)
file(GLOB_RECURSE RF_UI_MODULES
    "${RF_LOCATION}/src/ui/*.ixx")
target_sources(rf_ui PUBLIC FILE_SET CXX_MODULES FILES "${RF_UI_MODULES}")
add_library(rf::ui ALIAS rf_ui)
source_group(TREE ${RF_LOCATION}/src/ FILES ${RF_UI_MODULES})
set_target_properties(rf_ui PROPERTIES LINKER_LANGUAGE CXX)
target_compile_features(rf_ui PRIVATE cxx_std_20)
target_link_libraries(rf_ui PRIVATE rf::core)

if(RF_ADD_TESTS)
    add_subdirectory("${RF_LOCATION}/tests")
endif()
if(RF_ADD_EXAMPLES)
    add_subdirectory("${RF_LOCATION}/examples")
endif()