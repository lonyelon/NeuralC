#include <iostream>
#include <vector>
#include "Neuron.h"

using namespace std;

class Brain 
{
private:
    vector<vector<Neuron>> Neurons;
public:
    void Barin()
    {
        Neurons.push_back(vector<Neuron>());
        Neurons.push_back(vector<Neuron>());
    }

    int add_layer()
    {

    }

    int add_neuron()
    {

    }
};