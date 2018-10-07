#include "../include/NeuralC.h"

#include <cmath>
#include <random>

using namespace std;

float sigmoid_function(float x)
{
	float e = 2.718281828459;
	return 1 / (1 + pow(e, -x));
	//return tanh(x); 
}

float sigmoid_derivative(float x)
{
	float e = 2.718281828459;
	return x*(1 - x);
	//return 1 - pow(x , 2);
}

float rectify_function(float x)
{
	if (x > 0)
		return x;
	return 0;
}

float get_sign(float x)
{
	if (x > 0)
		return 1;
	return -1;
}

//Random number (float) betwen min and max
float random_range(float min, float max)
{
	uniform_real_distribution<float> rn(min, max);
	mt19937 mt;
	mt.seed(random_device{}());
	return rn(mt);
}