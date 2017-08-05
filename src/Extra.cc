#include "Network.h"

#include <string>
#include <cmath>
#include <random>
#include <fstream>
#include <iostream>
#include <thread>

#include "NeuralMath.h"

#define file_ext ".txt"
#define data_dir "Data/"

using namespace std;

void print_layers(const Network net) {
	vector<int> layers = net.get_layer_blueprint();
	for (int l = 0; l < layers.size(); l++) {
		string buff = "Layer[" + to_string(l) + "]->";
		cout << buff;
		for (int n = 0; n < layers[l]; n++) {
			if (n != 0) {
				for (int i = 0; i < buff.size(); i++) {
					cout << " ";
				}
			}
			cout << "Neuron[" << n << "]" << endl;
		}
		cout << endl;
	}
}

float calc_error(Network n, const vfloat2d_t inp, const vfloat2d_t out) {
	float err = 0;
	for (int i = 0; i < inp.size(); i++) {
		vfloat_t r = n.get_result(inp[i]);
		for (int q = 0; q < inp[i].size(); q++) {
			err += 0.5*pow(out[i][q] - r[q], 2);
		}
	}
	return err;
}