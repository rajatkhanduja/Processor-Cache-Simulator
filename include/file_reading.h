/* File describes the classes necessary for reading both the input and configuration files.
 */

#ifndef FILE_READING_INCLUDED
#define FILE_READING_INCLUDED

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <cstdlib>
#include <cstring>
#include <cstdio>

#include "cache.h"

using std::ifstream;
using std::ofstream;

void conf_file_reading(ifstream &fin,int *conf_arr);
void input_file_reading(ifstream &fin,cache *mem,ofstream &output);


#endif      // End of file
