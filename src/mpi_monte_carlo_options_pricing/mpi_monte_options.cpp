
#include "./mpi_monte_options.hpp"
#include "./pre_controls.hpp"

#include <cnpy.h>
#include <omp.h>

#include <algorithm>
#include <chrono>
#include <cmath>
#include <filesystem>
#include <format>
#include <fstream>
#include <iostream>
#include <random>
#include <string>
#include <vector>

namespace MPI_MONTE_OPTIONS {

Heston_Parameters Construct_Parameters_Object( float initial_price,
                                               float initial_variance,
                                               float timestep,
                                               float drift,
                                               float mean_reversion_speed,
                                               float mean_reversion_level,
                                               float volatility,
                                               float correlation_factor ) {

  Heston_Parameters new_parameters = { initial_price, initial_variance,
                                       timestep, drift, 
                                       mean_reversion_speed, mean_reversion_level,
                                       volatility, 
                                       correlation_factor };

  return new_parameters;
}

void Simulate_Asset_Price_Walk( unsigned long long total_timesteps,
                                std::vector<float>* price_path_buffer,
                                std::mt19937_64* random_engine,
                                std::normal_distribution<float>* normal_distribution_gen,
                                Heston_Parameters parameters ) {

  float asset_price = parameters.initial_price;
  ( *price_path_buffer ) [ 0 ] = asset_price;

  float variance = parameters.initial_variance;
  float weiner_step_1;
  float weiner_step_2;

  for( unsigned long long timestep = 1; timestep < total_timesteps + 1; timestep++ ) {

    // Using the Heston stochastic volatility model

    // W_1 = sqrt( dt ) * Z
    weiner_step_1 = std::sqrt( parameters.timestep ) * ( *normal_distribution_gen )( *random_engine );

    // dS_t = drift * S_t * dt + sqrt( var ) * S_t * W_1
    asset_price += parameters.drift * asset_price * parameters.timestep 
                   + std::sqrt( variance ) * asset_price * weiner_step_1;

    ( *price_path_buffer )[ timestep ] = asset_price;

    // W_2 = p * W_1 + sqrt( 1 - p^2 ) * sqrt( dt ) * Z
    weiner_step_2 = parameters.correlation_factor * weiner_step_1
                    + std::sqrt( std::abs( 1 - std::pow( parameters.correlation_factor, 2 ) ) )
                    * std::sqrt( parameters.timestep ) 
                    * ( *normal_distribution_gen )( *random_engine );

    // dvar= k( Θ - var ) * dt + σ * sqrt( var ) * W_2
    variance += parameters.mean_reversion_speed 
                * ( parameters.mean_reversion_level - variance ) * parameters.timestep
                + parameters.volatility * std::sqrt( variance ) * weiner_step_2;

    variance = std::max( ( float ) 0.0, variance );

  }

}

std::vector<float> Run_Single_Threaded_Simulation( unsigned long long total_runs,
                                       unsigned long long total_timesteps,
                                       unsigned long long seed,
                                       bool do_write_to_file,
                                       Heston_Parameters parameters ) {

  // Deterministicly random componentry
  std::mt19937_64 random_engine;
  random_engine.seed( seed );

  std::normal_distribution<float> normal_distribution_gen( 0.0, 1.0 );

  std::vector<float> price_path_buffer( total_timesteps + 1 );
  std::vector<float> price_paths( total_runs * ( total_timesteps + 1 ) );

  std::filesystem::path output_file;

  if( do_write_to_file ) {
    // Defining output directory
    std::filesystem::path output_directory( MMCOP_OUTPUT_DIRECTORY_PREFIX );
    output_directory += "_";
    output_directory += std::format( "{:%Y%m%d_%H%M%S}", std::chrono::system_clock::now() );

    std::filesystem::create_directory( output_directory );

    output_file = output_directory;
    output_file /= MMCOP_OUTPUT_FILE_PREFIX;
    output_file += ".npy";
  }

  for( unsigned long long run = 0; run < total_runs; run++ ) {

    Simulate_Asset_Price_Walk( total_timesteps,
                               &price_path_buffer,
                               &random_engine,
                               &normal_distribution_gen,
                               parameters );


    std::copy( price_path_buffer.begin(), 
               price_path_buffer.end(), 
               &price_paths[ run * ( total_timesteps + 1 ) ] );

  }

  if( do_write_to_file ) {
    cnpy::npy_save( output_file, &price_paths[0], { total_runs, total_timesteps + 1 } );
  }

  return price_paths;
}


std::vector<float> Run_Multi_Threaded_Simulation( const unsigned long long total_runs,
                                            const unsigned long long total_timesteps,
                                            const unsigned long long seed,
                                            const bool do_write_to_file,
                                            const Heston_Parameters parameters ) {

  std::vector<float> price_paths( total_runs * ( total_timesteps + 1 ) );
  std::filesystem::path output_file;

  if( do_write_to_file ) {
    // Defining output directory
    std::filesystem::path output_directory( MMCOP_OUTPUT_DIRECTORY_PREFIX );
    output_directory += "_";
    output_directory += std::format( "{:%Y%m%d_%H%M%S}", std::chrono::system_clock::now() );

    std::filesystem::create_directory( output_directory );

    output_file = output_directory;
    output_file /= MMCOP_OUTPUT_FILE_PREFIX;

    output_file += ".npy";
  }

  // Shared values are effectively constant except price_paths
  #omp parallel default( none ) shared( price_paths, total_runs, total_timesteps, seed, do_write_to_file, parameters ) num_threads( MMCOP_NUMBER_OF_THREADS )
  {
    int thread_idx = omp_get_thread_num();

    // Deterministicly random componentry
    // Modifying seed deterministically per thread
    std::mt19937_64 random_engine;
    random_engine.seed( seed + thread_idx * MMCOP_THREAD_SEED_MAGIC_NUMBER );
    std::normal_distribution<float> normal_distribution_gen( 0.0, 1.0 );

    std::vector<float> price_path_buffer( total_timesteps + 1 );

    // Parallelised simulation 
    // TODO: Investigate memory sharing here
    #omp for default( none ) schedule( static ) 
    for( unsigned long long run = 0; run < total_runs; run++ ) {

      Simulate_Asset_Price_Walk( total_timesteps,
                                &price_path_buffer,
                                &random_engine,
                                &normal_distribution_gen,
                                parameters );

      // TODO: investigate requirement for atomic here 
      std::copy( price_path_buffer.begin(), 
                price_path_buffer.end(), 
                &price_paths[ run * ( total_timesteps + 1 ) ] );

    }

  }

  // Saving to file
  if( do_write_to_file ) {
    cnpy::npy_save( output_file, &price_paths[0], { total_runs, total_timesteps + 1 } );
  }

  return price_paths;
}


float Compute_Call_Price( std::vector<float>* price_paths,
                          unsigned long long total_runs,
                          unsigned long long total_timesteps,
                          float strike_price,
                          float discounting_rate ) {
  float call_price = 0;

  for( unsigned long long run = 0; run < total_runs; run++ ) {

    call_price += std::max( ( ( *price_paths )[ ( run + 1 ) * ( total_timesteps + 1 ) - 1 ] - strike_price ), ( float ) 0.0 );

  }

  call_price = ( std::pow( discounting_rate, total_timesteps ) * call_price ) / total_runs;

  return call_price;
}

}
