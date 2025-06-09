export module rf.core.memory:arena;
import rf.core.types;

export namespace rf {
struct AllocatorSchema {
  size alignment=8;// allocation pointer alignment
};

struct Arena {
  mem push(size Bytes);
  mem pushExtended(size Bytes, size Alignment);
  void pop(mem &Block);
  void clear();

  mem memory = {};
  size offset = 0;
  AllocatorSchema schema;
};

struct DoubleSidedArena :Arena {
    size backOffset=0;

    mem pushBack(size Bytes);
    mem pushExtendedBack(size Bytes, size Alignment);
    void popBack(mem& Block);
    void clear();
    void clearFront();
    void clearBack();
};

mem Arena::push(const size Bytes) {
  mem result;
  result.address = (ptr)((ptrdiff)this->memory.address + this->offset);
  result.bytes = Bytes;
  this->offset += Bytes;
  return result;
}

mem Arena::pushExtended(const size Bytes, const size Alignment) {
  mem result;
  result.address =
      (ptr)(((ptrdiff)this->memory.address + this->offset + Alignment - 1) &
            ~(Alignment - 1));
  result.bytes = Bytes;
  this->offset += Bytes;
  return result;
}

void Arena::pop(mem &Block) { 
    this->offset -= Block.bytes; 
    Block.address = nullptr;
    Block.bytes = 0;
}


void Arena::clear() { this->offset = 0; }

mem DoubleSidedArena::pushBack(const size Bytes) {
    this->backOffset += Bytes;
    mem result;
    result.address = (ptr)((ptrdiff)this->memory.address + (this->memory.bytes - this->backOffset));
    result.bytes = Bytes;
    return result;
}

mem DoubleSidedArena::pushExtendedBack(const size Bytes, const size Alignment) {
    this->backOffset += Bytes;
    mem result;
    result.address =
        (ptr)(((ptrdiff)this->memory.address + (this->memory.bytes - this->backOffset) + Alignment - 1) &
            ~(Alignment - 1));
    result.bytes = Bytes;
    return result;
}

void DoubleSidedArena::popBack(mem& Block) { 
    this->backOffset -= Block.bytes; 
    Block.address = nullptr;
    Block.bytes = 0;
}

void DoubleSidedArena::clear() {
    this->offset = 0;
    this->backOffset = 0;
}

void DoubleSidedArena::clearFront() {
    this->offset = 0;
}

void DoubleSidedArena::clearBack() {
    this->backOffset = 0;
}

} // namespace rf