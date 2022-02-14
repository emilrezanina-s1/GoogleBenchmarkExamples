#include <benchmark/benchmark.h>
#include <vector>

static void BM_CreateVector(benchmark::State& state)
{
    for (auto _ : state)
    {
        std::vector<int> v;
        (void)v;
    }
}
BENCHMARK(BM_CreateVector);

static void BM_CreateVectorWithReserve(benchmark::State& state)
{
    for (auto _ : state)
    {
        std::vector<int> v;
        v.reserve(1);
        (void)v;
    }
}
BENCHMARK(BM_CreateVectorWithReserve)->Arg(1000);

static void BM_CreateVectorPushBack(benchmark::State& state)
{
    auto count = state.range(0);
    for (auto _ : state)
    {
        std::vector<int> v;
        for (size_t i = 0; i < count; i++)
            v.push_back(i);
    }
}
BENCHMARK(BM_CreateVectorPushBack)->Arg(1000);

static void BM_CreateVectorWithReservePushBack(benchmark::State& state)
{
    auto count = state.range(0);
    for (auto _ : state)
    {
        std::vector<int> v;
        v.reserve(count);
        for (size_t i = 0; i < count; i++)
            v.push_back(i);

    }
}
BENCHMARK(BM_CreateVectorWithReservePushBack)->Arg(1000);
