#ifndef _EXTRA_H_
#define _EXTRA_H_

#include <string>
#include <cmath>
#include <random>
#include <fstream>
#include <iostream>
#include <thread>

#include "Network.h"

#define file_ext ".txt"
#define data_dir "Data/"

using namespace std;

void print_layers(const Network net);
float calc_error(Network n, const vfloat2d_t inp, const vfloat2d_t out);

#endif