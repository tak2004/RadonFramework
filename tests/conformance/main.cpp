#define DOCTEST_CONFIG_IMPLEMENT
#include <doctest/doctest.h>
import rf.core;

TEST_CASE("ident faster then systemtime id") {
    rf::Heap heap;
    rf::mem identContext = { 0 };
    auto now = rf::getSystemTime();
    auto contextSize = rf::initIdentContext(identContext, now);
    identContext = heap.allocate(contextSize);
    rf::initIdentContext(identContext, now);
    rf::Ident id;
    rf::u32 tsc_aux;
    // ident
    auto start_tsc = rf::queryLogicalProcessorPerformanceCounter(tsc_aux);
    for (auto i = 0; i < 1000000; ++i) {
        id = rf::genIdent(identContext);
    }
    rf::u64 end_tsc = rf::queryLogicalProcessorPerformanceCounter(tsc_aux);
    auto identTime = end_tsc - start_tsc;
    float cycles_id = identTime / 1000000.f;
}

TEST_CASE("abs vs fast abs") {
    rf::f32 a = 0.0;
    rf::u32 tsc_aux;
    
    auto start_tsc = rf::queryLogicalProcessorPerformanceCounter(tsc_aux);
    for (auto i = 0; i < 1000000; ++i) {
        a = rf::math(a).abs();    
    }
    rf::u64 end_tsc = rf::queryLogicalProcessorPerformanceCounter(tsc_aux);
    auto precise = end_tsc - start_tsc;
    
    start_tsc = rf::queryLogicalProcessorPerformanceCounter(tsc_aux);
    for (auto i = 0; i < 1000000; ++i) {
        a = rf::fastmath(a).abs();    
    }
    end_tsc = rf::queryLogicalProcessorPerformanceCounter(tsc_aux);
    auto fast = end_tsc - start_tsc;
    printf("[abs]\ncmath =%llu\napprox=%llu\n", precise, fast);
}

TEST_CASE("atan vs approx atan") {
    rf::f32 a = 0.0;
    rf::u32 tsc_aux;
    
    auto start_tsc = rf::queryLogicalProcessorPerformanceCounter(tsc_aux);
    for (auto i = 0; i < 1000000; ++i) {
        a = rf::math(a).arcTan();    
    }
    rf::u64 end_tsc = rf::queryLogicalProcessorPerformanceCounter(tsc_aux);
    auto precise = end_tsc - start_tsc;
    
    start_tsc = rf::queryLogicalProcessorPerformanceCounter(tsc_aux);
    for (auto i = 0; i < 1000000; ++i) {
        a = rf::fastmath(a).arcTan();    
    }
    end_tsc = rf::queryLogicalProcessorPerformanceCounter(tsc_aux);
    auto fast = end_tsc - start_tsc;
    printf("[atan]\ncmath =%llu\napprox=%llu\n", precise, fast);
}

TEST_CASE("fma vs approx fma") {
    rf::f32 a = 0.0;
    rf::f32 b,c =1.0f;
    rf::u32 tsc_aux;
    
    auto start_tsc = rf::queryLogicalProcessorPerformanceCounter(tsc_aux);
    for (auto i = 0; i < 1000000; ++i) {
        a = rf::math(a).fma(rf::math(b),rf::math(c));    
    }
    rf::u64 end_tsc = rf::queryLogicalProcessorPerformanceCounter(tsc_aux);
    auto precise = end_tsc - start_tsc;
    
    start_tsc = rf::queryLogicalProcessorPerformanceCounter(tsc_aux);
    for (auto i = 0; i < 1000000; ++i) {
        a = rf::fastmath(a).fma(rf::fastmath(b),rf::fastmath(c));    
    }
    end_tsc = rf::queryLogicalProcessorPerformanceCounter(tsc_aux);
    auto fast = end_tsc - start_tsc;
    printf("[fma]\ncmath =%llu\napprox=%llu\n", precise, fast);
}

TEST_CASE("sin vs approx sin") {
    rf::f32 a = 1.5;
    rf::u32 tsc_aux;
    
    auto start_tsc = rf::queryLogicalProcessorPerformanceCounter(tsc_aux);
    for (auto i = 0; i < 1000000; ++i) {
        a = rf::math(a).sin();    
    }
    rf::u64 end_tsc = rf::queryLogicalProcessorPerformanceCounter(tsc_aux);
    auto precise = end_tsc - start_tsc;
    
    start_tsc = rf::queryLogicalProcessorPerformanceCounter(tsc_aux);
    for (auto i = 0; i < 1000000; ++i) {
        a = rf::fastmath(a).sin();
    }
    end_tsc = rf::queryLogicalProcessorPerformanceCounter(tsc_aux);
    auto fast = end_tsc - start_tsc;
    printf("[sin]\ncmath =%llu\napprox=%llu\n", precise, fast);
}

TEST_CASE("cos vs approx cos") {
    rf::f32 a = 0.0;
    rf::u32 tsc_aux;
    
    auto start_tsc = rf::queryLogicalProcessorPerformanceCounter(tsc_aux);
    for (auto i = 0; i < 1000000; ++i) {
        a = rf::math(a).cos();    
    }
    rf::u64 end_tsc = rf::queryLogicalProcessorPerformanceCounter(tsc_aux);
    auto precise = end_tsc - start_tsc;
    
    start_tsc = rf::queryLogicalProcessorPerformanceCounter(tsc_aux);
    for (auto i = 0; i < 1000000; ++i) {
        a = rf::fastmath(a).cos();
    }
    end_tsc = rf::queryLogicalProcessorPerformanceCounter(tsc_aux);
    auto fast = end_tsc - start_tsc;
    printf("[cos]\ncmath =%llu\napprox=%llu\n", precise, fast);
}

TEST_CASE("arcCos vs approx arcCos") {
    rf::f32 a = 1.5;
    rf::u32 tsc_aux;
    
    auto start_tsc = rf::queryLogicalProcessorPerformanceCounter(tsc_aux);
    for (auto i = 0; i < 1000000; ++i) {
        a = rf::math(a).arcCos();    
    }
    rf::u64 end_tsc = rf::queryLogicalProcessorPerformanceCounter(tsc_aux);
    auto precise = end_tsc - start_tsc;
    
    start_tsc = rf::queryLogicalProcessorPerformanceCounter(tsc_aux);
    for (auto i = 0; i < 1000000; ++i) {
        a = rf::fastmath(a).arcCos();
    }
    end_tsc = rf::queryLogicalProcessorPerformanceCounter(tsc_aux);
    auto fast = end_tsc - start_tsc;
    printf("[arcCos]\ncmath =%llu\napprox=%llu\n", precise, fast);
}

TEST_CASE("arcSin vs approx arcSin") {
    rf::f32 a = 1.5;
    rf::u32 tsc_aux;
    
    auto start_tsc = rf::queryLogicalProcessorPerformanceCounter(tsc_aux);
    for (auto i = 0; i < 1000000; ++i) {
        a = rf::math(a).arcSin();    
    }
    rf::u64 end_tsc = rf::queryLogicalProcessorPerformanceCounter(tsc_aux);
    auto precise = end_tsc - start_tsc;
    
    start_tsc = rf::queryLogicalProcessorPerformanceCounter(tsc_aux);
    for (auto i = 0; i < 1000000; ++i) {
        a = rf::fastmath(a).arcSin();
    }
    end_tsc = rf::queryLogicalProcessorPerformanceCounter(tsc_aux);
    auto fast = end_tsc - start_tsc;
    printf("[arcSin]\ncmath =%llu\napprox=%llu\n", precise, fast);
}

int main(int argc, char **argv) {
    doctest::Context context;
    context.applyCommandLine(argc, argv);
    int res = context.run(); // run doctest

    // important - query flags (and --exit) rely on the user doing this
    if (context.shouldExit()) {
        // propagate the result of the tests
        return res;
    }
}