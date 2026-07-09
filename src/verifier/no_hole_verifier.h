#ifndef NO_HOLE_VERIFIER_H
#define NO_HOLE_VERIFIER_H

#include "verifier.h"

class NoHoleVerifier : public Verifier
{
public:
    bool verify(ConfigData &config_data, GraphData &graph_data, std::vector<int> &solution, int solution_span) override;
};

#endif