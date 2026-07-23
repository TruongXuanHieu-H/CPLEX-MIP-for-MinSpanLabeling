#ifndef MIP_DATA_H
#define MIP_DATA_H

#include <ilcplex/ilocplex.h>
#include <vector>

#include "config_data.h"
#include "graph_data.h"

class MIPData
{
public:
    IloEnv env;
    IloModel model;

    /* label[i] = j + 1 is equivalent to assignment[i][j] = true */
    std::vector<IloIntVar> label;

    /* assignment[i][j] = true is equivalent to label[i] = j + 1 */
    std::vector<std::vector<IloBoolVar>> assignment;

    IloIntVar span;

    MIPData(const ConfigData &config_data, const GraphData &graph_data) : env(), model(env)
    {
        init_label(config_data, graph_data);
        init_assignment(config_data, graph_data);
        init_span(config_data, graph_data);
    }

    ~MIPData()
    {
        env.end();
    }

private:
    void init_label(const ConfigData &config_data, const GraphData &graph_data)
    {
        label.resize(graph_data.num_vertices);
        for (int i = 0; i < graph_data.num_vertices; i++)
        {
            label[i] = IloIntVar(env, 1, config_data.upper_bound);
        }
    }

    void init_assignment(const ConfigData &config_data, const GraphData &graph_data)
    {
        assignment.resize(graph_data.num_vertices);
        for (int i = 0; i < graph_data.num_vertices; i++)
        {
            assignment[i].resize(config_data.upper_bound);
            for (int j = 0; j < config_data.upper_bound; j++)
            {
                assignment[i][j] = IloBoolVar(env);
            }
        }
    }

    void init_span(const ConfigData &config_data, const GraphData &graph_data)
    {
        span = IloIntVar(env, config_data.lower_bound, config_data.upper_bound);
    }
};

#endif