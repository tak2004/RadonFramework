rcf_addlocation(XXHASH "git" "https://github.com/Cyan4973/xxHash.git")

rcf_obtain_project(XXHASH outdir "86011828f0fc77ad4d83ecfb1df88a91ebc37083")
add_subdirectory("${outdir}/cmake_unofficial/" "${outdir}")

if(RADONFRAMEWORK_EXPERIMENTAL_JIT)
    rcf_addlocation(ASMJIT "git" "https://github.com/kobalicek/asmjit.git")
    rcf_obtain_project(ASMJIT outdir "286bc22f4912417f95cbf49879c475abb7b6f990")
    add_subdirectory(${outdir} ${outdir})
endif()