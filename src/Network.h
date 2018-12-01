#ifndef _NETWORK_H_
#define _NETWORK_H_

#include <string>
#include <cmath>
#include <random>
#include <fstream>
#include <iostream>
#include <thread>

#include "NeuralMath.h"

#define file_ext ".txt"
#define data_dir "Data/"

class Network {
private:
    std::vector<std::vector<std::vector<float>>> synapses;
    std::vector<std::vector<float>> neurons;

public:
    /*
        Constructors
    */
    Network(std::vector<int> layers);
    Network(void);

    /*
        Getters and setters
    */
    std::vector<std::vector<float>> get_current_state();
    void set_genetics(std::vector<std::vector<std::vector<float>>> s);
    std::vector<int> get_layer_blueprint();
    std::vector<float> get_layer_values(int layer);
    std::vector<std::vector<std::vector<float>>> get_genetics();

    /*
        Other
    */
    void clear();
    std::vector<float> get_result(std::vector<float> inp);

};

void print_layers(Network net);
float calc_error(std::vector<std::vector<float>> inp, std::vector<std::vector<float>> out, Network n);
std::vector<std::vector<std::vector<float>>> mutate_network(std::vector<std::vector<std::vector<float>>> g, float mut_prob);

#endif