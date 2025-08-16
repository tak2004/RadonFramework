module;
#include <concepts>
#include <tuple>
#include <math.h>
export module rf.core.math.probabilistic:binaryfuse;
import rf.core.types;
import rf.core.cpu;

export namespace rf {
template<class T>
concept BinaryFuseFilterType = requires{
	std::_Is_any_of_v<u8, u16, u32>;
};

template<BinaryFuseFilterType T>
struct BinaryFuse {
	u64 seed;
	u32 segmentLength;
	u32 segmentLengthMask;
	u32 segmentCount;
	u32 segmentCountLength;
	mem fingerprints;

	void init(mem Arena) {
		u32 arity = 3;
		this->fingerprints = Arena;
		this->segmentLength = min(calculateSegmentLength(arity, this->fingerprints.bytes), 262144);
		this->segmentLengthMask = this->segmentLength - 1;
		auto sizeFactor = calculateSizeFactor(arity, this->fingerprints.bytes);
		u32 capacity = u32(math(sizeFactor).mul(this->fingerprints.bytes).round());
		auto initSegmentCount = (capacity + this->segmentLength - 1) / this->segmentLength - (arity - 1);
		auto arrayLength = (initSegmentCount + arity - 1) * this->segmentLength;
		this->segmentCount = (arrayLength + this->segmentLength - 1) / this->segmentLength;
		if (this->segmentCount <= arity - 1)
			this->segmentCount = 1;
		else
			this->segmentCount = this->segmentCount - (arity - 1);
		arrayLength = (this->segmentCount + arity - 1) * this->segmentLength;
		this->segmentCountLength = this->segmentCount * this->segmentLength;		
		u64 rng = 1;
		this->seed = splitmix64(rng);
	}
	bool contains(u64 Key) {
		auto hash = mixSplit(Key, this->seed);
		T fingerprint = fingerprint(hash);
		u32[h0, h1, h2] = this->getHashFromHash(hash);
		fingerprint ^= at(h0) ^ at(h1) ^ at(h2);
		return fingerprint == 0;
	}
	void populate(u64 Key) {

	}
private:
	u64 splitmix64(u64& Seed) {
		auto result = Seed += 0x9E3779B97F4A7C15;
		result = (result ^ (result >> 30)) * 0xBF58476D1CE4E5B9;
		result = (result ^ (result >> 27)) * 0x94D049BB133111EB;
		return result ^ (result >> 31);
	}
	std::tuple<u32, u32, u32> getHashFromHash(u64 Hash) {
		auto [hi, _] = math(Hash).mul(u64(this->segmentCountLength));
		u32 h0 = hi;
		u32 h1 = h0 + this->segmentLength;
		u32 h2 = h1 + this->segmentLength;
		h1 ^= u32(Hash >> 18) & this->segmentLengthMask;
		h2 ^= u32(Hash) & this->segmentLengthMask;
		return { h0, h1, h2 };
	}
	u32 calculateSegmentLength(u32 Arity, u32 Bytes) {
		if (Bytes == 0) return 4;
		if (Arity == 3)
			return 1ul << u32(floor(log(f64(Bytes))/log(3.33)+2.25));
		else if (Arity == 4)
			return 1ul << u32(floor(log(f64(Bytes))/log(2.91)-0.5));
		else
			return 65536;
	}
	f64 calculateSizeFactor(u32 Arity, u32 Bytes) {
		if (Arity == 3)
			return max(1.125, 0.875 + 0.25 * log(1000000.0) / log(f64(Bytes)));
		else if (Arity == 4)
			return max(1.075, 0.77 + 0.305 * log(600000.0) / log(f64(Bytes)));
		else
			return 2.0;
	}
};


}