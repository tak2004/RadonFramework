export module rf.core.math.hashes;
// Look into the devdoc/hashes.md for details.
export import :rapidhash;
export import :xxh3;
import rf.core.types;
export namespace rf {
    u32 operator ""_h32(const char* CLiteral, const size Bytes) {
        return operator""_32_xxh3(CLiteral, Bytes);
    }
    u64 operator ""_h64(const char* CLiteral, const size Bytes) {
        return operator""_64_rapid(CLiteral, Bytes);
    }
}