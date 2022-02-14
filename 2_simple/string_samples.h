#include <benchmark/benchmark.h>
#include <string>
// #include <iostream>

static void CompareString(size_t size)
{
    std::string s1(size, '-');
    std::string s2(size, '-');

    s1.compare(s2);
}

static void BM_CompareString(benchmark::State& state)
{
    for (auto _ : state)
    {
        CompareString(10000);
    }    
}
BENCHMARK(BM_CompareString);

static void BM_StringCreation(benchmark::State& state) 
{
  for (auto _ : state)
    std::string empty_string;
}
BENCHMARK(BM_StringCreation);

static void BM_StringCopy(benchmark::State& state) 
{
  std::string x = "hello";
  for (auto _ : state)
    std::string copy(x);
}
BENCHMARK(BM_StringCopy);