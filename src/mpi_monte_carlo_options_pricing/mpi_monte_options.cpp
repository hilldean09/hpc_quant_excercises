
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
                                  float initial_price,
                                  float initial_log_deviation,
                                  float mean,
                                  float persistence,
                                  float volatility ) {

  price_path_buffer[ 0 ] = std::log( initial_price );
  
  float deviation = initial_log_deviation;

  for( unsigned long long timestep = 0; timestep < total_timesteps; timestep++ ) {

    // Log return equation
    // s(t+1) = s(t) + mean + exp( h(t) ) * normal_distribution()
    price_path_buffer[ timestep + 1 ] = price_path_buffer[ timestep ]
                                            + mean + ( std::exp( log_deviation )
                                            * std::normal_distribution( *random_engine ) );

    // Mean-reverting log-volatility equation
    // h(t+1) = persistence * h(t) + volatility * normal_distribution()
    log_deviation = persistence * log_deviation + volatility * std::normal_distribution( *random_engine );

  }
  
  for( unsigned long long timestep = 1; timestep <= total_timesteps; timestep++ ) {
    price_path_buffer[ timestep ] = std::exp( price_path_buffer );
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

  std::default_random_engine random_engine;
  random_engine.seed( seed );

  std::vector<float> price_path_buffer( total_timesteps + 1 );

  if( !do_write_to_file ) {
    std::vector<std::vector<float>> price_paths( total_runs, vector<float>( total_timesteps + 1 ) );
  }
  else {
    // Defining output directory
    std::filesystem::path output_directory( MMCOP_OUTPUT_DIRECTORY_PREFIX );
    output_directory += "_";
    output_directory += std::format( "{:%Y%m%d_%H%M%S}", std::chrono::system_clock::now() );

    std::filesystem::create_directory( output_path );

    std::filesystem::path output_file = output_directory;
    output_file /= MMCOP_OUTPUT_FILE_PREFIX;
    output_file += ".npy";

    std::ofstream output_stream;
    output_stream.open( output_file, std::ios::out | std::ios::binary );

    Write_Numpy_File_Header( output_stream );
  }

  for( unsigned long long run; run < total_runs; run++ ) {

    Simulate_Asset_Price_Walk( total_timesteps, price_path_buffer, random_engine,
                               initial_price, initial_log_deviation, mean,
                               persistence, volatility );

    if( !do_write_to_file ) {
      price_paths[ run ] = price_path_buffer;
    }
    else {
      Write_Path_To_Numpy_File( price_path_buffer, output_stream );
    }

  }

  if( !do_write_to_file ) {

  }
  else {
      output_stream.close();
  }

}


}
