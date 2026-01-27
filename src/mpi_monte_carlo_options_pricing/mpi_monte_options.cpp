
#include <cmath>
#include <random>

namespace MPI_MONTE_OPTIONS {

float* Simulate_Asset_Price_Walk( unsigned long long total_timesteps,
                                  float* price_path_buffer,
                                  std::default_random_engine* random_engine,
                                  float initial_price,
                                  float initial_log_deviation,
                                  float mean,
                                  float persistence,
                                  float volatility ) {

  price_path_buffer[ 0 ] = std::log( initial_price );
  
  float deviation = initial_log_deviation;

  for( unsigned long long timestep = 0; timestep < total_timesteps; timestep++ ) {

    // Log return equation
    // s(t+1) = s(t) + mean + exp( h(t) ) * normal_distribution()
    price_path_buffer[ timestep + 1 ] = price_path_buffer[ timestep ]
                                            + mean + ( std::exp( log_deviation )
                                            * std::normal_distribution( *random_engine ) );

    // Mean-reverting log-volatility equation
    // h(t+1) = persistence * h(t) + volatility * normal_distribution()
    log_deviation = persistence * log_deviation + volatility * std::normal_distribution( *random_engine );

  }
  
  for( unsigned long long timestep = 1; timestep <= total_timesteps; timestep++ ) {
    price_path_buffer[ timestep ] = std::exp( price_path_buffer );
  }

  return price_path_buffer;
}

}
