import rf.ui;
import rf.core.collections;
import rf.core.cpu;
import rf.core.memory;
import rf.core.math.hashes;

using namespace rf;

AllocatorAdapter allocatorFrom(Allocator& Implementation) {
	return {
		.commitImplementation = [](mem Pool, size Offset, size Bytes, ptr Implementation)->mem {
			auto* allocator = reinterpret_cast<Allocator*>(Implementation);
			return allocator->commit(Pool, Offset, Bytes);
		},
		.releaseImplementation = [](mem Pool, mem& Memory, ptr Implementation) {
			auto* allocator = reinterpret_cast<Allocator*>(Implementation);
			allocator->deallocate(Memory);
		},
		.clearImplementation = [](ptr Implementation) { reinterpret_cast<Allocator*>(Implementation)->clear(); },
		.recommendetGranularityImplementation = [](ptr Allocator)->size {return 4_kib;},
		.reserveImplementation = [](size Bytes, ptr Implementation)->mem {
			auto* allocator = reinterpret_cast<Allocator*>(Implementation);
			return allocator->reserve(Bytes);
		},
		.allocator = &Implementation
	};
}

StackAdapter stackFrom(Arena& Implementation) {
	return {
		.pushImplementation = [](size Bytes, ptr Allocator)->mem {
			auto* allocator = reinterpret_cast<Arena*>(Allocator);
			return allocator->push(Bytes);
		},
		.popImplementation = [](mem& Memory, ptr Allocator) {
			auto* allocator = reinterpret_cast<Arena*>(Allocator);
			allocator->pop(Memory);
		},
		.clearImplementation = [](ptr Allocator) { reinterpret_cast<Arena*>(Allocator)->clear(); },
		.allocator = &Implementation
	};
}

int main() {
	CPUFeatures.detect();
	auto c_str = "/etc/dnsd";
	constmem memory = { "/etc/dnsd", sizeof("/etc/dnsd") };
	HashContextxxh3* context = createContext64();
	updateContext64(context, memory);
	auto h32 = hash32(context);
	auto h64 = hash64(context);
	freeContext(context);
	auto h32b = hash32xxh3(memory);
	auto h64b = hash64xxh3(memory);
	auto h32c = "/etc/dnsd"_32_xxh3;
	auto h32d = "/etc/dnsd"_h32;
	auto h64d = "/etc/dnsd"_h64;
	// configure the memory management
	Heap heap;
	auto stackMemory = heap.allocate(50_mb);
	Arena stack;
	stack.memory = stackMemory;
	auto stackAdapter = stackFrom(stack);
	auto allocatorAdapter = allocatorFrom(heap);
	Hashlist<> hashes(heap, stackAdapter, 1_gib);
	hashes.set(1, stack.memory.address);
	hashes.set(2, stack.memory.address);
	hashes.set(1, stack.memory.address);
	auto isKeySet = hashes.containsKey(1);
	hashes.remove(1);
	auto isKeySetAfterRemove = hashes.containsKey(1);
	auto two = hashes.get(2);
	Hashlist<> otherHashes(heap, stackAdapter);
	hashes.clone(otherHashes);
	auto otherTwo = hashes.get(2);
	return two == otherTwo ? 0 : -1;
}