export module rf.core.types:simd;
export import :memory;

export namespace rf {
// SIMD works best if the data are fitting the operations.
// struct Transform{ f32 x,y,z,scale,dx,dy,dz; }; // row based
// std::vec<Transform> t; loadData(t);
// for (....){
//   t[i].x+=t[i].dx*deltaT;
//   t[i].y+=t[i].dy*deltaT;
//   t[i].z+=t[i].dz*deltaT;
// }
// struct TransformSIMD{ f32v x,dx,y,dy,z,dz,scale; }; // column based
// x,x,x,x,dx,dx,dx,dx
// mem data = loadData(); TransformSIMD t{{data, 4,16}, {slice(data,16),4,16},..};
// t.x += t.dx*deltaT;
// t.y += t.dy*deltaT;
// t.z += t.dz*deltaT;
	
// To avoid the ownership of data and still be flexible with the memory layout
// the Radon framework works with a view concept. Many APIs use SIMD types which
// represent one element but this isn't future proof because your code restrict
// to a specific SIMD implementation like 128Bit, 256Bit or 512Bit.
// The idea is to store your data in way you like and during the load process
// you transform them into the proposed format the hardware supports.
// if componentsUntilGap and gap are set zero then a hot path is used.
template <class T, class MT=mem> struct SIMDView {
	using Type = T;
  MT memory;  // The memory arena the operation will working on.
  // Specifies how many consecutive T's need to be processed until gap is applied.
  size componentsUntilGap;
  size gap; // Specifies the byte offset between groups.  
  T& operator[](size Index){
	  if (this->componentsUntilGap == 0 || this->gap == 0) {
		  return offset<T>(this->memory, Index);
	  }
	  else {
		  auto gaps = Index / this->componentsUntilGap;
		  auto sumGaps = gaps * this->gap;
		  auto totalOffset = sumGaps + sizeof(T) * Index;
		  return *reinterpret_cast<T*>(slice(this->memory, totalOffset).address);
	  }	  
  }
};

// The following types are used for optimize operation implementations.
using u8v = SIMDView<u8>;
using u8cv = SIMDView<u8,constmem>;
using u16v = SIMDView<u16>;
using u16cv = SIMDView<u16,constmem>;
using u32v = SIMDView<u32>;
using u32cv = SIMDView<u32,constmem>;
using u64v = SIMDView<u64>;
using u64cv = SIMDView<u64,constmem>;
using i8v = SIMDView<i8>;
using i8cv = SIMDView<i8,constmem>;
using i16v = SIMDView<i16>;
using i16cv = SIMDView<i16,constmem>;
using i32v = SIMDView<i32>;
using i32cv = SIMDView<i32,constmem>;
using i64v = SIMDView<i64>;
using i64cv = SIMDView<i64,constmem>;

using f32v = SIMDView<f32>;
using f32cv = SIMDView<f32,constmem>;
using f64v = SIMDView<f64>;
using f64cv = SIMDView<f64,constmem>;

template<class MT> struct SIMDView<bool,MT> {
	MT memory;
	bool operator[](size Index)const {
		auto byteOffset = Index / 8;
		return (*offset(this->memory, byteOffset)) & (1<<(Index%8));
	}
	void set(size Index, bool NewValue) {
		auto byteOffset = Index / 8;
		auto& byte = *offset(this->memory, byteOffset);
		if (NewValue)
			byte |= 1 << (Index % 8);
		else
			byte &= ~(1 << (Index % 8));
	}
};
using bits = SIMDView<bool>;
using constbits = SIMDView<bool,constmem>;

#pragma pack(push, 16)
struct alignas(16) f32v4 {
	f32 raw[4];
};
#pragma pack(pop)
static_assert(sizeof(f32v4) == 16);
static_assert(alignof(f32v4) == 16);

struct alignas(64) f32m4 {
	f32v4 raw[4];
};
static_assert(sizeof(f32m4) == 64);
static_assert(alignof(f32m4) == 64);

} // namespace rf