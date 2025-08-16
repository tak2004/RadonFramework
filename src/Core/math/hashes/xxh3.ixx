module;
#define XXH_INLINE_ALL
#include <xxh3.h>
export module rf.core.math.hashes:xxh3;
import rf.core.types;

export namespace rf {
    using HashContextxxh3 = XXH3_state_t;
    HashContextxxh3* createContext64() {
        XXH3_state_t* state = XXH3_createState();
        XXH3_64bits_reset(state);
        return state;
    }
    HashContextxxh3* createContext128() {
        XXH3_state_t* state = XXH3_createState();
        XXH3_128bits_reset(state);
        return state;
    }
    void resetContext64(HashContextxxh3* Context) {
        XXH3_64bits_reset(Context);
    }
    void resetContext128(HashContextxxh3* Context) {
        XXH3_128bits_reset(Context);
    }
    void freeContext(HashContextxxh3* Context) {
        XXH3_freeState(Context);
    }
    void updateContext64(HashContextxxh3* Context, constmem Memory) {
        XXH3_64bits_update(Context, Memory.address, Memory.bytes);
    }
    void updateContext128(HashContextxxh3* Context, constmem Memory) {
        XXH3_128bits_update(Context, Memory.address, Memory.bytes);
    }
    u32 hash32(HashContextxxh3* Context) {
        auto result = XXH3_64bits_digest(Context);
        return static_cast<u32>(result);
    }
    u64 hash64(HashContextxxh3* Context) {
        auto result = XXH3_64bits_digest(Context);
        return result;
    }
    void hash128(HashContextxxh3* Context, u64& High, u64& Low) {
        auto result = XXH3_128bits_digest(Context);
        High = result.high64;
        Low = result.low64;
    }
    u32 hash32xxh3(constmem Memory) {
        return static_cast<u32>(XXH3_64bits(Memory.address, Memory.bytes));
    }
    u64 hash64xxh3(constmem Memory) {
        return XXH3_64bits(Memory.address, Memory.bytes);
    }
    void hash128xxh3(constmem Memory, u64& High, u64& Low) {
        auto hash = XXH3_128bits(Memory.address, Memory.bytes);
        High = hash.high64;
        Low = hash.low64;
    }
    u32 operator ""_32_xxh3(const char* CLiteral, const size Bytes) {
        return static_cast<u32>(XXH3_64bits(CLiteral, Bytes+1));
    }
}
