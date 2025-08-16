module;
#include <intrin.h>
export module rf.core.cpu:simd;
import rf.core.types;

[[nodiscard]] rf::i32 compare_sse(rf::constmem SourceA, rf::constmem SourceB) {
    if (SourceA.address == SourceB.address) {
        return 0;
    }
    __m128i* ptr1 = reinterpret_cast<__m128i*>(const_cast<void*>(SourceA.address));
    __m128i* ptr2 = reinterpret_cast<__m128i*>(const_cast<void*>(SourceB.address));
    for (/**/; /**/; ptr1++, ptr2++) {
        const __m128i a = _mm_loadu_si128(ptr1);
        const __m128i b = _mm_loadu_si128(ptr2);

        const rf::u8 mode =
            _SIDD_UBYTE_OPS | _SIDD_CMP_EQUAL_EACH | _SIDD_NEGATIVE_POLARITY | _SIDD_LEAST_SIGNIFICANT;

        if (_mm_cmpistrc(a, b, mode)) {
            // a & b are different (not counting past-zero bytes)
            const auto idx = _mm_cmpistri(a, b, mode);
            const rf::u8 b1 = (reinterpret_cast<char*>(ptr1))[idx];
            const rf::u8 b2 = (reinterpret_cast<char*>(ptr2))[idx];
            if (b1 < b2) {
                return -1;
            }
            else if (b1 > b2) {
                return +1;
            }
            else {
                return 0;
            }
        }
        else if (_mm_cmpistrz(a, b, mode)) {
            // a & b are same, but b contains a zero byte
            break;
        }
    }
    return 0;
}

export namespace rf {

template<class SIMDTYPE>
size detectMaxSIMDWidth() {
	static_assert(true, "Type isn't supported yet!");
}

template<rf::ReadonlyView A, rf::ReadonlyView B>
[[nodiscard]] __forceinline i32 compare(A SourceA, B SourceB) {
	static i32(*pimpl)(constmem SourceA, constmem SourceB) =
		[](constmem SourceA, constmem SourceB)->i32 {
			pimpl = compare_sse;
			return pimpl(SourceA, SourceB);
		};
    return pimpl(constmem{ .address = SourceA.address, .bytes = SourceA.bytes }, 
        constmem{ .address = SourceB.address, .bytes = SourceB.bytes });
}
} // namespace rf