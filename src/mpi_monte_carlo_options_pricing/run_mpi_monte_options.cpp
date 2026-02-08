

#include "./pre_controls.hpp"
#include "./mpi_monte_options.hpp"

#include <iostream>
#include <string>

using namespace MPI_MONTE_OPTIONS;

void Print_Parameters( unsigned long long total_runs,
                       unsigned long long total_timesteps,
                       int total_ranks,
                       unsigned long long seed,
                       bool do_write_to_file,
                       Heston_Parameters parameters,
                       float strike_price,
                       float discounting_rate ) {

  std::cout << "\tTotal runs : " << std::to_string( total_runs ) << "\n";
  std::cout << "\tTotal timesteps : " << std::to_string( total_timesteps ) << "\n";
  std::cout << "\tTotal Ranks : " << std::to_string( total_ranks ) << "\n";
  std::cout << "\tTimestep : " << std::to_string( parameters.timestep ) << "\n";
  std::cout << "\tSeed : " << std::to_string( seed ) << "\n";
  std::cout << "\tWrite to file? : " << std::to_string( do_write_to_file ) << "\n";

  std::cout << "\tInitial price : " << std::to_string( parameters.initial_price ) << "\n";

  std::cout << "\tInitial variance : " << std::to_string( parameters.initial_variance ) << "\n";
  std::cout << "\tDrift factor : " << std::to_string( parameters.drift ) << "\n";
  std::cout << "\tMean reversion speed : " << std::to_string( parameters.mean_reversion_speed ) << "\n";
  std::cout << "\tMean reversion level : " << std::to_string( parameters.mean_reversion_level ) << "\n";
  std::cout << "\tVolatility : " << std::to_string( parameters.volatility ) << "\n";
  std::cout << "\tCorrelation factor : " << std::to_string( parameters.correlation_factor ) << "\n";

  std::cout << "\tStrike price : " << std::to_string( strike_price ) << "\n";
  std::cout << "\tDiscounting rate : " << std::to_string( discounting_rate ) << std::endl;
}


void User_Parameter_Initialisation( unsigned long long* total_runs, unsigned long long* total_timesteps, int* seed, 
                                    bool* do_write_to_file, Heston_Parameters* parameters, 
                                    float* strike_price, float* discounting_rate ) {



}



int main( int argc, char* argv[] ) {
  // Parameter Declaration
  unsigned long long total_runs;
  unsigned long long total_timesteps;
  unsigned long long seed;
  bool do_write_to_file;
  Heston_Parameters parameters;
  float strike_price;
  float discounting_rate;

  float call_price;

  bool skip_manual_initialisation = false;

  // Simple CLI parser
  for( int arg_idx = 1; argv_idx < argc; argv_idx++ ) {
    if( std::string( argv[ arg_idx ] ) == "-d" || std::string( argv[ arg_idx ] ) == "--default" ) {
      skip_manual_initialisation = true;
    }
  }

  if( !skip_manual_initialisation ) {

    User_Parameter_Initialisation( &total_runs, &total_timesteps, &seed, 
                                   &do_write_to_file, &parameters, &strike_price, &discounting_rate );

  }



  return 0;
}


