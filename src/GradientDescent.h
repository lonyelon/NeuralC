#ifndef _GRADIENT_DESCENT_H_
#define _GRADIENT_DESCENT_H_

#include <vector>
#include <iostream>
#include <thread>

#include "Network.h"
#include "NeuralMath.h"

void gradient_descent(Network *N, std::vector<std::vector<float>> inp, std::vector<std::vector<float>> out, int it, int cores);

#endif