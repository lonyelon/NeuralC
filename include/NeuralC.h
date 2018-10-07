#ifndef _NEURALC_H_
#define _NEURALC_H_

#include <vector>
#include <string>
#include <thread>
#include <cmath>
#include <chrono>
#include <fstream>
#include <algorithm>

float sigmoid_function(float x);
float sigmoid_derivative(float x);
float rectify_function(float x);
float get_sign(float x);
float random_range(float min, float max);

class Network
{
private:
	std::vector<std::vector<float>> neurons;
	std::vector<std::vector<std::vector<float>>> synapses;
	void clear();
public:
	Network(std::vector<int> layers);
	std::vector<float> get_result(std::vector<float> inp);
	std::vector<int> get_layer_blueprint();
	std::vector<std::vector<std::vector<float>>> get_genetics();
	std::vector<float> get_layer_values(int layer);
	void set_genetics(std::vector<std::vector<std::vector<float>>> s);
	std::vector<std::vector<float>> get_current_state();
};

//Useful things
void print_layers(Network net);

//Learning 
float calc_error(std::vector<std::vector<float>> inp, std::vector<std::vector<float>> out, Network n);
std::vector<std::vector<std::vector<float>>> mutate_network(std::vector<std::vector<std::vector<float>>> g, float mut_prob);

void gradient_descent(Network *N, std::vector<std::vector<float>> inp, std::vector<std::vector<float>> out, int it, int cores);

void save_genetics(std::string file, Network n);
Network load_genetics(std::string path);

#endif