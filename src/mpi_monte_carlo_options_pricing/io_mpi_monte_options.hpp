
#ifndef IO_MPI_MONTE_OPTIONS_HPP
#define IO_MPI_MONTE_OPTIONS_HPP

#include "./pre_controls.hpp"
#include "./mpi_monte_options.hpp"

#include <string>
#include <sstream>

namespace MPI_MONTE_OPTIONS {
namespace IO {

// Adapted from https://stackoverflow.com/a/447307
template <class T_type_to_check>
bool Is_Of_Type( std::string string_to_check ) {

  // Effectively uses a string stream to attempt to construct a value 
  // of the given type and checking if fail or bad bits are set. "noskipws"
  // indicates that initial whitespace is not overlooked.

  std::istringstream input_string_stream( string_to_check );
  T_type_to_check testing_value;

  input_string_stream >> testing_value;

  return input_string_stream.eof() && !input_string_stream.fail();
}

bool Parse_Parameters_From_Arguments( int argc, char* argv[],
                                      unsigned long long* total_runs,
                                      unsigned long long* total_timesteps,
                                      unsigned long long* seed, 
                                      bool* do_write_to_file,
                                      Heston_Parameters* parameters,
                                      float* strike_price,
                                      float* discounting_rate );


}

}

#endif

