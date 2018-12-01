#ifndef _NEURAL_MATH_H_
#define _NEURAL_MATH_H_

#include <cmath>
#include <random>
#include <vector>

#define vint std::vector<int>
#define vint2d std::vector<std::vector<int>>

#define vfloat std::vector<float>
#define vfloat2d std::vector<std::vector<float>>
#define vfloat3d std::vector<std::vector<std::vector<float>>>

float sigmoid_function(float x);
float sigmoid_derivative(float x);
float rectify_function(float x);
float get_sign(float x);
float random_range(float min, float max);

#endif