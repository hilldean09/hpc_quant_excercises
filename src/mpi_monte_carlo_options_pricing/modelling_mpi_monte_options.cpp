
#include "./io_mpi_monte_options.hpp"
#include "./mpi_monte_options.hpp"
#include "./modelling_mpi_monte_options.hpp"
#include "./pre_controls.hpp"

#include <cnpy.h>
#include <mpi.h>
#include <omp.h>

#include <string>
#include <random>
#include <iostream>

namespace MPI_MONTE_OPTIONS {


// Reducing heap memory allocation
float Run_Multi_Threaded_Simulation_V1( unsigned long long total_runs,
                                       unsigned long long total_timesteps,
                                       unsigned long long seed,
                                       bool do_write_to_file,
                                       Heston_Parameters parameters,
                                       float strike_price,
                                       float discounting_rate ) {

  float output_call_price = 0.0;
  float working_call_price = 0.0;

  if( do_write_to_file ) {
    std::cout << "ERROR : Write to file not supported in this implementation" << std::endl;
  }

  #pragma omp parallel default( none ) private( working_call_price ) shared( output_call_price, total_runs, total_timesteps, seed, do_write_to_file, parameters, strike_price, discounting_rate ) num_threads( MMCOP_NUMBER_OF_THREADS )
  {
    int thread_idx = omp_get_thread_num();

    // Deterministicly random componentry
    // Modifying seed deterministically per thread
    std::mt19937_64 random_engine;
    random_engine.seed( seed + thread_idx * MMCOP_THREAD_SEED_MAGIC_NUMBER );
    std::normal_distribution<float> normal_distribution_gen( 0.0, 1.0 );

    // Parallelised simulation 
    #pragma omp for schedule( static ) 
    for( unsigned long long run = 0; run < total_runs; run++ ) {

      working_call_price = std::max( Simulate_Asset_Price_Walk_V1( total_timesteps, &random_engine, &normal_distribution_gen, parameters )
                                      - strike_price, ( float ) 0.0 );

      // Summing call price
      #pragma omp atomic update
      output_call_price += working_call_price;

    }

  }

  output_call_price = ( std::pow( discounting_rate, total_timesteps * parameters.timestep ) * output_call_price ) / total_runs;

  return output_call_price;
}

float Simulate_Asset_Price_Walk_V1( unsigned long long total_timesteps,
                                    std::mt19937_64* random_engine,
                                    std::normal_distribution<float>* normal_distribution_gen,
                                    Heston_Parameters parameters ) {

  float asset_price = parameters.initial_price;

  float variance = parameters.initial_variance;
  float weiner_step_1;
  float weiner_step_2;

  for( unsigned long long timestep = 0; timestep < total_timesteps; timestep++ ) {

    // Using the Heston stochastic volatility model

    // W_1 = sqrt( dt ) * Z
    weiner_step_1 = std::sqrt( parameters.timestep ) * ( *normal_distribution_gen )( *random_engine );

    // dS_t = drift * S_t * dt + sqrt( var ) * S_t * W_1
    asset_price += parameters.drift * asset_price * parameters.timestep 
                   + std::sqrt( variance ) * asset_price * weiner_step_1;

    // W_2 = p * W_1 + sqrt( 1 - p^2 ) * sqrt( dt ) * Z
    weiner_step_2 = parameters.correlation_factor * weiner_step_1
                    + std::sqrt( std::abs( 1 - std::pow( parameters.correlation_factor, 2 ) ) )
                    * std::sqrt( parameters.timestep ) 
                    * ( *normal_distribution_gen )( *random_engine );

    // dvar = k( Θ - var ) * dt + σ * sqrt( var ) * W_2
    variance += parameters.mean_reversion_speed 
                * ( parameters.mean_reversion_level - variance ) * parameters.timestep
                + parameters.volatility * std::sqrt( variance ) * weiner_step_2;

    // Alternative to abs is max
    variance = std::abs( variance );

  }

  return asset_price;

}



} // Global namespace end



