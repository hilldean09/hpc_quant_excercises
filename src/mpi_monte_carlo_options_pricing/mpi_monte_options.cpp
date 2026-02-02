
#include "./pre_controls.hpp"

#include <cnpy.h>

#include <algorithm>
#include <chrono>
#include <cmath>
#include <filesystem>
#include <format>
#include <fstream>
#include <random>
#include <string>
#include <vector>

namespace MPI_MONTE_OPTIONS {

void Simulate_Asset_Price_Walk( unsigned long long total_timesteps,
                                  std::vector<float>* price_path_buffer,
                                  std::default_random_engine* random_engine,
                                  std::normal_distribution<float>* normal_distribution_gen,
                                  float initial_price,
                                  float initial_log_deviation,
                                  float mean,
                                  float persistence,
                                  float volatility ) {

  ( *price_path_buffer )[ 0 ] = std::log( initial_price );
  
  float log_deviation = initial_log_deviation;

  for( unsigned long long timestep = 0; timestep < total_timesteps; timestep++ ) {

    // Log return equation
    // s(t+1) = s(t) + mean + exp( h(t) ) * normal_distribution()
    ( *price_path_buffer )[ timestep + 1 ] = ( *price_path_buffer )[ timestep ]

                                            + mean + ( std::exp( log_deviation )
                                            * ( *normal_distribution_gen )( *random_engine ) );

    // Mean-reverting log-volatility equation
    // h(t+1) = persistence * h(t) + volatility * normal_distribution()
    log_deviation = persistence * log_deviation + volatility * ( *normal_distribution_gen )( *random_engine );

  }
  
  for( unsigned long long timestep = 1; timestep <= total_timesteps; timestep++ ) {
    ( *price_path_buffer )[ timestep ] = std::exp( ( *price_path_buffer )[ timestep ] );
  }

}

std::vector<float> Run_Single_Threaded_Simulation( unsigned long long total_runs,
                                       unsigned long long total_timesteps,
                                       unsigned long long seed,
                                       bool do_write_to_file,
                                       float initial_price, 
                                       float initial_log_deviation,
                                       float mean,
                                       float persistence,
                                       float volatility ) {

  // Deterministicly random componentry
  std::default_random_engine random_engine;
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

    Simulate_Asset_Price_Walk( total_timesteps, &price_path_buffer,
                               &random_engine, &normal_distribution_gen,
                               initial_price, initial_log_deviation, mean,
                               persistence, volatility );

    std::copy( price_path_buffer.begin(), 
               price_path_buffer.end(), 
               &price_paths[ run * ( total_timesteps + 1 ) ] );

  }

  if( do_write_to_file ) {
    cnpy::npy_save( output_file, &price_paths[0], { total_timesteps + 1, total_runs } );
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

  call_price = std::pow( discounting_rate, total_timesteps ) / total_runs;

  return call_price;
}

}
