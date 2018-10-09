#ifndef _NEURAL_MATH_H_
#define _NEURAL_MATH_H_

#include <cmath>
#include <random>

float sigmoid_function(float x);
float sigmoid_derivative(float x);
float rectify_function(float x);
float get_sign(float x);
float random_range(float min, float max);

#endif