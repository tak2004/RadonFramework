module;
#include <intrin.h>
export module rf.core.cpu:simd_bits;
import rf.core.types;
import :infos;
import :simd;

rf::size nextSet_SSE(const rf::bits& Bits, rf::size Offset){
    auto a = _mm_stream_load_si128(reinterpret_cast<const __m128i*>(Bits.memory.address));
    auto b = _mm_lzcnt_epi64(a);

    return 0;
}

rf::size nextSet_AVX2(const rf::bits& Bits, rf::size Offset){
    auto a = _mm256_stream_load_si256(reinterpret_cast<const __m256i*>(Bits.memory.address));
    auto b = _mm256_lzcnt_epi64(a);
    return 0;
}

rf::size nextSet_AVX512F(const rf::bits& Bits, rf::size Offset){
    auto a = _mm512_stream_load_si512(Bits.memory.address);
    auto b = _mm512_lzcnt_epi64(a);
    return 0;
}

rf::size nextUnset_SSE41(const rf::bits& Bits, rf::size Offset, rf::size OffsetEnd) {
    rf::u8* p = reinterpret_cast<rf::u8*>(Bits.memory.address);
    rf::u8* pEnd = p + (OffsetEnd / 8);
    __m128i v1, v2;
    while (p < pEnd ) {
        v1 = _mm_stream_load_si128(reinterpret_cast<const __m128i*>(p));
        v2 = _mm_stream_load_si128(reinterpret_cast<const __m128i*>(p+16));
        auto vand = _mm_and_si128(v1, v2);
        if (_mm_test_all_ones(vand) == 0)
            break;
        p += 32;
    }
    rf::size i = (reinterpret_cast<rf::ptrdiff>(p) - reinterpret_cast<rf::ptrdiff>(Bits.memory.address))*8;
    for (; i < OffsetEnd; ++i) {
        if (Bits[i] == false)
            break;
    }
    return i;
}

rf::size nextUnset_Bytes(const rf::bits& Bits, rf::size Offset, rf::size OffsetEnd) {
    rf::size i = Offset;
    for (; i < OffsetEnd; ++i) {
        if (Bits[i] == false)
            break;
    }
    return i;
}

export namespace rf {
size (*nextSet)(const bits& Bits, size Offset) = []() {

    return nextSet_SSE;
}();
size (*nextUnset)(const bits& Bits, size Offset, size OffsetEnd) = [](const bits& Bits, size Offset, size OffsetEnd) -> size {
    if (CPUFeatures.has(Features::SSE4_1))
        nextUnset = nextUnset_SSE41;
    else
        nextUnset = nextUnset_Bytes;
    return nextUnset(Bits, Offset, OffsetEnd);
};

template<>
size detectMaxSIMDWidth<bits>()
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