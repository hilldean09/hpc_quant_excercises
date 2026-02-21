
#include "./io_mpi_monte_options.hpp"

#include <iostream>
#include <string>

namespace MPI_MONTE_OPTIONS {
namespace IO {

bool Parse_Parameters_From_Arguments( int argc, char* argv[],
                                      unsigned long long* total_runs,
                                      unsigned long long* total_timesteps,
                                      unsigned long long* seed, 
                                      bool* do_write_to_file,
                                      Heston_Parameters* parameters,
                                      float* strike_price,
                                      float* discounting_rate ) {

  std::string arg;
  bool parameter_args_detected = false;

  // Default initialisation
  *do_write_to_file = false;
  *total_runs = MMCOP_DEFAULT_TOTAL_RUNS;
  *total_timesteps = MMCOP_DEFAULT_TOTAL_TIMESTEPS;
  parameters->timestep = MMCOP_DEFAULT_TIMESTEP;
  *seed = MMCOP_DEFAULT_SEED;
  parameters->initial_price = MMCOP_DEFAULT_INITIAL_PRICE;
  parameters->initial_variance = MMCOP_DEFAULT_INITIAL_VARIANCE;
  parameters->drift = MMCOP_DEFAULT_DRIFT;
  parameters->mean_reversion_speed = MMCOP_DEFAULT_MEAN_REVERSION_SPEED;
  parameters->mean_reversion_level = MMCOP_DEFAULT_MEAN_REVERSION_LEVEL;
  parameters->volatility = MMCOP_DEFAULT_VOLATILITY;
  parameters->correlation_factor = MMCOP_DEFAULT_CORRELATION_FACTOR;
  *strike_price = MMCOP_DEFAULT_STRIKE_PRICE;
  *discounting_rate = MMCOP_DEFAULT_DISCOUNTING_RATE;

  for( int argv_idx = 0; argv_idx < argc; argv_idx++ ) {
    arg = std::string( argv[ argv_idx ] );

    if( arg == "--write-to-file" ) {
      arg = std::string( argv[ argv_idx + 1 ] );
      argv_idx++;
      parameter_args_detected = true;

      if( arg == "true" || arg == "True" ) {
        *do_write_to_file = true;
      }
      else if( arg == "false" || arg == "False" ) {
        *do_write_to_file = false;
      }
      else {

      std::cout << "ERROR : Write to file value is invalid" << std::endl;

      }

    }
    else if( arg == "--total-runs" ) {

      arg = std::string( argv[ argv_idx + 1 ] );
      argv_idx++;
      parameter_args_detected = true;

      if( Is_Of_Type<unsigned long long>( arg ) ) {
        *total_runs = std::stoull( arg );
      }
      else {
        std::cout << "ERROR : Total runs value is invalid" << std::endl;
      }

    }
    else if( arg == "--total_timesteps" ) {

      arg = std::string( argv[ argv_idx + 1 ] );
      argv_idx++;
      parameter_args_detected = true;

      if( Is_Of_Type<unsigned long long>( arg ) ) {
        *total_timesteps = std::stoull( arg );
      }
      else {
        std::cout << "ERROR : Total timesteps value is invalid" << std::endl;
      }

    }
    else if( arg == "--seed" ) {

      arg = std::string( argv[ argv_idx + 1 ] );
      argv_idx++;
      parameter_args_detected = true;

      if( Is_Of_Type<unsigned long long>( arg ) ) {
        *seed = std::stoull( arg );
      }
      else {
        std::cout << "ERROR : Seed value is invalid" << std::endl;
      }

    }
    else if( arg == "--initial-price" ) {

      arg = std::string( argv[ argv_idx + 1 ] );
      argv_idx++;
      parameter_args_detected = true;

      if( Is_Of_Type<float>( arg ) ) {
        parameters->initial_price = std::stof( arg );
      }
      else {
        std::cout << "ERROR : Initial price value is invalid" << std::endl;
      }

    }
    else if( arg == "--initial-variance" ) {

      arg = std::string( argv[ argv_idx + 1 ] );
      argv_idx++;
      parameter_args_detected = true;

      if( Is_Of_Type<float>( arg ) ) {
        parameters->initial_variance = std::stof( arg );
      }
      else {
        std::cout << "ERROR : Initial variance value is invalid" << std::endl;
      }

    }
    else if( arg == "--timestep" ) {

      arg = std::string( argv[ argv_idx + 1 ] );
      argv_idx++;
      parameter_args_detected = true;

      if( Is_Of_Type<float>( arg ) ) {
        parameters->timestep = std::stof( arg );
      }
      else {
        std::cout << "ERROR : Timestep value is invalid" << std::endl;
      }

    }
    else if( arg == "--drift" ) {

      arg = std::string( argv[ argv_idx + 1 ] );
      argv_idx++;
      parameter_args_detected = true;

      if( Is_Of_Type<float>( arg ) ) {
        parameters->drift = std::stof( arg );
      }
      else {
        std::cout << "ERROR : Drift value is invalid" << std::endl;
      }

    }
    else if( arg == "--mean-reversion-speed" ) {

      arg = std::string( argv[ argv_idx + 1 ] );
      argv_idx++;
      parameter_args_detected = true;

      if( Is_Of_Type<float>( arg ) ) {
        parameters->mean_reversion_speed = std::stof( arg );
      }
      else {
        std::cout << "ERROR : Mean reversion speed value is invalid" << std::endl;
      }

    }
    else if( arg == "--mean-reversion-level" ) {

      arg = std::string( argv[ argv_idx + 1 ] );
      argv_idx++;
      parameter_args_detected = true;

      if( Is_Of_Type<float>( arg ) ) {
        parameters->mean_reversion_level = std::stof( arg );
      }
      else {
        std::cout << "ERROR : Mean reversion level value is invalid" << std::endl;
      }

    }
    else if( arg == "--volatility" ) {

      arg = std::string( argv[ argv_idx + 1 ] );
      argv_idx++;
      parameter_args_detected = true;

      if( Is_Of_Type<float>( arg ) ) {
        parameters->volatility = std::stof( arg );
      }
      else {
        std::cout << "ERROR : Volatility value is invalid" << std::endl;
      }

    }
    else if( arg == "--correlation-factor" ) {

      arg = std::string( argv[ argv_idx + 1 ] );
      argv_idx++;
      parameter_args_detected = true;

      if( Is_Of_Type<float>( arg ) ) {
        parameters->correlation_factor = std::stof( arg );
      }
      else {
        std::cout << "ERROR : Correlation factor value is invalid" << std::endl;
      }

    }
    else if( arg == "--strike-price" ) {

      arg = std::string( argv[ argv_idx + 1 ] );
      argv_idx++;
      parameter_args_detected = true;

      if( Is_Of_Type<float>( arg ) ) {
        *strike_price = std::stof( arg );
      }
      else {
        std::cout << "ERROR : Strike price value is invalid" << std::endl;
      }

    }
    else if( arg == "--discounting-rate" ) {

      arg = std::string( argv[ argv_idx + 1 ] );
      argv_idx++;
      parameter_args_detected = true;

      if( Is_Of_Type<float>( arg ) ) {
        *discounting_rate = std::stof( arg );
      }
      else {
        std::cout << "ERROR : Discounting rate value is invalid" << std::endl;
      }

    }

  }

  return parameter_args_detected;

}


// Ending namespaces
}
}

