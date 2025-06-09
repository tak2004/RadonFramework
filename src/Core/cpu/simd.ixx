export module rf.core.cpu:simd;
import rf.core.types;

export namespace rf {

template<class SIMDTYPE>
size detectMaxSIMDWidth() {
	static_assert(true, "Type isn't supported yet!");
}

i32 compare_(const constmem &a, const constmem &b) { return 0; }

i32 (*compare)(const constmem &a, const constmem &b) = &compare_;
} // namespace rf