#ifndef ENCODER_H
#define ENCODER_H

#include <ilcplex/ilocplex.h>

#include "../data/graph_data.h"
#include "../data/mip_data.h"

class Encoder
{
public:
    virtual ~Encoder() = default;

    virtual void encode_model(ConfigData &config_data, GraphData &graph_data, MIPData &mip_data) = 0;

protected:
    void encode_symmetry_breaking(ConfigData &config_data, GraphData &graph_data, MIPData &mip_data)
    {
        mip_data.init_label(config_data, graph_data);

        std::vector<int> degree(graph_data.num_vertices + 1, 0);
        for (const auto &edge : graph_data.edges)
        {
            degree[edge.u]++;
            degree[edge.v]++;
        }

        int max_degree_vertex = 1;
        for (int i = 2; i <= graph_data.num_vertices; i++)
            if (degree[i] > degree[max_degree_vertex])
                max_degree_vertex = i;

        mip_data.model.add(mip_data.label[max_degree_vertex] <= (config_data.upper_bound + 1) / 2);
    }

    void encode_target_value(ConfigData &config_data, GraphData &graph_data, MIPData &mip_data)
    {
        mip_data.init_label(config_data, graph_data);
        mip_data.init_span(config_data, graph_data);

        switch (config_data.target_value_type)
        {
        case TargetValueMode::abp:
        {
            for (const auto &edge : graph_data.edges)
            {
                IloNumVar diff = IloNumVar(mip_data.env, -config_data.upper_bound, config_data.upper_bound, ILOINT);
                mip_data.model.add(diff == mip_data.label[edge.u] - mip_data.label[edge.v]);

                IloBoolVar is_diff_positive = IloBoolVar(mip_data.env);
                mip_data.model.add(IloIfThen(mip_data.env, is_diff_positive == 1, diff >= config_data.target_value));
                mip_data.model.add(IloIfThen(mip_data.env, is_diff_positive == 0, diff <= -config_data.target_value));
            }
            break;
        }
        case TargetValueMode::cabp:
        {
            for (const auto &edge : graph_data.edges)
            {
                IloNumVar diff = IloNumVar(mip_data.env, -config_data.upper_bound, config_data.upper_bound, ILOINT);
                mip_data.model.add(diff == mip_data.label[edge.u] - mip_data.label[edge.v]);

                IloNumVar absDiff(mip_data.env, 0, config_data.upper_bound, ILOINT);
                IloBoolVar isPositive(mip_data.env);

                mip_data.model.add(IloIfThen(mip_data.env, isPositive == 1, diff >= 0));
                mip_data.model.add(IloIfThen(mip_data.env, isPositive == 1, absDiff == diff));

                mip_data.model.add(IloIfThen(mip_data.env, isPositive == 0, diff <= 0));
                mip_data.model.add(IloIfThen(mip_data.env, isPositive == 0, absDiff == -diff));

                mip_data.model.add(absDiff >= config_data.target_value);
                mip_data.model.add(mip_data.span - absDiff >= config_data.target_value);
            }
            break;
        }
        }
    }

    void encode_span(ConfigData &config_data, GraphData &graph_data, MIPData &mip_data)
    {
        mip_data.init_label(config_data, graph_data);
        mip_data.init_span(config_data, graph_data);

        switch (config_data.target_value_type)
        {
        case TargetValueMode::abp:
        {
            for (int i = 1; i <= graph_data.num_vertices; i++)
                mip_data.model.add(mip_data.span >= mip_data.label[i]);
            break;
        }
        case TargetValueMode::cabp:
        {
            IloBoolVarArray is_max(mip_data.env, graph_data.num_vertices + 1);
            IloExpr sum(mip_data.env);

            for (int i = 1; i <= graph_data.num_vertices; i++)
            {
                sum += is_max[i];
                mip_data.model.add(IloIfThen(mip_data.env, is_max[i] == 1, mip_data.label[i] == mip_data.span));
                mip_data.model.add(IloIfThen(mip_data.env, is_max[i] == 0, mip_data.label[i] <= mip_data.span - 1));
            }

            mip_data.model.add(sum >= 1);
            sum.end();
            break;
        }
        default:
            break;
        }
    }

    void link_label_and_assignment(ConfigData &config_data, GraphData &graph_data, MIPData &mip_data)
    {
        mip_data.init_label(config_data, graph_data);
        mip_data.init_assignment(config_data, graph_data);

        for (int i = 1; i <= graph_data.num_vertices; i++)
        {
            IloExpr label_expr = IloExpr(mip_data.env);
            IloExpr assign_expr = IloExpr(mip_data.env);

            for (int j = 1; j <= config_data.upper_bound; j++)
            {
                label_expr += (j)*mip_data.assignment[i][j];
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