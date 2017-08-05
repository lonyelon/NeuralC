#ifndef _NETWORK_H_
#define _NETWORK_H_

#include <vector>
#include "Neuron.h"

class Network
{
private:
    std::vector<std::vector<Neuron>> Layer;
    void connect();
public:
    Network(int inputs, int outputs);
    void add_layer(std::vector<Neuron> l);
    void remove_layer(int n);
};

#endif