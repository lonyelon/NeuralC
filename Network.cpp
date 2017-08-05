#include <iostream>
#include <vector>
#include <time.h>
#include "Neuron.h"

using namespace std;

class Network
{
private:
    vector<vector<Neuron>> Layer;
    void connect()
    {
        for (int l = Layer.size() -2; l >= 0; l--)
        {
            for (int n = 0; n < Layer[l].size(); n++)
            {
                vector<double> dob;
                vector<Neuron*> tmp_pointer;
                for (int i = 0; i < Layer[l].size(); i++)
                {
                    dob.push_back(1);
                    tmp_pointer.push_back(&Layer[l][n]);
                }
                int neurontype = Layer[l][n].get_type();
                Layer[l][n] = Neuron(neurontype, tmp_pointer, dob);
            }
        }
    }
public:
    Network(int inputs, int outputs)
    {
        vector<Neuron> inp;
        vector<Neuron> out;

        for (int i = 0; i < outputs; i++)
        {
            out.push_back(Neuron(0, vector<Neuron*>(), vector<double>()));
        }

        for (int i = 0; i < inputs; i++) 
        {
            vector<Neuron*> tmp;
            vector<double> dtmp;
            for (int k = 0; k < out.size(); k++) 
            {
                tmp.push_back(&out[k]);
                dtmp.push_back(1);
            }
            inp.push_back(Neuron(0, tmp, dtmp));
        }

        Layer.push_back(vector<Neuron>());
        Layer.push_back(vector<Neuron>());
    }

    void add_layer(vector<Neuron> l) 
    {
        Layer.push_back(l);
    }

    void remove_layer(int n) 
    {
        if (n != 0 && n != Layer.size())
        {
            Layer.erase(Layer.begin()+n);
        }
    }
};