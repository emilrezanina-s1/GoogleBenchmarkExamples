#include <benchmark/benchmark.h>
#include <cstdlib>
#include <time.h>
#include <iostream>

static void BM_SimpleGenerateNumber(benchmark::State& state)
{
    srand(time(NULL));
    int foo = 0;
    while (state.KeepRunning())
    {
        foo = rand() % state.range(0);
    }
}
BENCHMARK(BM_SimpleGenerateNumber)->DenseRange(100, 1000, 100);

static void BM_SimpleGenerateNumberWithUserCounters(benchmark::State& state)
{
    srand(time(NULL));
    int foo = 0;
    while (state.KeepRunning())
    {
        foo = rand() % state.range(0);
    }
    state.counters["SimpleCounterFoo"] = foo;
    state.counters["HowManyFoosAreProcessed"] = benchmark::Counter(foo, benchmark::Counter::kIsRate);
    state.counters["HowManySecsItTakesToProcessOneFoo"] = benchmark::Counter(foo, benchmark::Counter::kIsRate | benchmark::Counter::kInvert);
    state.counters["ThreadAverageQuantity"] = benchmark::Counter(foo, benchmark::Counter::kAvgThreads);
    state.counters["HowManyFoosAreProcessed"] = benchmark::Counter(state.range(0), benchmark::Counter::kIsIterationInvariantRate, benchmark::Counter::OneK::kIs1024);
    // Check benchmark::Counter::k...    
}
BENCHMARK(BM_SimpleGenerateNumberWithUserCounters)->DenseRange(100, 1000, 100);

BENCHMARK_MAIN();