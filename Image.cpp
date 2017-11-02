#include "Image.h"
#include <cmath>

using namespace std;

struct pixel
{
    int r;
    int g;
    int b;
};

struct image
{
    pixel p[1000];
};

image image_to_grey(image inp)
{
    for (int i = 0; i < 1000; i++)
    {
        int med = inp.p[i].r;
        med += inp.p[i].g;
        med += inp.p[i].b;
        med = round(med/3);
        inp.p[i].r = med;
        inp.p[i].g = med;
        inp.p[i].b = med;
    }
    return inp;
}

vector2d image_to_training_data(image inp, int inp_size)
{
    vector2d out;
    for (int i = 0; i < 1000; i++)
    {
        int k;
        vector<float> out_tmp;
        for (k = 0; k < inp_size; k++)
            out_tmp.push_back(inp.p[i].r/255);
        i += k;
        out.push_back(out_tmp);
    }
    return out;
}