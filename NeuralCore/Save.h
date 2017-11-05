#ifndef _SAVING_H_
#define _SAVING_H_

#include <string>
#include <fstream>
#include "Network.h"

void save_genetics(std::string file, Network n);
Network load_genetics(std::string path);

#endif