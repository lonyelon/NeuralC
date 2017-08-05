#ifndef _GRADIENT_DESCENT_H_
#define _GRADIENT_DESCENT_H_

#include <vector>
#include <iostream>
#include <thread>

#include "Network.h"
#include "NeuralMath.h"

void gradient_descent(Network *N, const vfloat2d_t inp, const vfloat2d_t out, const int it, const int cores);

#endif