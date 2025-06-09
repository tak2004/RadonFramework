import rf.core;
#define DOCTEST_CONFIG_IMPLEMENT
#include <doctest/doctest.h>

int main(int argc, char **argv) {
    doctest::Context context;
    context.applyCommandLine(argc, argv);

    int res = context.run(); // run doctest

    // important - query flags (and --exit) rely on the user doing this
    if (context.shouldExit()) {
        // propagate the result of the tests
        return res;
    }

    printf("%s\n", "Hello, World!");
}

TEST_CASE("Test ID generation with the fast path.") {
    rf::Heap heap;
    rf::mem identContext = { 0 };
    auto now = rf::getSystemTime();
    auto contextSize = rf::initIdentContext(identContext, now);
    identContext = heap.allocate(contextSize);
    rf::initIdentContext(identContext, now);
    auto id = rf::genIdent(identContext);
}

TEST_CASE("Test ID generation with the slower time path.") {
    rf::Heap heap;
    rf::mem identContext = { 0 };
    auto now = rf::getSystemTime();
    auto contextSize = rf::initIdentContext(identContext, now, 1000);
    identContext = heap.allocate(contextSize);
    rf::initIdentContext(identContext, now, 1000);
    auto id = rf::genIdent(identContext);
    rf::sleep(2000);
    auto id2 = rf::genIdent(identContext);
    CHECK(id != id2);
}

TEST_CASE("Test ID generation with global fast time path.") {
    rf::Heap heap;
    rf::mem identContext = { 0 };
    auto now = rf::getSystemTime();
    auto contextSize = rf::initIdentContext(identContext, now);
    identContext = heap.allocate(contextSize);
    rf::initIdentContext(identContext, now);
    auto id = rf::genIdent(identContext);
    // new frame
    now = rf::getSystemTime();
    rf::updateIdentContext(identContext, now);
    auto id2 = rf::genIdent(identContext);
    CHECK(id != id2);
}

TEST_CASE("Test fixed size heap allocations") {
    rf::Heap heap;
    auto empty = heap.allocate(0);
    CHECK(empty.bytes == 0);
    auto validBlock = heap.allocate(1024);
    CHECK(validBlock.bytes >= 1024);
    auto terabyte = 1024Ui64 * 1024 * 1024 * 1024;    
    auto outOfMemory = heap.allocate(terabyte);
    CHECK(outOfMemory.bytes == 0);
}

TEST_CASE("Test dynamic heap allocations") {
    rf::Heap heap;
    auto terabyte = 1024Ui64 * 1024 * 1024 * 1024;
    auto megabyte = 1024 * 1024;

    auto reservation = heap.reserve(terabyte);
    CHECK(reservation.bytes >= terabyte);
    auto startMemory = heap.commit(reservation, 0, megabyte);
    auto midMemory = heap.commit(reservation, terabyte / 2, megabyte);
    auto endMemory = heap.commit(reservation, terabyte-megabyte, megabyte);
    
    auto commitableReservation = heap.reserve(megabyte);
    CHECK(commitableReservation.bytes >= megabyte);
    auto memory = heap.commit(commitableReservation, 0, megabyte);
    CHECK(memory.bytes >= megabyte);
}

int factorial(const int number) {
    return number < 1 ? 1 : number <= 1 ? number : factorial(number - 1) * number;
}

TEST_CASE("testing the factorial function") {
    CHECK(factorial(0) == 1);
    CHECK(factorial(1) == 1);
    CHECK(factorial(2) == 2);
    CHECK(factorial(3) == 6);
    CHECK(factorial(10) == 3628800);
}