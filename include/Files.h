#ifndef _FILES_H_
#define _FILES_H_

#include <iostream>
#include <vector>
#include <string>

#include "Network.h"

void save_genetics(std::string path, Network n);
Network load_genetics(std::string path);

#endif