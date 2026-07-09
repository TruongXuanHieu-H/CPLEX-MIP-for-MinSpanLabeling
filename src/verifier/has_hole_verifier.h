#ifndef HAS_HOLE_VERIFIER_H
#define HAS_HOLE_VERIFIER_H

#include "verifier.h"

class HasHoleVerifier : public Verifier
{
public:
    bool verify(ConfigData &config_data, GraphData &graph_data, std::vector<int> &solution, int solution_span) override;
};

#endif