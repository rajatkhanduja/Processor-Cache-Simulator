/* This file declares the cache class */

#ifndef CACHE_H_INCLUDED
#define CACHE_H_INCLUDED

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cstdio>

class element
{
	public:
		unsigned long int tag;
		unsigned long int time_stored,time_accessed;
		bool valid;
};


class cache
{
	private:
		int num_sets,assoc,line_s,wp,rp,cache_hit_time,cache_miss_penalty;
		unsigned int n_hit,n_miss;		// Maintains the number of cache hits and misses
		int size;
		unsigned long int timestamp;		// Maintains the time
		element **mem;

	public:
		cache(int *arr);
		bool insert(unsigned long int val);
		bool inCache(unsigned long int val);
		void read_write_request(unsigned long int val,int read_write);
		unsigned int hits();
		unsigned int misses();
		unsigned long int time_taken();
		unsigned int TMAT();		// Total Memory Access time
		float AMAT();		// Average Memory Access time

};

#endif 	//End of file
