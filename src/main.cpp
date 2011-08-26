// The file contains the main function

/* Argument list :-
 *
 * arg1 : input_file
 * arg2 : configuration_file
 */

#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include "../include/file_reading.h"
#include "../include/cache.h"


using std::string;
using std::ifstream;

int main(int argc,char*args[])
{
	if(argc<4)
	{
		// Insufficient number of parameters are passed to the program
		std::cerr<<"Please input the input file and the configuration file\n";
		std::cerr<<"Usage : cache_simulator <input file> <configuration file>\n";
        	exit(1);        // exit status 1 : Incorrect number of inputs.
    	}	

	// If parameters are correct, continue

	ifstream input(args[1]);
	ifstream conf(args[2]);
	ofstream output(args[3]);

	int conf_arr[7];

    /* Configuration is stored in the array conf_arr
     * Index        property
     *   0          number of sets
     *   1          associativity
     *   2          Linesize
     *   3          WritePolicy
     *   4          Replacement policy
     *   5          Cache hit time
     *   6          Cache miss penalty
     */

    // Set the configuration array by reading the file

	conf_file_reading(conf,conf_arr);

	/* Initialize cache */
	cache *cache_mem=new cache(conf_arr);

	input_file_reading(input,cache_mem,output);

	input.close();
	conf.close();
	output.close();

	return 0;
}
