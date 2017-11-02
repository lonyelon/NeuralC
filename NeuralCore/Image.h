#ifndef _IMAGE_H_
#define _IMAGE_H_

#include <vector>
#define vector2d std::vector<std::vector<float>>

struct image;

vector2d image_to_training_data(image inp, int inp_size);

#endif