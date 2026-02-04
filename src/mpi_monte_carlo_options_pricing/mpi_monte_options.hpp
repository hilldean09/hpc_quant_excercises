

#ifndef MMMCOP_HEADER
#define MMMCOP_HEADER

#include <random>

namespace MPI_MONTE_OPTIONS {

void Simulate_Asset_Price_Walk( unsigned long long total_timesteps,
                                  std::vector<float> price_path_buffer,
                                  std::mt19937_64* random_engine,
                                  std::normal_distribution<float>* normal_distribution_gen );

int Write_Numpy_File_Header( std::ofstream output_stream  );

int Write_Path_To_Numpy_File( std::vector<float> price_path_buffer, std::ofstream output_stream );

std::vector<float> Run_Single_Threaded_Simulation( unsigned long long total_runs,
                                       unsigned long long total_timesteps,
                                       unsigned long long seed,
                                       bool do_write_to_file );


float Compute_Call_Price( std::vector<float>* price_paths,
                          unsigned long long total_runs,
                          unsigned long long total_timesteps,
                          float strike_price,
                          float discounting_rate );

}

#endif


