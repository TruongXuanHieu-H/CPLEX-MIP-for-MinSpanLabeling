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

protected:
    bool verify_target_value(ConfigData &config_data, GraphData &graph_data, std::vector<int> &solution, int solution_span)
    {
        for (const auto &e : graph_data.edges)
        {
            int diff;

            switch (config_data.target_value_mode)
            {
            case TargetValueMode::abp:
            {
                diff = std::abs(solution[e.u] - solution[e.v]);
                break;
            }
            case TargetValueMode::cabp:
            {
                diff = std::min(std::abs(solution[e.u] - solution[e.v]), solution_span - std::abs(solution[e.u] - solution[e.v]));
                break;
            }

            default:
            {
                diff = 0;
                break;
            }
            }

            if (diff < config_data.target_value)
            {
                std::cout << "! VERIFY FAILED: edge (" << e.u << ", " << e.v << ") has distance " << diff << " < " << config_data.target_value << "\n";
                return false;
            }
        }

        return true;
    }

    bool verify_span(GraphData &graph_data, std::vector<int> &solution, int solution_span)
    {
        int min_label = solution[0];
        int max_label = solution[0];

        for (int v = 1; v < graph_data.num_vertices; v++)
        {
            max_label = std::max(max_label, solution[v]);
            min_label = std::min(min_label, solution[v]);
        }

        if (max_label != solution_span)
        {
            std::cout << "! VERIFY FAILED: span = " << solution_span << ", but max label = " << max_label << "\n";
            return false;
        }

        if (min_label != 1)
        {
            std::cout << "! VERIFY FAILED: minimum label = " << min_label << ", while it must be 1.\n";
            return false;
        }
        return true;
    }
};

#endif