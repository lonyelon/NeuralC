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
float calc_error(vector<vector<float>> inp, vector<vector<float>> out, Network n)
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
