#include "all_diff_verifier.h"

#include <iostream>

bool AllDiffVerifier::verify(ConfigData &config_data, GraphData &graph_data, std::vector<int> &solution, int solution_span)
{
    if (!verify_target_value(config_data, graph_data, solution, solution_span))
        return false;

    if (!verify_span(graph_data, solution, solution_span))
        return false;

    for (int i = 1; i <= graph_data.num_vertices; i++)
    {
        for (int j = i + 1; j <= graph_data.num_vertices; j++)
        {
            if (solution[i] == solution[j])
            {
                std::cout << "! VERIFY FAILED: duplicate label " << solution[i] << "\n";
                return false;
            }
        }
    }

    return true;
}