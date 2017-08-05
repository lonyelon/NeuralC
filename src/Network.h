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
    vfloat3d_t synapses;
    vfloat2d_t neurons;

public:
    Network(vint_t layers);
    Network(void);
    vfloat2d_t get_current_state();
    void set_genetics(vfloat3d_t s);
    vint_t get_layer_blueprint() const;
    vfloat_t get_layer_values(int layer);
    vfloat3d_t get_genetics();
    void clear();
    vfloat_t get_result(vfloat_t inp);
};

#endif