#include <benchmark/benchmark.h>
#include <iostream>


static void BM_LocalSetupTeardown(benchmark::State& state)
{
    // Setup part
    static int setupLocalCounter = 0;
    std::cout << "setupLocalCounter: "  << ++setupLocalCounter << std::endl;

    for (auto _ : state)
    {
        // Do some staff...
    }

    // Teardown part
    static int teardownLocalCounter = 0;
    std::cout << "teardownLocalCounter: "  << ++teardownLocalCounter << std::endl;
}
BENCHMARK(BM_LocalSetupTeardown);

static void Setup(const benchmark::State& state)
{
    // Some operation
    static int setupGlobalCounter = 0;
    std::cout << "setupGlobalCounter: "  << ++setupGlobalCounter << std::endl;
}

static void Teardown(const benchmark::State& state)
{
    // Some operation
    static int teardownGlobalCounter = 0;
    std::cout << "teardownGlobalCounter: "  << ++teardownGlobalCounter << std::endl;
}


static void BM_GlobalSetupTeardown(benchmark::State& state)
{
    for (auto _ : state)
    {
        // Do some staff...
    }
}
BENCHMARK(BM_GlobalSetupTeardown)->Setup(Setup)->Teardown(Teardown);

class SetupTeardownFixture 
: public benchmark::Fixture 
{
public:
    void SetUp(const ::benchmark::State& state) 
    {
        std::cout << "setupCounter: "  << ++setupCounter << std::endl;
    }

    void TearDown(const ::benchmark::State& state) 
    {
        std::cout << "teardownCounter: "  << ++teardownCounter << std::endl;
    }

private:
    int setupCounter = 0;
    int teardownCounter = 0;
};

// BENCHMARK_F(SetupTeardownFixture, FixtureSetupTeardown)(benchmark::State& state)
// {
//     for (auto _ : state)
//     {
//         // Do some staff...
//     }
// }

BENCHMARK_DEFINE_F(SetupTeardownFixture, BM_FixtureSetupTeardown)(benchmark::State& state)
{
    for (auto _ : state)
    {
        // Do some staff...
    }
}

BENCHMARK_REGISTER_F(SetupTeardownFixture, BM_FixtureSetupTeardown);


BENCHMARK_MAIN();