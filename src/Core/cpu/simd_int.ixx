module;
#include <intrin.h>
#include <concepts>
export module rf.core.cpu:simd_int;
import rf.core.types;
import :infos;
import :simd;

rf::size find_u32_SSE(rf::SIMDView<rf::u32> Source, rf::u32 Value)
{
    __m128i a, b;
    a = _mm_load_si128(reinterpret_cast<const __m128i*>(Source.memory.address));
    b = _mm_set1_epi32(Value);
    a = _mm_cmpeq_epi32(a, b);
    return _mm_movemask_epi8(a);
}

export namespace rf {
    size(*find)(SIMDView<u32> Source, u32 Value) = [](SIMDView<u32> Source, u32 Value) -> size {
        find = find_u32_SSE;
        return find(Source, Value);
    };

    template<std::integral SIMDTYPE>
    size detectMaxSIMDWidth()
    {
        constexpr Features WidthFeatures[] = { Features::SSE2 , Features::AVX2 , Features::AVX512F };
        constexpr size Width[] = { 16, 32, 64 };
        size maxWidth = 8;// u64
        for (auto i = 0; i < sizeof(WidthFeatures); ++i)
            if (CPUFeatures.has(WidthFeatures[i]))
                maxWidth = Width[i];
        return maxWidth;
    }
} // namespace rf