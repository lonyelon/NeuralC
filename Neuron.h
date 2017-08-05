#ifndef _NEURON_H_
#define _NEURON_H_

#include <vector>
#include "NeuralMath.h"

class Neuron
{
private:
    std::vector<double> Synapses;
    std::vector<Neuron*> Neurons;
    double Value = 0;
    /*
        TYPE 0 => f(x) = x.
        TYPE 1 => f(x) = tanh(x/2).
        TYPE 2 => f(x) = x, only when x > 0. When x <= 0, x = 0.
    */
    int Type;

public:
    void process_data();
    Neuron(int t, std::vector<Neuron*> n, std::vector<double> s);
    void add_value(double val);
    void send_data();
    double get_value();
    int get_type();
};

#endif