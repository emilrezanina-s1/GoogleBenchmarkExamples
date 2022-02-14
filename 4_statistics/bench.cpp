#include <benchmark/benchmark.h>

static void BM_MemoryCopy(benchmark::State& state)
{
    int size = 8 << 12;
    char* src = new char[size];
    char* dst = new char[size];
    memset(src, 'x', size);
    for (auto _ : state)
        {
            memcpy(dst, src, size);
        }
    delete[] src;
    delete[] dst;
}
BENCHMARK(BM_MemoryCopy);
BENCHMARK(BM_MemoryCopy)->Repetitions(10);


BENCHMARK_MAIN();