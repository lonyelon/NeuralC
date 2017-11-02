#include "Image.h"
#include <cmath>

using namespace std;

struct image
{
    int r[1024][1024];
    int g[1024][1024];
    int b[1024][1024];
};

vector2d image_to_training_data(image inp)
{
    vector2d out;
    
    for (int y = 0; y < 1024; y += 2)
    {
        vector<float> tmp;
        for (int x = 0; x < 1024; x += 2)
        {
            tmp.push_back(inp.r[x][y]);
            tmp.push_back(inp.r[x+1][y]);
            tmp.push_back(inp.r[x][y+1]);
            tmp.push_back(inp.r[x+1][y+1]);
        }
        out.push_back(tmp);
    }

    return out;
}