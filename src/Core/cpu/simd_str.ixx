module;
#include <intrin.h>
#include <concepts>
export module rf.core.cpu:simd_str;
import rf.core.types;
import :infos;

rf::size findFirstOf_ansi_sse(rf::constmem Source, rf::ansi Value, rf::size Offset=0){
    auto* p = reinterpret_cast<const __m256i*>(Source.address);
    __m256i v = _mm256_set1_epi8(Value);
    __m256i r = _mm256_load_si256(p);
    __m256i cmp = _mm256_cmpeq_epi8(r, v);
    rf::u32 mask = _mm256_movemask_epi8(cmp);
    mask = mask >> Offset << Offset;
    return _tzcnt_u32(mask);
}

export namespace rf {

template<rf::ReadonlyView C>
__forceinline size findFirstOf(C Source, ansi Value, size Offset) { 
    static size(*pimpl)(constmem Source, ansi Value, size Offset) =
        [](constmem Source, ansi Value, size Offset) -> size {
            pimpl = findFirstOf_ansi_sse;
            return pimpl(Source, Value, Offset);
        };
    return pimpl(constmem{ .address = Source.address , .bytes = Source.bytes}, Value, Offset);
}

template<View SIMDTYPE>
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
}