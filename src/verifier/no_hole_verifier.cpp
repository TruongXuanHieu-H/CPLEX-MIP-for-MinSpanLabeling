#include "no_hole_verifier.h"

#include <iostream>

bool NoHoleVerifier::verify(ConfigData &config_data, GraphData &graph_data, std::vector<int> &solution, int solution_span)
{
    if (!verify_target_value(config_data, graph_data, solution, solution_span))
        return false;

    if (!verify_span(graph_data, solution, solution_span))
        return false;

    std::vector<bool> used(solution_span, false);
    for (int v = 0; v < graph_data.num_vertices; v++)
        used[solution[v] - 1] = true;
    for (int label = 0; label < solution_span; label++)
    {
        if (!used[label])
        {
            std::cout << "! VERIFY FAILED: label " << label + 1 << " is not used\n";
            return false;
        }
    }

    return true;
}