
#ifndef MODELLING_MPI_MONTE_OPTIONS_HPP
#define MODELLING_MPI_MONTE_OPTIONS_HPP

namespace MPI_MONTE_OPTIONS {


namespace VERSION_1 {

void Run_Multi_Threaded_Simulation_V1( std::vector<float>* end_prices_array_ptr,
                                       unsigned long long total_runs,
                                       unsigned long long total_timesteps,
                                       unsigned long long seed,
                                       bool do_write_to_file,
                                       Heston_Parameters parameters );

float Simulate_Asset_Price_Walk_V1( unsigned long long total_timesteps,
                                    std::mt19937_64* random_engine,
                                    std::normal_distribution<float>* normal_distribution_gen,
                                    Heston_Parameters parameters );


}

}


#endif
