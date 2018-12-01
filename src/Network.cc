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

Network::Network(vector<int> layers)
{
	for (int i = 0; i < layers.size() - 1; i++)
	{
		layers[i]++;
	}


	//Create the neurons
	for (int l = 0; l < layers.size(); l++)
	{
		//Temporal storage for neuronal layer && it's synapses
		vector<float> neuron_layer_tmp;

		for (int n = 0; n < layers[l]; n++)
		{
			neuron_layer_tmp.push_back(0);
		}

		Network::neurons.push_back(neuron_layer_tmp);
	}

	//Create the synapses
	for (int l = 0; l < layers.size() - 1; l++)
	{
		//Synapses of that neuron
		vector<vector<float>> synapses_layer_tmp;
		for (int n = 0; n < layers[l]; n++)
		{
			vector<float> synapses_tmp;

			int t = layers[l + 1];
			if (l != layers.size() - 2)
			{
				t--;
			}

			for (int s = 0; s < t; s++)
			{
				float val = random_range(-0.01, 0.01);
				synapses_tmp.push_back(val);
			}
			synapses_layer_tmp.push_back(synapses_tmp);
		}

		Network::synapses.push_back(synapses_layer_tmp);
	}

	Network::clear();
}

vector<vector<float>> Network::get_current_state()
{
	return Network::neurons;
}

void Network::clear()
{
	for (int l = 0; l < Network::neurons.size(); l++)
	{
		for (int n = 0; n < Network::neurons[l].size(); n++)
		{
			if (l == Network::neurons.size() - 1 || n != Network::neurons[l].size() - 1)
				Network::neurons[l][n] = 0;
			else
				Network::neurons[l][n] = 1;
		}
	}
}

vector<float> Network::get_result(vector<float> inp)
{
	Network::clear();
	for (int i = 0; i < Network::neurons[0].size() - 1; i++)
	{
		Network::neurons[0][i] = inp[i];
	}

	for (int l = 1; l < Network::neurons.size(); l++)
	{
		int t = Network::neurons[l].size();
		if (l != Network::neurons.size() - 1)
		{
			t--;
		}

		for (int n = 0; n < t; n++)
		{
			float value = 0;
			for (int s = 0; s < Network::neurons[l - 1].size(); s++)
			{
				value += Network::neurons[l - 1][s] * Network::synapses[l - 1][s][n];
			}
			value = sigmoid_function(value);
			Network::neurons[l][n] = value;
		}
	}

	vector<float> r;
	for (int n = 0; n < Network::neurons[Network::neurons.size() - 1].size(); n++)
	{
		r.push_back(Network::neurons[Network::neurons.size() - 1][n]);
	}

	return r;
}

void Network::set_genetics(vector<vector<vector<float>>> s)
{
	Network::synapses = s;
}

vector<int> Network::get_layer_blueprint()
{
	vector<int> data;
	for (int i = 0; i < Network::neurons.size(); i++)
	{
		int val = Network::neurons[i].size();

		data.push_back(val);
	}

	return data;
}

vector<float> Network::get_layer_values(int layer)
{
	return Network::neurons[layer];
}

vector<vector<vector<float>>> Network::get_genetics()
{
	return Network::synapses;
}