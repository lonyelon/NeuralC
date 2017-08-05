#include <iostream>
#include "NeuralMath.h"

using namespace std;

double sigmoid_function(double x)
{
    return tanh(x / 2);
}

double rectify_function(double x)
{
    if (x > 0)
        return x;
    else
        return 0;
}