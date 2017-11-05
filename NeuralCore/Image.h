#ifndef _IMAGE_H_
#define _IMAGE_H_

#include <vector>

struct image;

std::vector<std::vector<float>> image_to_training_data(image inp, int inp_size);

#endif