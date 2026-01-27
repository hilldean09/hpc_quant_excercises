

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

}
