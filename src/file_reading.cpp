/* File in which the functions for reading the files are
 * implemented
 */

#include "../include/file_reading.h"

void conf_file_reading(ifstream &fin,int *conf_arr)
{
    /* Configuration file is read in this function and the parameters are
     * stored in the 'array' passed.
     *
     * Index        property
     *   0          number of sets
     *   1          associativity
     *   2          Linesize
     *   3          WritePolicy
     *   4          Replacement policy
     *   5          Cache hit time
     *   6          Cache miss penalty
     */
   int i=0;

   while(!fin.eof() && i<7)
   {
		std::string line;
		getline(fin,line);

		if (line[0]=='#' || line[0]=='\n' || line[0]==0)
			continue;

		conf_arr[i]=atoi(line.c_str());
		//conf_arr[i]=0 signifies default
		i++;
   }

}

long unsigned int hex2int(std::string &hex_string)
{
	int i;
	unsigned long int val=0;
	for(i=0;i<hex_string.size();i++)
	{
		if(hex_string[i]>='0' && hex_string[i]<='9')
			val=val*16+(hex_string[i]-'0');
		else if(hex_string[i]>='a' && hex_string[i]<='f')
			val=val*16+(hex_string[i]-'a')+10;
	}

	return val;
}

void input_file_reading(ifstream &fin,cache*mem,ofstream &output)
{
	while(!fin.eof())
	{
		unsigned long int val;
		std::string req,val_string;
		int read_write;

		std::string line;
		getline(fin,line);
		if (line[0]=='\n' || line[0]=='\x0')
			continue;

		char ptr[line.size()+1];

		strcpy(ptr,line.c_str());
		val_string=strtok(ptr," ,\t");
		val=hex2int(val_string);
		req=strtok(NULL," ,\t");

		read_write=((req.compare("RD")==0)?1:((req.compare("WR")==0)?2:0));
		/* read_write = 1 (for RD)
		 * read_write = 2 (for WR)
		 * read_write = 0 (otherwise, incorrect input)
		 */
	//	std::cout<<"val ="<<val<<std::endl;
		if(read_write)
			mem->read_write_request(val,read_write);

	}

	output<<"Numer of hits : "<<mem->hits()<<"\nNumber of misses : "<<mem->misses()<<"\nTotal Memory Access time : "<<mem->TMAT()<<"\nAverage Memory Access Time : "<<mem->AMAT()<<"\nBus busy time : "<<mem->time_taken()<<std::endl;

}
