#include "GradientDescent.h"

#include <vector>
#include <iostream>
#include <thread>

#include "Network.h"
#include "NeuralMath.h"

using namespace std;

void _gd_hidden(vector<vector<vector<float>>>* synapses, vector<int> blue, vector<vector<float>> inp, vector<vector<float>> out, int rep)
{
    Network n = Network(blue);    
	for (int r = 0; r < rep; r++)
	{
		for (int i = 0; i < inp.size(); i++)
		{
            n.set_genetics(*synapses);
            vector<float> result = n.get_result(inp[i]); //Solution for the input i
            
            vector<vector<float>> derivative = n.get_current_state();
            vector<vector<float>> neurons = n.get_current_state();
			for (int l = 0; l < derivative.size(); l++)
			{
				for (int n = 0; n < derivative[l].size(); n++)
				{
					derivative[l][n] = 0;
				}
			}

            
			for (int l = neurons.size() - 1; l >= 0; l--)
			{
                // l     == current neuroal layer
				// l - 1 == current synapses layer
				// l + 1 == next neuronal layer
                
				if (l == synapses->size()) //If it is the last layer
				{
                    for (int n = 0; n < neurons[l].size(); n++) //Compute the error for every output neuron
					{
                        float val = 0;
						val = out[i][n] - result[n];
						val *= sigmoid_derivative(result[n]);
						derivative[l][n] = val;
					}
				}
				else
				{
                    for (int n = 0; n < neurons[l].size(); n++)
					{
                        int t = 0;
						if (l != synapses->size() - 1)
						{
                            t = 1;
						}
                        
						for (int s = 0; s < neurons[l + 1].size() - t; s++)
						{
                            if (derivative[l][n] == 0)
							{
                                derivative[l][n] = derivative[l + 1][s] * (*synapses)[l][n][s] * sigmoid_derivative(neurons[l][n]);
							}
							else
							{
                                derivative[l][n] += derivative[l + 1][s] * (*synapses)[l][n][s] * sigmoid_derivative(neurons[l][n]);
                            }
						}
						derivative[l][n] /= neurons[l + 1].size();
					}
				}
			}
            
			//cout << endl;
			for (int l = 0; l < synapses->size(); l++)
			{
                for (int n = 0; n < (*synapses)[l].size(); n++)
				{
                    int t = 0;
					if (l != synapses->size() - 1)
					{
                        t = 0;
					}
                    
					for (int s = 0; s < (*synapses)[l][n].size() - t; s++)
					{
						(*synapses)[l][n][s] += derivative[l + 1][s] * neurons[l][n];
					}
				}
            }
		}
    }
}

void gradient_descent(Network *N, vector<vector<float>> inp, vector<vector<float>> out, int it, int cores)
{
	vector<vector<vector<float>>> synapses = N->get_genetics();
	vector<int> b = N->get_layer_blueprint();
	thread *t = new thread[cores];

	for (int i = 0; i < b.size()-1; i++)
		b[i]--;

	for (int  i = 0; i < cores; i++)
		t[i] = thread(_gd_hidden, &synapses, b, inp, out, it/cores);

	for (int  i = 0; i < cores; i++)
		t[i].join();
		
	N->set_genetics(synapses);
}