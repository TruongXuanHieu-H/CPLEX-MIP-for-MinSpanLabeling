#ifndef ALL_DIFF_VERIFIER_H
#define ALL_DIFF_VERIFIER_H

#include "verifier.h"

class AllDiffVerifier : public Verifier
{
public:
    bool verify(ConfigData &config_data, GraphData &graph_data, std::vector<int> &solution, int solution_span) override;
};

#endif