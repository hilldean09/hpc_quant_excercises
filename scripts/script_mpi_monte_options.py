
import sys
import numpy as np
import matplotlib.pyplot as plt

def Read_NPY( npy_filename ):
    price_paths_array = np.load( npy_filename )

    return price_paths_array

def Generate_Price_Paths_Plot( price_paths_array ):
    for run in range( 0,  int( price_paths_array.shape[ 0 ] ) ):
        plt.plot( price_paths_array[ run ][ : ] )


price_paths_array = Read_NPY( sys.argv[ 1 ] )

Generate_Price_Paths_Plot( price_paths_array )

plt.yscale( 'log' )
plt.show()
