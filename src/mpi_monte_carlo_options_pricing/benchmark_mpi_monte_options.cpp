


#include "./pre_controls.hpp"
#include "./mpi_monte_options.hpp"

#include <benchmark/benchmark.h>

#include <iostream>
#include <string>


using namespace MPI_MONTE_OPTIONS;


#define MMCOP_BM_TOTAL_RUNS 100000
#define MMCOP_BM_TOTAL_TIMESTEPS 504


static void BM_Run_Single_Threaded_Simulation( benchmark::State& state ) {
  // Parameters
  unsigned long long total_timesteps = MMCOP_BM_TOTAL_TIMESTEPS;
  unsigned long long seed = MMCOP_DEFAULT_SEED;
  bool do_write_to_file = false;
  Heston_Parameters parameters = Construct_Parameters_Object( MMCOP_DEFAULT_INITIAL_PRICE, MMCOP_DEFAULT_INITIAL_VARIANCE, MMCOP_DEFAULT_TIMESTEP, MMCOP_DEFAULT_DRIFT, MMCOP_DEFAULT_MEAN_REVERSION_SPEED, MMCOP_DEFAULT_MEAN_REVERSION_LEVEL, MMCOP_DEFAULT_VOLATILITY, MMCOP_DEFAULT_CORRELATION_FACTOR ); 

  for( auto _ : state ) {
    Run_Single_Threaded_Simulation( state.range( 0 ), total_timesteps, seed, do_write_to_file, parameters );
  }
}

BENCHMARK( BM_Run_Single_Threaded_Simulation )->RangeMultiplier( 2 )->Range( 64, 1'000'000 );


static void BM_Run_Multi_Threaded_Simulation( benchmark::State& state ) {
  // Parameters
  unsigned long long total_timesteps = MMCOP_BM_TOTAL_TIMESTEPS;
  unsigned long long seed = MMCOP_DEFAULT_SEED;
  bool do_write_to_file = false;
  Heston_Parameters parameters = Construct_Parameters_Object( MMCOP_DEFAULT_INITIAL_PRICE, MMCOP_DEFAULT_INITIAL_VARIANCE, MMCOP_DEFAULT_TIMESTEP, MMCOP_DEFAULT_DRIFT, MMCOP_DEFAULT_MEAN_REVERSION_SPEED, MMCOP_DEFAULT_MEAN_REVERSION_LEVEL, MMCOP_DEFAULT_VOLATILITY, MMCOP_DEFAULT_CORRELATION_FACTOR ); 

  for( auto _ : state ) {
    Run_Multi_Threaded_Simulation( state.range( 0 ), total_timesteps, seed, do_write_to_file, parameters );
  }
}

BENCHMARK( BM_Run_Multi_Threaded_Simulation )->RangeMultiplier( 2 )->Range( 64, 1'000'000 );

BENCHMARK_MAIN();

