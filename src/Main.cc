#include <iostream>
#include <vector>
#include <string>
#include <thread>
#include <cmath>
#include <chrono>
#include <fstream>
#include <algorithm>

#include "NeuralC.h"

using namespace std;

int main(int argc, char *argv[])
{
    vector<string> data;
    vector<float> network_input;
    vector<int> layers = {2, 8, 1};
    vector<vector<float>> inp;
    vector<vector<float>> out;

    string name, arg[argc], line;
    string data_file;
    string buff;
    char command;

    int iterations = 100000;
    int threads = 4;

    Network N = Network({1, 1});

    for (int i = 0; i < argc; i++)
            arg[i] = argv[i];

    for (int i = 1; i < argc; i++)
    {
        if (arg[i] == "--new" || arg[i] == "-N")
            command = 'N';

        if (arg[i] == "--train" || arg[i] == "-T")
            command = 'T';

        if (arg[i] == "--input" || arg[i] == "-I")
        {
            if (argc <= i + 1)
                return 1;

            command = 'I';

            vector<string> l = break_string(arg[i + 1], '-');
            for (int c = 0; c < l.size(); c++)
                network_input.push_back(stof(l[c]));

            i++;
        }

        if (arg[i] == "--name" || arg[i] == "-n")
        {
            if (argc <= i + 1)
                return 1;

            name = arg[i + 1];

            i++;
        }

        if (arg[i] == "--data" || arg[i] == "-d")
        {
            if (argc <= i + 1)
                return 1;

            data_file = arg[i + 1];
            
            i++;
        }

        if (arg[i] == "--layers" || arg[i] == "-l")
        {
            if (argc <= i + 1)
                return 1;
            
            layers.clear();

            vector<string> l = break_string(arg[i + 1], '-');
            for (int c = 0; c < l.size(); c++)
                layers.push_back(stoi(l[c]));
        }

        if (arg[i] == "--threads" || arg[i] == "-t")
        {
            if (argc <= i + 1)
                return 1;

            threads = stoi(arg[i + 1]);
            i++;
        }

        if (arg[i] == "--iterations" || arg[i] == "-i")
        {
            if (argc <= i + 1)
                return 1;

            iterations = stoi(arg[i + 1]);
            i++;
        }
    }

    // Command processing

    switch (command)
    {
        case 'N':
            N = Network(layers);
            save_genetics(name, N);
            break;

        case 'T':
        {
            N = load_genetics(name);

            ifstream file(data_file);
            while (!file.eof())
            {
                getline(file, buff);
                vector<string> file_line = break_string(buff, ' ');
                vector<float> inp_tmp, out_tmp;

                for (int i = 0; i < file_line.size(); i++)
                {
                    if (i < N.get_layer_blueprint()[0] - 1)
                        inp_tmp.push_back(stof(file_line[i]));
                    else
                        out_tmp.push_back(stof(file_line[i]));
                }

                inp.push_back(inp_tmp);
                out.push_back(out_tmp);
            }
            
            gradient_descent(&N, inp, out, iterations, threads);
            save_genetics(name, N);
            break;
        }

        case 'I':
        {
            N = load_genetics(name);  
            vector<float> outp = N.get_result(network_input);

            for (int i = 0; i < outp.size(); i++)
            {
                cout << outp[i];
                if (i != outp.size() - 1)
                    cout << " ";
            }
            cout << endl;

            break;
        }
        
        default:
            break;
    }

    return 0;
}
