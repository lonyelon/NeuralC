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

void print_layers(Network net);
float calc_error(vector<vector<float>> inp, vector<vector<float>> out, Network n);

#endif