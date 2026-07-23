#include "all_diff_encoder.h"

IloModel AllDiffEncoder::encode_model(ConfigData &config_data, GraphData &graph_data, MIPData &mip_data)
{
    encode_symmetry_breaking(config_data, graph_data, mip_data);
    encode_target_value(config_data, graph_data, mip_data);
    encode_span(config_data, graph_data, mip_data);
    link_label_and_assignment(config_data, graph_data, mip_data);
    encode_all_diff(config_data, graph_data, mip_data);

    mip_data.model.add(IloMinimize(mip_data.env, mip_data.span));

    return mip_data.model;
}

void AllDiffEncoder::encode_all_diff(ConfigData &config_data, GraphData &graph_data, MIPData &mip_data)
{
    for (int j = 0; j < config_data.upper_bound; j++)
    {
        IloExpr expr(mip_data.env);

        for (int i = 0; i < graph_data.num_vertices; i++)
            expr += mip_data.assignment[i][j];

        mip_data.model.add(IloConstraint(expr <= 1));
        expr.end();
    }
}