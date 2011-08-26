// This file defines the functions of the cache class

#include "../include/cache.h"

cache::cache(int *arr)
{
	/* Configuration details */
	num_sets=arr[0];
	assoc=arr[1];
	line_s=arr[2];
	wp=arr[3];
	rp=arr[4];
	cache_hit_time=arr[5];
	cache_miss_penalty=arr[6];
	/* ----- */

	/* Initialize the clock (timestamp) and hits/misses to zero */
	timestamp=n_hit=n_miss=0;
	/* ----- */


	/* Total size of the cache */
	size=num_sets*line_s;
	/* ------ */

	mem=new element*[assoc];
	unsigned int i,j;
	for(i=0;i<assoc;i++)
	{
		mem[i]=new element[num_sets*line_s];
	}

	for(i=0;i<assoc;i++)
	{
		for(j=0;j<size;j++)
			mem[i][j].valid=false;
	}
}

bool cache::inCache(long unsigned int val)
{
	// Increase time
	timestamp++;

	long unsigned int line_val=val%line_s;
	long unsigned int index=(val/line_s)%num_sets;
	long unsigned int tag=(val/line_s)/num_sets;


	/* Calculate the array index where the value needs to be checked */
	long unsigned int arr_index=(index*line_s)+line_val;
	unsigned long int layer;


	/* Check in the 2-D array for the required tag at the
	 * corresponding index in 'each' 1-D array
	 */

	for(layer=0;layer<assoc;layer++)
	{
		if(mem[layer][arr_index].valid)
		{
			if(mem[layer][arr_index].tag==tag)
			{

			//	printf("%lu %lu %lu %lu\n",tag,index,line_val,timestamp);
				mem[layer][arr_index].time_accessed=timestamp;
				return true;
			}
		}
	}

	/* If not found, return false */
	return false;
}

bool cache::insert(unsigned long int val)
{
	// Increase time
	timestamp++;

	long unsigned int line_val=val%line_s;
	long unsigned int index=(val/line_s)%num_sets;
	long unsigned int tag=(val/line_s)/num_sets;

	/* Calculate the entry point in the array */

	long unsigned int arr_index=(index*line_s)+line_val;
	long unsigned int layer;
	//printf("%lu %lu %lu %lu\n",tag,index,line_val,timestamp);
	for(layer=0;layer<assoc && (mem[layer][arr_index].valid);layer++);
	//std::cerr<<layer<<","<<arr_index<<::endl;
	if(layer!=assoc)
	{
		// If appropriate spot is found, write it there
		mem[layer][arr_index].tag=tag;
		mem[layer][arr_index].valid=true;
		mem[layer][arr_index].time_stored=timestamp;
		mem[layer][arr_index].time_accessed=timestamp;
		return true;
	}

	else
	{
		/* If associativity = 1, replace the only place in the memory
		 * where it can be entered.
		 */

		if(assoc==1)
		{
			layer=0;
			mem[layer][arr_index].tag=tag;
			mem[layer][arr_index].valid=true;
			mem[layer][arr_index].time_stored=timestamp;
			mem[layer][arr_index].time_accessed=timestamp;
			return true;
		}

		/* Replace one of the places on the basis of the replacement policy described*/

		if(rp==1)
		{
			/* Random replacement */
			srand(time(NULL));
			int replace_index=rand()%assoc;
			mem[replace_index][arr_index].tag=tag;
			mem[replace_index][arr_index].valid=true;
			mem[replace_index][arr_index].time_stored=timestamp;
			mem[replace_index][arr_index].time_accessed=timestamp;

			return true;
		}
		else if(rp==2)
		{
			/* FIFO replacement
			 * Compare the time_stored and replace the one
			 * with the minimum value
			 */

			unsigned int i,replace_index;
			unsigned long int min_time=0;
			min_time--;		// -1 = MAX of unsigned int
			for(i=0;i<assoc;i++)
			{

				if(mem[i][arr_index].time_stored<min_time)
				{
					min_time=mem[i][arr_index].time_stored;
					replace_index=i;
				}

			}

			/* Finally, replace value at the obtained index */
			mem[replace_index][arr_index].tag=tag;
			mem[replace_index][arr_index].valid=true;
			mem[replace_index][arr_index].time_stored=timestamp;
			mem[replace_index][arr_index].time_accessed=timestamp;
			return true;

		}
		else if(rp==3)
		{
			/* LRU replacement
			 * Compare the time_accessed and replace the one with the minimum value
			 */

			unsigned long int i,replace_index;
			unsigned long int min_time=0;
			min_time--;		// -1 = MAX of unsigned int
			for(i=0;i<assoc;i++)
			{
				if(mem[i][arr_index].time_accessed<min_time)
				{
					min_time=mem[i][arr_index].time_accessed;
					replace_index=i;
				}
			}

			/* Finally, replace value at the obtained index */
			mem[replace_index][arr_index].tag=tag;
			mem[replace_index][arr_index].valid=true;
			mem[replace_index][arr_index].time_stored=timestamp;
			mem[replace_index][arr_index].time_accessed=timestamp;
			return true;

		}
		else
		{
			std::cerr<<"Unknown replacement policy"<<std::endl;
			exit(2);		// 2 => unknown replacement policy
		}


	}


}


void cache::read_write_request(unsigned long int  val,int read_write)
{
	/*
	 * read_write = 1 (for read)
	 * read_write = 2 (for write)
	 */

	/* Irrespective of the read_write request, check if the value is already present */
	if(!inCache(val))
	{
		n_miss++;
		if(insert(val))
		{
			if(read_write==1)
				return;
			else
			{
				if(wp==1)
				{
					// Write back, increase time accordingly
					timestamp=timestamp+2;
					return;
				}
				else if(wp==2)
				{
					// Write through
					return;
				}
				else
				{
					std::cerr<<"Unknown write policy"<<std::endl;
					exit(3);			// Unknown write policy
				}
			}
		}
	}
	else
	{
		n_hit++;
	//	printf("%lx %lu %d\n",val,val,read_write);
		/* In case of read request, return */
		if (read_write==1)
		{
			return;
		}

		else
		{
			if(wp==1)
			{
				// Write back, increase time accordingly
				return;
			}
			else if(wp==2)
			{
				timestamp=timestamp+2;
				return;
			}
			else
			{
				std::cerr<<"Unknown write policy"<<std::endl;
				exit(3);			// Unknown write policy
			}
		}
	}

}

unsigned int cache::hits()
{
		return n_hit;
}

unsigned int cache::misses()
{
		return n_miss;
}

unsigned long int cache::time_taken()
{
		return timestamp;
}

unsigned int cache::TMAT()
{
	return (n_hit*cache_hit_time + n_miss*cache_miss_penalty);
}

float cache::AMAT()
{
	return (TMAT()*1.0/(n_hit+n_miss));
}
