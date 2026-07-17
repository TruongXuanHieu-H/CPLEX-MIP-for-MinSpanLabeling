#include "has_hole_verifier.h"

#include <iostream>

bool HasHoleVerifier::verify(ConfigData &config_data, GraphData &graph_data, std::vector<int> &solution, int solution_span)
{
    if (!verify_target_value(config_data, graph_data, solution, solution_span))
        return false;

    if (!verify_span(graph_data, solution, solution_span))
        return false;

    int max_label = 0;
    for (int v = 1; v <= graph_data.num_vertices; v++)
        max_label = std::max(max_label, solution[v]);

    if (max_label != solution_span)
    {
        std::cout << "! VERIFY FAILED: span = " << solution_span << ", but max label = " << max_label << "\n";
        return false;
    }

    return true;
}