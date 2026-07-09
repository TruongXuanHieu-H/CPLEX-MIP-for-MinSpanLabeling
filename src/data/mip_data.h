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

    std::vector<IloNumVar> label;
    bool is_label_initialized = false;

    std::vector<std::vector<IloBoolVar>> assignment;
    bool is_assignment_initialized = false;

    IloNumVar span;
    bool is_span_initialized = false;

    MIPData(ConfigData &config_data, GraphData &graph_data) : env(), model(env) {}

    void init_label(ConfigData &config_data, GraphData &graph_data)
    {
        if (!is_label_initialized)
        {
            label.resize(graph_data.num_vertices + 1);
            for (int i = 1; i <= graph_data.num_vertices; i++)
            {
                label[i] = IloNumVar(env, 1, config_data.upper_bound, ILOINT);
            }
            is_label_initialized = true;
        }
    }

    void init_assignment(ConfigData &config_data, GraphData &graph_data)
    {
        if (!is_assignment_initialized)
        {
            assignment.resize(graph_data.num_vertices + 1);
            for (int i = 1; i <= graph_data.num_vertices; i++)
            {
                assignment[i].resize(config_data.upper_bound + 1);
                for (int j = 1; j <= config_data.upper_bound; j++)
                {
                    assignment[i][j] = IloBoolVar(env);
                }
            }
            is_assignment_initialized = true;
        }
    }

    void init_span(ConfigData &config_data, GraphData &graph_data)
    {
        if (!is_span_initialized)
        {
            span = IloNumVar(env, config_data.lower_bound, config_data.upper_bound, ILOINT);
            is_span_initialized = true;
        }
    }

    ~MIPData()
    {
        env.end();
    }
};

#endif