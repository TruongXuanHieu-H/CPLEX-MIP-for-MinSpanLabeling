#include "has_hole_verifier.h"

#include <iostream>

bool HasHoleVerifier::verify(ConfigData &config_data, GraphData &graph_data, std::vector<int> &solution, int solution_span)
{
    if (!verify_target_value(config_data, graph_data, solution, solution_span))
        return false;

    if (!verify_span(graph_data, solution, solution_span))
        return false;

    return true;
}