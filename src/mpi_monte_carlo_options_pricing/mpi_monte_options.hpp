

#include <random>

namespace MPI_MONTE_OPTIONS {

float* Simulate_Asset_Price_Walk( unsigned long long total_timesteps,
                                  float* price_path_buffer,
                                  std::default_random_engine* random_engine,
                                  float initial_price = MMCOP_DEFAULT_INITIAL_PRICE, 
                                  float initial_log_deviation = MMCOP_DEFAULT_INITIAL_LOG_DEVIATION, 
                                  float mean = MMCOP_DEFAULT_MEAN, 
                                  float persistence = MMCOP_DEFAULT_PERSISTENCE,
                                  float volatility = MMCOPD_DEFULT_VOLATILITY );

float* Run_Single_Threaded_Simulation( unsigned long long total_runs,
                                       unsigned long long total_timesteps,
                                       unsigned long long seed = DEFAULT_SEED,
                                       bool do_write_to_file = false,
                                       float initial_price = MMCOP_DEFAULT_INITIAL_PRICE, 
                                       float initial_log_deviation = MMCOP_DEFAULT_INITIAL_LOG_DEVIATION, 
                                       float mean = MMCOP_DEFAULT_MEAN, 
                                       float persistence = MMCOP_DEFAULT_PERSISTENCE,
                                       float volatility = MMCOP_DEFAULT_VOLATILITY );



}
