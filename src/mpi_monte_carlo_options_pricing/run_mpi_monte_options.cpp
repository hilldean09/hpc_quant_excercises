

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

// Adapted from https://stackoverflow.com/a/447307
template <class T_type_to_check>
bool Is_Of_Type( std::string string_to_check ) {

  // Effectively uses a string stream to attempt to construct a value 
  // of the given type and checking if fail or bad bits are set.

  std::istringstream input_string_stream( string_to_check );
  T_type_to_check testing_value;

  input_string_stream >> testing_value;

  return input_string_stream.eof() && !input_string_stream.fail();
}

template <class T_return_type>
T_return_type Get_Parameter_From_User( std::string parameter_name, std::string type_name, T_return_type default_value ) {

  T_return_type output;
  std::string input_string;
  bool continue_input_loop = true;

  std::cout << "\t[ " << parameter_name << " ] of type [ " << type_name << " ] with default of [ " << std::to_string( default_value ) << " ] : ";

  while( continue_input_loop ) {
    std::cin >> input_string;

    if( input_string == "default" ) {
      output = default_value;
    }

  }

}


void User_Parameter_Initialisation( unsigned long long* total_runs, unsigned long long* total_timesteps, int* seed, 
                                    bool* do_write_to_file, Heston_Parameters* parameters, 
                                    float* strike_price, float* discounting_rate ) {

  std::cout << "--- User Parameter Initialisation ---\n" << std::endl;

  std::string input_buffer;

  bool do_manual_initialisation = false;
  bool do_continue_initialisation_mode = true;

  while( do_continue_initialisation_mode ) {
    std::cout << "Do manual initialisation (defaults will be applied otherwise)? y / n : ";
    std::cin >> input_buffer;
    std::cout << std::endl;

    if( input_buffer == "y" || input_buffer == "Y" ) {
      do_manual_initialisation == true;
      do_continue_initialisation_mode == false;
    }
    else if( input_buffer == "n" || input_buffer == "N" ) {
      do_manual_initialisation == false;
      do_continue_initialisation_mode == false;
    }
    else {
      std::cout << "Answer not recognised, please try again" << std::endl;
    }

  }

  if( do_manual_initialisation ) {
    total_runs = Get_Parameter_From_User<unsigned long long>( "Total Runs" );
  }

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


