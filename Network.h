#ifndef _NETWORK_H_
#define _NETWORK_H_
 
#include <vector>
 
//Math
double sigmoid_function(double x);
double sigmoid_derivative(double x);
double rectify_function(double x);
double random_range(double min, double max);
 
//The network
class Network 
{
private:
    std::vector<std::vector<double>> neurons;
    std::vector<std::vector<std::vector<double>>> synapses;
    void clear();
public:
    Network(std::vector<int> layers);
    std::vector<double> get_result(std::vector<double> inp);
    std::vector<int> get_layer_blueprint();
    std::vector<std::vector<std::vector<double>>> get_genetics();
    std::vector<double> get_layer_values(int layer);
    void set_genetics(std::vector<std::vector<std::vector<double>>> s);
    void gradient_descent(std::vector<std::vector<double>>, std::vector<std::vector<double>>, int);
};
 
//Useful things
void print_layers(Network net);
 
//Learning 
double calc_error(std::vector<std::vector<double>> inp, std::vector<std::vector<double>> out, Network n);
std::vector<std::vector<std::vector<double>>> mutate_network(std::vector<std::vector<std::vector<double>>> g, double mut_prob);
 
#endif
