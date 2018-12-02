#include "StringUtils.h"

#include <vector>
#include <string>

using namespace std;

vector<string> break_string(string inp, char c) {
    vector<string> return_data;
    string buff = "";
    for (int i = 0; i < inp.size(); i++) {
        if (inp[i] == c && buff != "") {
            return_data.push_back(buff);
            buff = "";
            continue;
        }
        if (i == inp.size() - 1 && inp[i] != c) {
            buff += inp[i];
            return_data.push_back(buff);
            continue;
        }

        buff += inp[i];
    }
    return return_data;
}