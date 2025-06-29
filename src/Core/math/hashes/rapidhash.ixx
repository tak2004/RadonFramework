module;
#include <rapidhash.h>
export module rf.core.math.hashes:rapidhash;
import rf.core.types;

export namespace rf{
    // Best suited for up to 48byte large strings.
    u64 operator ""_64_rapid_nano(const char* CLiteral, const size Bytes) {
        return rapidhashNano(CLiteral, Bytes+1);
    }
    // Best suited for 48-512byte large strings.
    u64 operator ""_64_rapid_micro(const char* CLiteral, const size Bytes) {
        return rapidhashMicro(CLiteral, Bytes+1);
    }
    u64 operator ""_64_rapid(const char* CLiteral, const size Bytes) {
        if (Bytes <= 48)
            return rapidhashNano(CLiteral, Bytes+1);
        else
            return rapidhashMicro(CLiteral, Bytes+1);
    }
    u64 hash64rapid(constmem Memory) {
        return rapidhash(Memory.address, Memory.bytes);
    }
}