# hpc_quant_exercises
A collection of my exercise in high-performance computing and low latency programming in the context of quantitative finance.

# Current Exercises
## MPI Monte Carlo Options Pricing
- Uses the Heston stochastic volatility model to simulate asset price movements, computing a call price.
- Developed to explore using MPI and profiling / optimising very tight loops.
- Includes a Python script (```script_mpi_monte_options```) to visualise the price walks from the written data within output directories.

**Executables Available**
- ```run_mpi_monte_options```
- ```test_mpi_monte_options```
- ```benchmark_mpi_monte_options```

# Build
**Requirements**:
- CMake
- C/C++ Compiler
- OpenMP
- MPI
- [Google Benchmark](https://github.com/google/benchmark)
- Python3 (including numpy and matplotlib) for scripts


To build any given executable (relevant scripts will be copied alongside them), first the repository must be cloned and a build directory made. This can be done via:
```bash
# Clone the repository
git clone https://github.com/hilldean09/hpc_quant_excercises.git

# Enter the repository then create and enter a subdirectory named "build"
cd hpc_quant_excercises

# Initialise git submodules
git submodule init

# Create and enter a subdirectory named build
mkdir build
cd build

# Generate build files using CMake
cmake .. -DCMAKE_BUILD_TYPE=Release
# The default build type is "Release" (even without the flag) and can
# be changed to "Debug" by changed the specified build type accordingly

# Make target e.g. test_mpi_monte_options
make [desired target]
```

# Acknowledgements 
- Google Benchmark : https://github.com/google/benchmark
- cnpy : https://github.com/rogersce/cnpy
