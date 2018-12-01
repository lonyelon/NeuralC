#include "Mutation.h"

#include "NeuralC.h"

/*
    Mutates a neural net given as n.
*/

Network simpleMutate(Network n, double chance, double factor)
{
    auto s = n.get_genetics();
    for (int i = 0; i < s.size(); i++)
        for (int j = 0; j < s[i].size(); j++)
            for (int k = 0; k < s[i][j].size(); k++)
                if (random_range(0, 1) < chance)
                    s[i][j][k] *= factor;
    Network N = Network(n.get_layer_blueprint());
    return N;
}