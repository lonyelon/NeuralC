#include <string>
#include <cmath>
#include <random>
#include <fstream>
#include <iostream>
#include <thread>
#include "Network.h"

#define file_ext ".txt"
#define data_dir "Data/"

using namespace std;

/*

Math needed for the net

*/

float sigmoid_function(float x)
{
	float e = 2.718281828459;
	return 1 / (1 + pow(e, -x));
	//return tanh(x); 
}

float sigmoid_derivative(float x)
{
	float e = 2.718281828459;
	return x*(1 - x);
	//return 1 - pow(x , 2);
}

float rectify_function(float x)
{
	if (x > 0)
		return x;
	return 0;
}

float get_sign(float x)
{
	if (x > 0)
		return 1;
	return -1;
}

//Random number (float) betwen min and max
float random_range(float min, float max)
{
	uniform_real_distribution<float> rn(min, max);
	mt19937 mt;
	mt.seed(random_device{}());
	return rn(mt);
}

/*

Aditional functions that are useful

*/

void print_layers(Network net)
{
	vector<int> layers = net.get_layer_blueprint();
	for (int l = 0; l < layers.size(); l++)
	{
		string buff = "Layer[" + to_string(l) + "]->";
		cout << buff;
		for (int n = 0; n < layers[l]; n++)
		{
			if (n != 0)
			{
				for (int i = 0; i < buff.size(); i++)
				{
					cout << " ";
				}
			}
			cout << "Neuron[" << n << "]" << endl;
		}
		cout << endl;
	}
}

//Compares the result of "inp" to what we expected ("out") and retuen the error
float calc_error(vector2d inp, vector2d out, Network n)
{
	float err = 0;
	for (int i = 0; i < inp.size(); i++)
	{
		vector<float> r = n.get_result(inp[i]);
		for (int q = 0; q < inp[i].size(); q++)
		{
			err += 0.5*pow(out[i][q] - r[q], 2);
		}
	}
	//err /= inp.size();
	return err;
}

//Randomly changes the value of one synapse, used in genetic algorithms
vector3d mutate_network(vector3d g, float mut_prob)
{
	for (int l = 0; l < g.size(); l++)
	{
		for (int n = 0; n < g[l].size(); n++)
		{
			for (int s = 0; s < g[l][n].size(); s++)
			{
				if (random_range(0, 1) < mut_prob)
				{
					g[l][n][s] = tanh(atanh(g[l][n][s]) + random_range(-2, 2));
				}
			}
		}
	}

	return g;
}

/*

CODE FOR THE NETWORK CLASS

*/

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
		vector2d synapses_layer_tmp;
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

void Network::set_genetics(vector3d s)
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

vector3d Network::get_genetics()
{
	return Network::synapses;
}

/*

Optimization

*/

void Network::gradient_descent(vector2d inp, vector2d out, int rep)
{
	float best_result = calc_error(inp, out, *this);
	Network best = *this;
	for (int r = 0; r < rep; r++)
	{
		for (int i = 0; i < inp.size(); i++)
		{
			vector<float> result = Network::get_result(inp[i]); //Solution for the input i

			vector2d derivative = Network::neurons;
			for (int l = 0; l < derivative.size(); l++)
			{
				for (int n = 0; n < derivative[l].size(); n++)
				{
					derivative[l][n] = 0;
				}
			}

			for (int l = Network::neurons.size() - 1; l >= 0; l--)
			{
				// l     == current neuroal layer
				// l - 1 == current synapses layer
				// l + 1 == next neuronal layer

				if (l == Network::synapses.size()) //If it is the last layer
				{
					for (int n = 0; n < Network::neurons[l].size(); n++) //Compute the error for every output neuron
					{
						float val = 0;
						val = out[i][n] - result[n];
						val *= sigmoid_derivative(result[n]);
						derivative[l][n] = val;
					}
				}
				else
				{
					for (int n = 0; n < Network::neurons[l].size(); n++)
					{
						int t = 0;
						if (l != Network::synapses.size() - 1)
						{
							t = 1;
						}

						for (int s = 0; s < Network::neurons[l + 1].size() - t; s++)
						{
							if (derivative[l][n] == 0)
							{
								derivative[l][n] = derivative[l + 1][s] * Network::synapses[l][n][s] * sigmoid_derivative(Network::neurons[l][n]);
							}
							else
							{
								derivative[l][n] += derivative[l + 1][s] * Network::synapses[l][n][s] * sigmoid_derivative(Network::neurons[l][n]);
							}
						}
						derivative[l][n] /= Network::neurons[l + 1].size();
					}
				}
			}

			//cout << endl;
			for (int l = 0; l < Network::synapses.size(); l++)
			{
				for (int n = 0; n < Network::synapses[l].size(); n++)
				{
					int t = 0;
					if (l != Network::synapses.size() - 1)
					{
						t = 0;
					}

					for (int s = 0; s < Network::synapses[l][n].size() - t; s++)
					{
						Network::synapses[l][n][s] += derivative[l + 1][s] * Network::neurons[l][n];
					}
				}
			}
		}

		if (best_result > calc_error(inp, out, *this))
		{
			best_result = calc_error(inp, out, *this);
			best = *this;
		}

		//Loadbar but in the terminal
		if (r % (rep / 100) == 0)
		{
			cout << "Training, " << r * 100 / rep << "\% completed." << endl;
		}
	}

	//*this = best; //This is optional, it selects only the best network.
}

/*

File management

*/

void save_genetics(string path, Network n)
{
	ofstream file;
	file.open(path);

	vector3d synapses = n.get_genetics();
	vector<int> layers = n.get_layer_blueprint();
	int layer_count = layers.size();

	file << layers.size();

	for (int l = 0; l < layer_count; l++)
	{
		file << "\r\n" << layers[l];
	}

	string out;

	for (int l = 0; l < layer_count - 1; l++)
	{
		for (int n = 0; n < layers[l]; n++)
		{
			int t = 0;
			if (l != synapses.size() - 1)
			{
				t = 1;
			}

			for (int s = 0; s < layers[l + 1] - t; s++)
			{
				if (abs(synapses[l][n][s]) < 0.00001)
				{
					synapses[l][n][s] = 0;
				}

				out += "\r\n" + to_string(synapses[l][n][s]);
			}
		}
	}
	file << out;

	file.close();
}

Network load_genetics(string path)
{
	ifstream file;
	file.open(path);

	string buff;

	getline(file, buff);
	int network_size = stoi(buff);

	vector<int> layers;
	for (int l = 0; l < network_size; l++)
	{
		getline(file, buff);
		int count = stoi(buff);

		if (l != network_size - 1)
		{
			count--;
		}

		layers.push_back(count);
	}

	vector<float> nsynapses;
	vector2d lsynapses;
	vector3d synapses;

	int l = 0;
	int n = 0;
	int s = 0;

	while (!file.eof())
	{
		getline(file, buff);
		nsynapses.push_back(stod(buff));

		s++;

		if (s == layers[l + 1])
		{
			n++;
			s = 0;
			lsynapses.push_back(nsynapses);
			nsynapses.clear();
		}

		if (n == layers[l] + 1)
		{
			s = 0;
			n = 0;
			l++;
			synapses.push_back(lsynapses);
			lsynapses.clear();
		}

		if (l == layers.size() - 1)
		{
			break;
		}
	}

	Network net = Network(layers);
	net.set_genetics(synapses);

	file.close();
	return net;
}