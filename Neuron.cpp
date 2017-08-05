#include <iostream>
#include "Neuron.h"

using namespace std;

void Neuron::process_data()
{
    switch (Neuron::Type)
    {
    case 0:
        break;
    case 1:
        Neuron::Value = sigmoid_function(Neuron::Value);
        break;
    case 2:
        Value = rectify_function(Value);
        break;
    }
}

Neuron::Neuron(int t, vector<Neuron*> n, vector<double> s)
{
    Type = t;
    Neurons = n;
    Synapses = s;
}

void Neuron::add_value(double val)
{
    Neuron::Value += val;
}

void Neuron::send_data()
{
    Neuron::process_data();
    for (int i = 0; i < Neuron::Neurons.size(); i++)
    {
        Neuron::Neurons[i]->add_value(Neuron::Value * Neuron::Synapses[i]);
    }
}

double Neuron::get_value()
{
    return Neuron::Value;
}

int Neuron::get_type() 
{
    return Neuron::Type;
}