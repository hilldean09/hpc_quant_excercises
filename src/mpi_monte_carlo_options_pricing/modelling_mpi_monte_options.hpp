
#ifndef MODELLING_MPI_MONTE_OPTIONS_HPP
#define MODELLING_MPI_MONTE_OPTIONS_HPP

namespace MPI_MONTE_OPTIONS {



namespace VERSION_1 {

float Run_Multi_Threaded_Simulation( unsigned long long total_runs,
                                        unsigned long long total_timesteps,
                                        unsigned long long seed,
                                        bool do_write_to_file,
                                        Heston_Parameters parameters );

float Simulate_Asset_Price_Walk( unsigned long long total_timesteps,
                                    std::mt19937_64* random_engine,
                                    std::normal_distribution<float>* normal_distribution_gen,
                                    Heston_Parameters parameters );

}


}


#endif
