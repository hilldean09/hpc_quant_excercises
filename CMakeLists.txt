
cmake_minimum_required( VERSION 4.2.0 )
project( camasim LANGUAGES C CXX )

set( CMAKE_CXX_STANDARD 23 )
set( CMAKE_CXX_STANDARD_REQUIRED ON )
set( CMAKE_CXX_EXTENSIONS OFF )

if( NOT CMAKE_BUILD_TYPE )
  set( CMAKE_BUILD_TYPE Release )
endif()

set( CMAKE_CXX_FLAGS "-Wall -Wextra -pedantic" )
set( CMAKE_CXX_FLAGS_DEBUG "-g" )
set( CMAKE_CXX_FLAGS_RELEASE "-O3" )

find_package( MPI REQUIRED COMPONENTS C CXX )
find_package( OpenMP REQUIRED )

add_library( cnpy STATIC external/cnpy/cnpy.cpp )
target_include_directories( cnpy PUBLIC external/cnpy )

add_executable( test_mpi_monte_options )
target_link_libraries( test_mpi_monte_options PRIVATE cnpy )

add_subdirectory( src )
add_subdirectory( scripts )
