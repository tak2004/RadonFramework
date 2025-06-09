export module rf.core.types:memory;
export import :builtin;

export namespace rf {
struct mem {
  ptr address;
  size bytes;
};

struct constmem {
  constptr address;
  size bytes;
};

struct memmap {
  ptr handle;
  size bytes;
};

mem slice(mem Memory, size ByteOffsetStart, size ByteOffsetEnd = 0){
	return {reinterpret_cast<ptr>(
				reinterpret_cast<ptrdiff>(Memory.address)+ByteOffsetStart), 
			Memory.bytes-(ByteOffsetStart+ByteOffsetEnd)};
}

constmem slice(constmem Memory, size ByteOffsetStart, size ByteOffsetEnd = 0) {
	return { reinterpret_cast<ptr>(
				reinterpret_cast<ptrdiff>(Memory.address) + ByteOffsetStart),
			Memory.bytes - (ByteOffsetStart + ByteOffsetEnd) };
}

template<class T>
T& offset(mem Memory, size Elements) { 
	return reinterpret_cast<T*>(Memory.address)[Elements]; 
}

template<class T>
mem align(mem Memory) {
	auto alignMask = alignof(T)-1;
	auto addr = reinterpret_cast<ptrdiff>(Memory.address);
	auto alignedAddr =(addr + alignMask) & ~alignMask;
	return { reinterpret_cast<ptr>(alignedAddr), Memory.bytes-(alignedAddr-addr)};
}

template<class T>
size indexOf(mem Memory, T* Element) { return (ptrdiff(Memory.address) - ptrdiff(Element)) / sizeof(T); }

// TODO : Use a SIMD implementation
template<class T>
void swap(mem Memory, size IndexA, size IndexB) { 
	// T is known at compiletime and a unrolled xor loop should be faster
	u8* a = reinterpret_cast<u8*>(Memory.address) + IndexA * sizeof(T);
	u8* b = reinterpret_cast<u8*>(Memory.address) + IndexB * sizeof(T);
	for (auto i = 0; i < sizeof(T);++i) {
		a[i] = a[i] xor b[i];
		b[i] = a[i] xor b[i];
		a[i] = a[i] xor b[i];
	}
}
// TODO: Use a SIMD implementation
void copy(mem Source, mem Target){
	u8* a = reinterpret_cast<u8*>(Source.address);
	u8* b = reinterpret_cast<u8*>(Target.address);
	for (auto i = 0; i < Source.bytes; ++i) b[i] = a[i];
}
} // namespace rf

export constexpr rf::size operator ""_gb(rf::size GigaByte) {
	return GigaByte * 1000 * 1000 * 1000;
}

export constexpr rf::size operator ""_mb(rf::size MegaByte) {
	return MegaByte * 1000 * 1000;
}

export constexpr rf::size operator ""_kb(rf::size KiloByte) {
	return KiloByte * 1000;
}

export constexpr rf::size operator ""_gib(rf::size GibiByte) {
	return GibiByte * 1024 * 1024 * 1024;
}

export constexpr rf::size operator ""_mib(rf::size MibiByte) {
	return MibiByte * 1024 * 1024;
}

export constexpr rf::size operator ""_kib(rf::size KibiByte) {
	return KibiByte * 1024;
}