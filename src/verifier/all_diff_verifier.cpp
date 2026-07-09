#include "all_diff_verifier.h"

#include <iostream>

bool AllDiffVerifier::verify(ConfigData &config_data, GraphData &graph_data, std::vector<int> &solution, int solution_span)
{
    for (const auto &e : graph_data.edges)
    {
        int diff = std::abs(solution[e.u] - solution[e.v]);
        if (diff < config_data.target_value)
        {
            std::cout << "! VERIFY FAILED: edge (" << e.u << ", " << e.v << ") has distance " << diff << " < " << config_data.target_value << "\n";
            return false;
        }
    }

    int max_label = 0;
    for (int v = 1; v <= graph_data.num_vertices; v++)
        max_label = std::max(max_label, solution[v]);

    if (max_label != solution_span)
    {
        std::cout << "! VERIFY FAILED: span = " << solution_span << ", but max label = " << max_label << "\n";
        return false;
    }

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