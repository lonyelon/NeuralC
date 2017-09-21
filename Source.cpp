#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <fstream>
#include "Network.h"
 
using namespace std;
 
int main(int argc, char *argv[])
{
    Network n = Network({ 2, 4, 4, 3 });
    vector<vector<double>> inp
    {
        { 0, 0 },
        { 0, 1 },
        { 1, 0 },
        { 1, 1 },
    };
 
    vector<vector<double>> out = 
    {
        { 0, 0, 1 },      
        { 0, 1, 0 },    
        { 0, 1, 0 },  
        { 1, 0, 0 },  
    };
 
 
    double c = 0.0000001;
    while(true)
    {
        string s;
        getline(cin, s);
 
        if (s == "train")
        {
            n.gradient_descent(inp, out, 100000);
            cout << calc_error(inp, out, n) << endl;
            cout << "done" << endl;
        }
 
        if (s == "input")
        {
            vector<double> d;
            vector<double> r;
 
            for (int i = 0; i < n.get_layer_blueprint()[0]-1; i++)
            {
                getline(cin, s);
                d.push_back(stod(s));
            }
 
            cout << endl << "Output:" << endl;
            r = n.get_result(d);
            //r = n.get_layer_values(1);
            for(int i = 0; i < r.size(); i++)
            {
                cout << "(" << round(r[i]) << ") " << r[i] << endl;
            }
        }
 
        if (s == "genetics")
        {
            auto g = n.get_genetics();
            for (int l = 0; l < g.size(); l++)
            {
                for (int n = 0; n < g[l].size(); n++)
                {
                    for (int s = 0; s < g[l][n].size(); s++)
                    {
                        cout << "[" << l << "," << n << "," << s << "]: " << g[l][n][s] << endl;
                    }
                }
            }
        }
 
        if (s == "change")
        {
            getline(cin, s);
            c = stod(s);
        }
    }
 
    return 0;
}
