#include "Files.h"

#include <iostream>
#include <vector>

using namespace std;

void save_genetics(Network n, string path) {
	ofstream file;
	file.open(path);
	vfloat3d_t synapses = n.get_genetics();
	vint_t layers = n.get_layer_blueprint();
	int layer_count = layers.size();
	file << layers.size();
	for (int l = 0; l < layer_count; l++) {
		file << "\r\n" << layers[l];
	}
	string out;
	for (int l = 0; l < layer_count - 1; l++) {
		for (int n = 0; n < layers[l]; n++) {
			int t = 0;
			if (l != synapses.size() - 1) {
				t = 1;
			}
			for (int s = 0; s < layers[l + 1] - t; s++) {
				out += "\r\n" + to_string(synapses[l][n][s]);
			}
		}
	}
	file << out;
	file.close();
}

Network load_genetics(string path) {
	ifstream file;
	file.open(path);
	string buff;
	getline(file, buff);
	int network_size = stoi(buff);
	vint_t layers;
	for (int l = 0; l < network_size; l++) {
		getline(file, buff);
		int count = stoi(buff);

		if (l != network_size - 1) {
			count--;
		}

		layers.push_back(count);
	}
	vfloat_t nsynapses;
	vfloat2d_t lsynapses;
	vfloat3d_t synapses;
	int l = 0;
	int n = 0;
	int s = 0;
	while (!file.eof()) {
		getline(file, buff);
		nsynapses.push_back(stod(buff));
		s++;
		if (s == layers[l + 1]) {
			n++;
			s = 0;
			lsynapses.push_back(nsynapses);
			nsynapses.clear();
		}
		if (n == layers[l] + 1) {
			s = 0;
			n = 0;
			l++;
			synapses.push_back(lsynapses);
			lsynapses.clear();
		}
		if (l == layers.size() - 1) {
			break;
		}
	}
	Network net = Network(layers);
	net.set_genetics(synapses);
	file.close();
	return net;
}