#ifndef _NETWORK_H_
#define _NETWORK_H_

#include <vector>
#include <string>

#define vector2d std::vector<std::vector<float>>
#define vector3d std::vector<vector2d>

float sigmoid_function(float x);
float sigmoid_derivative(float x);
float rectify_function(float x);
float random_range(float min, float max);

class Network
{
private:
	vector2d neurons;
	vector3d synapses;
	void clear();
public:
	Network(std::vector<int> layers);
	std::vector<float> get_result(std::vector<float> inp);
	std::vector<int> get_layer_blueprint();
	vector3d get_genetics();
	std::vector<float> get_layer_values(int layer);
	void set_genetics(vector3d s);
	void gradient_descent(vector2d, vector2d, int);
};

//Useful things
void print_layers(Network net);

//Learning 
float calc_error(vector2d inp, vector2d out, Network n);
vector3d mutate_network(vector3d g, float mut_prob);
void save_genetics(std::string file, Network n);
Network load_genetics(std::string path);

#endif