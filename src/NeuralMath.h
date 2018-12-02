#ifndef _NEURAL_MATH_H_
#define _NEURAL_MATH_H_

#include <cmath>
#include <random>
#include <vector>

#define vint_t std::vector<int>
#define vfloat_t std::vector<float>
#define vfloat2d_t std::vector<std::vector<float>>
#define vfloat3d_t std::vector<std::vector<std::vector<float>>>

float sigmoid_function(float x);
float sigmoid_derivative(float x);
float rectify_function(float x);
float get_sign(float x);
float random_range(float min, float max);

#endif