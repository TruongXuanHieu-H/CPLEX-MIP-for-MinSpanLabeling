#ifndef ENCODER_H
#define ENCODER_H

#include <ilcplex/ilocplex.h>

#include "../data/graph_data.h"
#include "../data/mip_data.h"

class Encoder
{
public:
    virtual ~Encoder() = default;

    virtual IloModel encode_model(ConfigData &config_data, GraphData &graph_data, MIPData &mip_data) = 0;

protected:
    void encode_symmetry_breaking(ConfigData &config_data, GraphData &graph_data, MIPData &mip_data)
    {
        std::vector<int> degree(graph_data.num_vertices, 0);
        for (const auto &edge : graph_data.edges)
        {
            degree[edge.u]++;
            degree[edge.v]++;
        }

        int max_degree_vertex = 0; // First vertex
        for (int i = 1; i < graph_data.num_vertices; i++)
            if (degree[i] > degree[max_degree_vertex])
                max_degree_vertex = i;

        mip_data.model.add(mip_data.label[max_degree_vertex] <= (config_data.upper_bound + 1) / 2);
    }

    void encode_target_value(ConfigData &config_data, GraphData &graph_data, MIPData &mip_data)
    {
        for (const auto &edge : graph_data.edges)
        {
            IloExpr diff(mip_data.env);
            diff = mip_data.label[edge.u] - mip_data.label[edge.v];

            IloIntVar absDiff(mip_data.env, 0, config_data.upper_bound);
            mip_data.model.add(absDiff == IloAbs(diff));

            switch (config_data.target_value_mode)
            {
            case TargetValueMode::abp:
            {
                mip_data.model.add(absDiff >= config_data.target_value);
                break;
            }
            case TargetValueMode::cabp:
            {
                mip_data.model.add(absDiff >= config_data.target_value);
                mip_data.model.add(mip_data.span - absDiff >= config_data.target_value);
                break;
            }
            default:
                break;
            }

            diff.end();
        }
    }

    void encode_span(ConfigData &config_data, GraphData &graph_data, MIPData &mip_data)
    {
        IloExpr is_label_one_used(mip_data.env);
        for (int v = 0; v < graph_data.num_vertices; v++)
            is_label_one_used += mip_data.assignment[v][0];
        mip_data.model.add(is_label_one_used >= 1);
        is_label_one_used.end();

        IloBoolVarArray is_max(mip_data.env, graph_data.num_vertices);
        IloExpr sum(mip_data.env);
        for (int v = 0; v < graph_data.num_vertices; v++)
        {
            sum += is_max[v];
            mip_data.model.add(IloIfThen(mip_data.env, is_max[v] == 1, mip_data.label[v] == mip_data.span));
            mip_data.model.add(IloIfThen(mip_data.env, is_max[v] == 0, mip_data.label[v] <= mip_data.span - 1));
        }

        mip_data.model.add(sum >= 1);
        sum.end();
    }

    void link_label_and_assignment(ConfigData &config_data, GraphData &graph_data, MIPData &mip_data)
    {
        for (int i = 0; i < graph_data.num_vertices; i++)
        {
            IloExpr label_expr(mip_data.env);
            IloExpr assign_expr(mip_data.env);

            for (int j = 0; j < config_data.upper_bound; j++)
            {
                label_expr += (j + 1) * mip_data.assignment[i][j];
                assign_expr += mip_data.assignment[i][j];
            }

            mip_data.model.add(label_expr == mip_data.label[i]);
            mip_data.model.add(assign_expr == 1);

            label_expr.end();
            assign_expr.end();
        }
    }
};

#endif