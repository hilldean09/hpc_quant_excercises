
#include "./io_mpi_monte_options.hpp"

#include <string>

namespace MPI_MONTE_OPTIONS {
namespace IO {

void Parse_Parameters_From_Arguments( int argc, char* argv[],
                                      unsigned long long* total_runs,
                                      unsigned long long* total_timesteps,
                                      unsigned long long* seed, 
                                      bool* do_write_to_file,
                                      Heston_Parameters* parameters,
                                      float* strike_price,
                                      float* discounting_rate ) {

  std::string arg;

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

    // TODO: Fix type checking argument

    if( arg == "--write-to-file" ) {

      if( Is_Of_Type<bool>( arg ) ) {
        *total_runs = std::stoull( std::string( argv[ argv_idx + 1 ] ) );
        argv_idx++;
      }

    }
    else if( arg == "--total-runs" ) {

      if( Is_Of_Type<unsigned long long>( arg ) ) {
        *total_runs = std::stoull( std::string( argv[ argv_idx + 1 ] ) );
        argv_idx++;
      }

    }
    else if( arg == "--total_timesteps" ) {

      if( Is_Of_Type<unsigned long long>( arg ) ) {
        *total_timesteps = std::stoull( std::string( argv[ argv_idx + 1 ] ) );
        argv_idx++;
      }

    }
    else if( arg == "--seed" ) {

      if( Is_Of_Type<unsigned long long>( arg ) ) {
        *seed = std::stoull( std::string( argv[ argv_idx + 1 ] ) );
        argv_idx++;
      }

    }
    else if( arg == "--initial-price" ) {

      if( Is_Of_Type<float>( arg ) ) {
        parammeters->initial_price = std::stof( std::string( argv[ argv_idx + 1 ] ) );
        argv_idx++;
      }

    }
    else if( arg == "--initial-variance" ) {

      if( Is_Of_Type<float>( arg ) ) {
        parammeters->initial_variance = std::stof( std::string( argv[ argv_idx + 1 ] ) );
        argv_idx++;
      }

    }
    else if( arg == "--timestep" ) {

      if( Is_Of_Type<float>( arg ) ) {
        parammeters->timestep = std::stof( std::string( argv[ argv_idx + 1 ] ) );
        argv_idx++;
      }

    }
    else if( arg == "--drift" ) {

      if( Is_Of_Type<float>( arg ) ) {
        parammeters->drift = std::stof( std::string( argv[ argv_idx + 1 ] ) );
        argv_idx++;
      }

    }
    else if( arg == "--mean-reversion-speed" ) {

      if( Is_Of_Type<float>( arg ) ) {
        parammeters->mean_reversion_speed = std::stof( std::string( argv[ argv_idx + 1 ] ) );
        argv_idx++;
      }

    }
    else if( arg == "--mean-reversion-level" ) {

      if( Is_Of_Type<float>( arg ) ) {
        parammeters->mean_reversion_level = std::stof( std::string( argv[ argv_idx + 1 ] ) );
        argv_idx++;
      }

    }
    else if( arg == "--volatility" ) {

      if( Is_Of_Type<float>( arg ) ) {
        parammeters->volatility = std::stof( std::string( argv[ argv_idx + 1 ] ) );
        argv_idx++;
      }

    }
    else if( arg == "--correlation-factor" ) {

      if( Is_Of_Type<float>( arg ) ) {
        parammeters->correlation_factor = std::stof( std::string( argv[ argv_idx + 1 ] ) );
        argv_idx++;
      }

    }
    else if( arg == "--strike-price" ) {

      if( Is_Of_Type<float>( arg ) ) {
        *strike_price = std::stof( std::string( argv[ argv_idx + 1 ] ) );
        argv_idx++;
      }

    }
    else if( arg == "--discounting-rate" ) {

      if( Is_Of_Type<float>( arg ) ) {
        *discounting_rate = std::stof( std::string( argv[ argv_idx + 1 ] ) );
        argv_idx++;
      }

    }

  }

}


// Ending namespaces
}
}

