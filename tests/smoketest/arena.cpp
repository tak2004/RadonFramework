import rf.core;
#include <doctest/doctest.h>

TEST_CASE("Check the expected arena stack behaviour.") {
    rf::Arena root;
    CHECK(rf::threadArena != &root);
    root.begin();
    {
        CHECK(rf::threadArena == &root);
        rf::Arena nested;        
        nested.begin();
        {
            CHECK(rf::threadArena == &nested);
        }
        nested.end();
        CHECK(rf::threadArena == &root);
    }
}

TEST_CASE("Check overcommitment.") {
    rf::Arena root;
    auto overcomitted = root.push(8);
    CHECK(overcomitted.address == nullptr);
    CHECK(overcomitted.bytes == 8);
    root.pop(overcomitted);
    overcomitted = root.pushExtended(8,8);
    CHECK(overcomitted.address == nullptr);
    CHECK(overcomitted.bytes == 8);
    root.clear();
    CHECK(root.used == 0);
}