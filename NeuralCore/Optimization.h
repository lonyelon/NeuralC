#ifndef _OPTIMIZATION_H_
#define _OPTIMIZATION_H_

#include <vector>
#include "Network.h"

void gradient_descent(std::vector<std::vector<std::vector<float>>>* synapses, std::vector<int> blue, std::vector<std::vector<float>> inp, std::vector<std::vector<float>> out, int rep);

#endif