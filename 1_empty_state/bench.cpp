#include <benchmark/benchmark.h>
#include <iostream>

static void BM_EmptyStateUseForLoop(benchmark::State& state)
{
    // Setup part
    for (auto _ : state)
    {
        // Do some staff...
    }
    // Teardown part
}
BENCHMARK(BM_EmptyStateUseForLoop);
BENCHMARK(BM_EmptyStateUseForLoop)->Iterations(500);
BENCHMARK(BM_EmptyStateUseForLoop)->Name("Empty State: 1000 iterations")->Iterations(1000);

static void BM_EmptyStateUseWhileKeepRunningLoop(benchmark::State& state)
{
    // Setup part
    while (state.KeepRunning())
    {
        // Do some staff...
    }
    // Teardown part
}
BENCHMARK(BM_EmptyStateUseWhileKeepRunningLoop);

BENCHMARK_MAIN(); 