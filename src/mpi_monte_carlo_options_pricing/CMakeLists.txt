
target_sources( mpi_monte_options_lib
  PUBLIC
    mpi_monte_options.cpp io_mpi_monte_options.cpp
)

# Main executable
target_sources( run_mpi_monte_options
  PRIVATE
    run_mpi_monte_options.cpp
)

target_link_libraries( run_mpi_monte_options
  PRIVATE
    mpi_monte_options_lib
)

# Testing
target_sources( test_mpi_monte_options 
  PRIVATE 
    test_mpi_monte_options.cpp
)

target_link_libraries( test_mpi_monte_options
  PRIVATE
    mpi_monte_options_lib
)

# Benchmarking
target_sources( benchmark_mpi_monte_options 
  PRIVATE
    benchmark_mpi_monte_options.cpp
)

target_link_libraries( benchmark_mpi_monte_options 
  PRIVATE
    mpi_monte_options_lib
)

