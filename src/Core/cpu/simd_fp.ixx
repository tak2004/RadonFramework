module;
#include <concepts>
export module rf.core.cpu:simd_fp;
import rf.core.types;
import :infos;
import :simd;

export namespace rf {

    template<std::floating_point SIMDTYPE>
    size detectMaxSIMDWidth()
    {
        Features WidthFeatures[] = { Features::SSE2 , Features::AVX2 , Features::AVX512F };
        size Width[] = { 16, 32, 64 };
        size maxWidth = 8;// u64
        for (auto i = 0; i < sizeof(WidthFeatures); ++i)
            if (CPUFeatures.has(WidthFeatures[i]))
                maxWidth = Width[i];
        return maxWidth;
    }



} // namespace rf