#include <doctest/doctest.h>
import rf.core.types;

TEST_CASE("Check the expected byte size") {
    CHECK(sizeof(rf::i8) == 1);
    CHECK(sizeof(rf::u8) == 1);
    CHECK(sizeof(rf::utf8) == 1);
    CHECK(sizeof(rf::i16) == 2);
    CHECK(sizeof(rf::u16) == 2);
    CHECK(sizeof(rf::utf16) == 2);
    CHECK(sizeof(rf::wchar) == 2);
    CHECK(sizeof(rf::i32) == 4);
    CHECK(sizeof(rf::u32) == 4);
    CHECK(sizeof(rf::f32) == 4);
    CHECK(sizeof(rf::utf32) == 4);
    CHECK(sizeof(rf::i64) == 8);
    CHECK(sizeof(rf::u64) == 8);
    CHECK(sizeof(rf::f64) == 8);
    CHECK(sizeof(rf::size) == 8);
    CHECK(sizeof(rf::ptr) == 8);
    CHECK(sizeof(rf::ptrdiff) == 8);
}