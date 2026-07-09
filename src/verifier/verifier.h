#ifndef VERIFIER_H
#define VERIFIER_H

#include <vector>

#include "../data/config_data.h"
#include "../data/graph_data.h"

class Verifier
{
public:
    virtual ~Verifier() = default;

    virtual bool verify(ConfigData &config_data, GraphData &graph_data, std::vector<int> &solution, int solution_span) = 0;
};

#endif