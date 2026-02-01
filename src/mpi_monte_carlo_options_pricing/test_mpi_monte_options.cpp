
#include "./pre_controls.hpp"
#include "./mpi_monte_options.hpp"

#include <iostream>
#include <string>

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
  std::cout << "\tInitial price : " << std::to_string( initial_price ) << "\n";
  std::cout << "\tInitial log deviation : " << std::to_string( initial_log_deviation ) << "\n";
  std::cout << "\tMean : " << std::to_string( mean ) << "\n";
  std::cout << "\tPersistence : " << std::to_string( persistence ) << "\n";
  std::cout << "\tVolatility : " << std::to_string( volatility ) << std::endl;

}

int main( int argc, char** argv ) {



  return 0;
}

