#include <benchmark/benchmark.h>
#include <iostream>
#include <tuple>

static void BM_Args(benchmark::State& state)
{
    char* src = new char[state.range(0)];
    char* dst = new char[state.range(0)];
    memset(src, 'x', state.range(0));
    for (auto _ : state)
        {
            memcpy(dst, src, state.range(0));
        }
    delete[] src;
    delete[] dst;
}

BENCHMARK(BM_Args)->Arg(8)->Arg(64)->Arg(512)->Arg(1<<10);


static void BM_ArgsRange(benchmark::State& state)
{
    char* src = new char[state.range(0)];
    char* dst = new char[state.range(0)];
    memset(src, 'x', state.range(0));
    for (auto _ : state)
        {
            memcpy(dst, src, state.range(0));
        }
    delete[] src;
    delete[] dst;
}
BENCHMARK(BM_ArgsRange)->Range(8, 1 << 10);
//BENCHMARK(BM_ArgsRange)->RangeMultiplier(2)->Range(8, 1 << 10);
BENCHMARK(BM_ArgsRange)->DenseRange(0, 1024, 128);

static void BM_ArgsMultipleValues(benchmark::State& state)
{
    for (auto _ : state)
        {
            //std::cout << state.range(0) << ": " << state.range(1) << std::endl;
        }
}
BENCHMARK(BM_ArgsMultipleValues)
    ->Args({8, 8})
    ->Args({64, 64})
    ->Args({512, 512})
    ->Args({1<<10, 1<<10});
// BENCHMARK(BM_ArgsMultipleValues)->Ranges({{8, 1 << 10}, {8, 1 << 10}});
// BENCHMARK(BM_ArgsMultipleValues)
//     ->ArgsProduct({
//         benchmark::CreateRange(8, 128, /*multi=*/2),
//         benchmark::DenseRange(1, 4, /*step*/1)
//     });


static void GenerateArgsPair(benchmark::internal::Benchmark* b)
{
    for (int i = 1 << 4; i <= 1 << 10; i <<= 2)
        {
        // b = b->ArgPair(i, i);
        b->Args({i, i});
        }
}

static void BM_ArgsPairGenerate(benchmark::State& state)
{
    char* src = new char[state.range(0)];
    // char* src = new char[state.range_x()]; // Depricated
    char* dst = new char[state.range(1)];
    // char* dst = new char[state.range_y()]; // Depricated
    memset(src, 'x', state.range(0));
    for (auto _ : state)
        {
            memcpy(dst, src, state.range(0));
        }
    delete[] src;
    delete[] dst;
}
BENCHMARK(BM_ArgsPairGenerate)->Apply(GenerateArgsPair);

template <class ...Args>
void BM_TakesArgs(benchmark::State& state, Args&&... args) 
{
  auto args_tuple = std::make_tuple(std::move(args)...);
  (void)args_tuple;
  for (auto _ : state) 
  {
    // std::cout << std::get<0>(args_tuple) << ": " << std::get<1>(args_tuple) << '\n';
  }
}
BENCHMARK_CAPTURE(BM_TakesArgs, int_string_test, 42, std::string("abc"));
BENCHMARK_CAPTURE(BM_TakesArgs, int_test, 42, 43);

BENCHMARK_MAIN();