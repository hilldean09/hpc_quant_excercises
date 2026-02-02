
#include "./pre_controls.hpp"
#include "./mpi_monte_options.hpp"

#include <iostream>
#include <string>

using namespace MPI_MONTE_OPTIONS;

void Print_Parameters( unsigned long long total_runs,
                       unsigned long long total_timesteps,
                       unsigned long long seed,
                       bool do_write_to_file,
                       float initial_price, 
                       float initial_log_deviation, 
                       float mean, 
                       float persistence,
                       float volatility ) {

  std::cout << "\tTotal runs : " << std::to_string( total_runs ) << "\n";
  std::cout << "\tTotal timesteps : " << std::to_string( total_timesteps ) << "\n";
  std::cout << "\tSeed : " << std::to_string( seed ) << "\n";
  std::cout << "\tWrite to file? : " << std::to_string( do_write_to_file ) << "\n";
  std::cout << "\tInitial price : " << std::to_string( initial_price ) << "\n";
  std::cout << "\tInitial log deviation : " << std::to_string( initial_log_deviation ) << "\n";
  std::cout << "\tMean : " << std::to_string( mean ) << "\n";
  std::cout << "\tPersistence : " << std::to_string( persistence ) << "\n";
  std::cout << "\tVolatility : " << std::to_string( volatility ) << std::endl;

}

int main( int argc, char** argv ) {
  // Parameters
  unsigned long long total_runs = 5;
  unsigned long long total_timesteps = 10;
  unsigned long long seed = MMCOP_DEFAULT_SEED;
  bool do_write_to_file = true;
  float initial_price = MMCOP_DEFAULT_INITIAL_PRICE;
  float initial_log_deviation = MMCOP_DEFAULT_INITIAL_LOG_DEVIATION;
  float mean = MMCOP_DEFAULT_MEAN;
  float persistence = MMCOP_DEFAULT_PERSISTENCE;
  float volatility = MMCOP_DEFAULT_VOLATILITY;

  std::cout << "Running Single Threaded Test : " << std::endl;
  Print_Parameters( total_runs, total_timesteps, seed, do_write_to_file, initial_price, initial_log_deviation, mean, persistence, volatility );
  Run_Single_Threaded_Simulation( total_runs, total_timesteps, seed, do_write_to_file, initial_price, initial_log_deviation, mean, persistence, volatility );


  return 0;
}

