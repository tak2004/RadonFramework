import rf.core.net;
import rf.core.memory;

using namespace rf;

AllocatorAdapter allocatorFrom(DoubleSidedArena& Arena) {
	return {
		.allocateImplementation = [](size Bytes, ptr Allocator)->mem {
			auto* allocator = reinterpret_cast<DoubleSidedArena*>(Allocator);
			return allocator->push(Bytes);
		},
		.deallocateImplementation = [](mem& Memory, ptr Allocator) {
			auto* allocator = reinterpret_cast<DoubleSidedArena*>(Allocator);
			allocator->pop(Memory);
		},
		.clearImplementation = [](ptr Allocator) { reinterpret_cast<DoubleSidedArena*>(Allocator)->clearFront(); },
		.recommendetGranularityImplementation = [](ptr Allocator)->size {return 4_kb;},
		.allocator = &Arena
	};	
}

StackAdapter stackFrom(DoubleSidedArena& Arena) {
	return {
		.pushImplementation = [](size Bytes, ptr Allocator)->mem {
			auto* allocator = reinterpret_cast<DoubleSidedArena*>(Allocator);
			return allocator->pushBack(Bytes);
		},
		.popImplementation = [](mem& Memory, ptr Allocator) {
			auto* allocator = reinterpret_cast<DoubleSidedArena*>(Allocator);
			allocator->popBack(Memory);
		},
		.clearImplementation = [](ptr Allocator) { reinterpret_cast<DoubleSidedArena*>(Allocator)->clearBack(); },
		.allocator = &Arena
	};
}

void main() {
	// configure the memory management
	Heap heap;
	auto netMemory = heap.allocate(50_mb);
	DoubleSidedArena networkArena;
	networkArena.memory = netMemory;	
	// init network API because some systems need it
	NetworkAPIContext context(allocatorFrom(networkArena), stackFrom(networkArena));
	context.start();
	// now you can use it
	context.updateInterfaces();
}