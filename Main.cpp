#include <iostream>
#include <vector>
#include <string>
#include <thread>
#include <cmath>
#include <ctime>
#include <fstream>
#include <algorithm>
#include "NeuralCore/Network.h"
#include "NeuralCore/Image.h"
#include "NeuralCore/Save.h"
#include "NeuralCore/Optimization.h"
 
#define NO_NAME "Unnamed_Network"

using namespace std;
 
vector<string> break_string(string inp)
{
    vector<string> return_data;
    string buff;
    for (int i = 0; i < inp.size(); i++)
    {
        if (inp[i] == ' ' && buff != "")
        {
            return_data.push_back(buff);
            buff = "";
        }
        else if (i == inp.size() - 1 && inp[i] != ' ')
        {
            buff += inp[i];
            return_data.push_back(buff);
        }
        else
        {
            buff += inp[i];
        }
    }
    return return_data;
}

int main(int argc, char *argv[])
{
    Network n = Network({ 2, 4, 1 });
    vector<vector<float>> inp
    {
        { 0, 0 },
        { 0, 1 },
        { 1, 1 },
    };
 
    vector<vector<float>> out = 
    {
        { 0 },         
        { 1 },  
        { 0 },  
    };
 
    string name = NO_NAME;
    float c = 0.0000001;
    while(true)
    {
        cout << name << ">> ";
        string buff;
        getline(cin, buff);
        vector<string> input = break_string(buff);
        int values = input.size();
        if (values > 0)
        {
            if (input[0] == "help")
            {
                cout << "List of commands:" << endl;
                cout << "train, input, genetics, change, save, new network, set name" << endl; 
            }

            if (input[0] == "train")
            {
                auto t = time(NULL);
                vector<int> b = { 2, 4, 1};
                vector<vector<vector<float>>> s = n.get_genetics();
                thread t0(gradient_descent, &s, b, inp, out, 1000000);
                
                t0.join();

                n.set_genetics(s);
                cout << calc_error(inp, out, n) << endl;
                cout << "done" << endl;
                cout << time(NULL) - t << endl;                
            }
    
            if (input[0] == "input")
            {
                vector<float> d;
                vector<float> r;
    
                for (int i = 0; i < n.get_layer_blueprint()[0]-1; i++)
                {
                    cout << "Input " << i << ": ";
                    getline(cin, buff);
                    d.push_back(stod(buff));
                }
    
                cout << endl << "Output:" << endl;
                r = n.get_result(d);
                //r = n.get_layer_values(1);
                for(int i = 0; i < r.size(); i++)
                {
                    cout << "(" << round(r[i]) << ") " << r[i] << endl;
                }
            }
    
            if (buff == "genetics")
            {
                auto g = n.get_genetics();
                for (int l = 0; l < g.size(); l++)
                {
                    for (int n = 0; n < g[l].size(); n++)
                    {
                        for (int buff = 0; buff < g[l][n].size(); buff++)
                        {
                            cout << "[" << l << "," << n << "," << buff << "]: " << g[l][n][buff] << endl;
                        }
                    }
                }
            }
    
            if (buff == "change")
            {
                getline(cin, buff);
                c = stod(buff);
            }

            if (input[0] == "save")
            {
                save_genetics(name + ".ndf", n);
            }

            if (values > 1)
            {
                if (input[0] == "new")
                {
                    if (input[1] == "network")
                    {
                        int la;
                        vector<int> layers;
                        cout << "Ammount of layers: ";
                        getline(cin, buff);
                        la = stoi(buff);
                        for (int i = 0; i < la; i++)                        
                        {
                            cout << "Ammount of neurons in layer " << i << ": ";
                            getline(cin, buff);
                            layers.push_back(stoi(buff));
                        }
                        reverse(layers.begin(), layers.end());
                        n = Network(layers);
                        name = NO_NAME;
                    }
                }

                if (input[0] == "set")
                {
                    if (input[1] == "name")
                    {
                        cout << "New name for the network: ";
                        getline(cin, buff);
                        name = buff;
                    }
                }
            }
        }
    }
 
    return 0;
}
