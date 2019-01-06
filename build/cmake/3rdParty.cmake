if(RADONFRAMEWORK_ADD_XXHASH)
    rcf_addpackage(xxhash)
else()
    list(APPEND RADONFRAMEWORK_BLACKLIST ${CMAKE_CURRENT_SOURCE_DIR}/include/RadonFramework/System/Math/Hash/xxHashService.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/System/Math/Hash/xxHashService.cpp)
endif()

if(RADONFRAMEWORK_EXPERIMENTAL_JIT)
    rcf_addlocation(ASMJIT "git" "https://github.com/kobalicek/asmjit.git")
    rcf_obtain_project(ASMJIT outdir "286bc22f4912417f95cbf49879c475abb7b6f990")
    add_subdirectory(${outdir} ${outdir})
endif()