#include <benchmark/benchmark.h>
#include <cstdlib>
#include <time.h>
#include <iostream>


static void BM_MultiThreaded(benchmark::State& state) 
{
    int size = 8 << 12;
    if (state.thread_index() == 0) 
    {
        // Setup code here for the main thread
    }
    char* src = new char[size];
    char* dst = new char[size];
    memset(src, 'x', size);
    for (auto _ : state)
        {
            memcpy(dst, src, size);
        }
    delete[] src;
    delete[] dst;
    if (state.thread_index() == 0) 
    {
        // Teardown code here for the main thread
    }
}
// BENCHMARK(BM_MultiThreaded)->Threads(2)->Threads(4);
// BENCHMARK(BM_MultiThreaded)->ThreadRange(1, 8); //Counting 1, 2, 4, 8, multiplicator 2
BENCHMARK(BM_MultiThreaded)->Threads(1);
BENCHMARK(BM_MultiThreaded)->Threads(1)->UseRealTime();
BENCHMARK(BM_MultiThreaded)->Threads(4);
BENCHMARK(BM_MultiThreaded)->Threads(4)->UseRealTime();
BENCHMARK(BM_MultiThreaded)->Threads(4)->MeasureProcessCPUTime();
BENCHMARK(BM_MultiThreaded)->Threads(4)->MeasureProcessCPUTime()->UseRealTime();


BENCHMARK_MAIN();