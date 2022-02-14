#include <benchmark/benchmark.h>
#include <cstdlib>
#include <time.h>
#include <iostream>

static std::set<int> ConstructRandomSet(int size)
{
    srand(time(NULL));
    auto data = std::set<int>();
    for (size_t i = 0; i < size; i++)
        data.insert(rand() % 1000);
    return data;
}


static void BM_SetInsertWithoutTimerControl(benchmark::State& state) 
{
  std::set<int> data;
  for (auto _ : state) 
  {
    data = ConstructRandomSet(state.range(0));
    for (int j = 0; j < state.range(1); ++j)
      data.insert(rand() % 1000);
  }
}
BENCHMARK(BM_SetInsertWithoutTimerControl)->Ranges({{1 << 4, 1 << 10}, {128, 512}});

static void BM_SetInsertWithTimerControl(benchmark::State& state) 
{
  std::set<int> data;

  for (auto _ : state) 
  {
    state.PauseTiming();
    data = ConstructRandomSet(state.range(0));
    state.ResumeTiming();
    for (int j = 0; j < state.range(1); ++j)
      data.insert(rand() % 1000);
  }
}
BENCHMARK(BM_SetInsertWithTimerControl)->Ranges({{1 << 4, 1 << 10}, {128, 512}});


static void BM_EnableOptimization(benchmark::State& state) 
{
  for (auto _ : state) 
  {
      int x = 0;
      for (int i=0; i < 64; ++i) 
      {
          x += i;
      }
  }
}
BENCHMARK(BM_EnableOptimization)->Repetitions(5);

static void BM_DisableOptimization(benchmark::State& state) 
{
  for (auto _ : state) 
  {
      int x = 0;
      for (int i=0; i < 64; ++i) 
      {
        benchmark::DoNotOptimize(x += i);
      }
  }
}
BENCHMARK(BM_DisableOptimization)->Repetitions(5);

static void BM_EnableOptimizationWriteNotToGlobalMemory(benchmark::State& state) 
{
  for (auto _ : state) 
  {
    std::vector<int> v;
    v.reserve(1);
    v.data();
    v.push_back(42);
  }
}
BENCHMARK(BM_EnableOptimizationWriteNotToGlobalMemory)->Repetitions(5);

static void BM_DisableOptimizationWriteToGlobalMemory(benchmark::State& state) 
{
  for (auto _ : state) 
  {
    std::vector<int> v;
    v.reserve(1);
    benchmark::DoNotOptimize(v.data()); // Allow v.data() to be clobbered.
    v.push_back(42);
    benchmark::ClobberMemory(); // Force 42 to be written to memory.
  }
}
BENCHMARK(BM_DisableOptimizationWriteToGlobalMemory)->Repetitions(5);

BENCHMARK_MAIN();