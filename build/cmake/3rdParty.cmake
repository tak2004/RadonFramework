# libmorton is used by an octree implementation
rcf_addpackage(morton)

if(RADONFRAMEWORK_ADD_XXHASH)
    rcf_addpackage(xxhash)
#    rcf_addlocation(XXHASH "git" "https://github.com/Cyan4973/xxHash.git")
#    rcf_obtain_project(XXHASH outdir "5ab73ee82245b586f69762411edc7824d778ee2a")
#    set(BUILD_SHARED_LIBS OFF CACHE BOOL "Set to ON to build shared libraries" FORCE)
#    set(BUILD_XXHSUM OFF CACHE BOOL "Set to ON to build command line tool" FORCE)
#    add_subdirectory("${outdir}/cmake_unofficial/" ${outdir})
#    AddPublicInclude(XXHASH ${outdir}/)
#    GenerateCustomTargetMetaInfo(MODULE xxhash XXHASH "3rd Party Libraries")
#    FinalizeCustomTargetMetaInfo(XXHASH)
else()
    list(APPEND RADONFRAMEWORK_BLACKLIST ${CMAKE_CURRENT_SOURCE_DIR}/include/RadonFramework/System/Math/Hash/xxHashService.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/System/Math/Hash/xxHashService.cpp)
endif()

if(RADONFRAMEWORK_EXPERIMENTAL_JIT)
    rcf_addlocation(ASMJIT "git" "https://github.com/kobalicek/asmjit.git")
    rcf_obtain_project(ASMJIT outdir "286bc22f4912417f95cbf49879c475abb7b6f990")
    add_subdirectory(${outdir} ${outdir})
endif()

# libtess2 is used in the path tesselation
rcf_addlocation(LIBTESS2 "git" "https://github.com/memononen/libtess2.git")
rcf_obtain_project(LIBTESS2 outdir "24e4bdd4158909e9720422208ab0a0aca788e700")
AddSourceDirectoryRecursive(filelist "${outdir}/Source" "Source")
list(APPEND LIBTESS2_FILES ${filelist})	
AddHeaderDirectoryRecursive(filelist "${outdir}/Source" "Includes")
list(APPEND LIBTESS2_FILES ${filelist})	
Generate(MODULE LIBTESS2 libtess2 "3rd Party Libraries")
AddPublicInclude(LIBTESS2 ${outdir}/Include/)
Finalize(LIBTESS2)
