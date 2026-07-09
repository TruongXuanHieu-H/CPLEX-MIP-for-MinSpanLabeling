#include "no_hole_encoder.h"

IloModel NoHoleEncoder::encode_model(ConfigData &config_data, GraphData &graph_data, MIPData &mip_data)
{
    encode_symmetry_breaking(config_data, graph_data, mip_data);

    encode_target_value(config_data, graph_data, mip_data);

    encode_span(config_data, graph_data, mip_data);

    link_label_and_assignment(config_data, graph_data, mip_data);
    encode_no_hole(config_data, graph_data, mip_data);

    mip_data.model.add(IloMinimize(mip_data.env, mip_data.span));

    return mip_data.model;
}

void NoHoleEncoder::encode_no_hole(ConfigData &config_data, GraphData &graph_data, MIPData &mip_data)
{
    for (int j = 1; j <= config_data.upper_bound; j++)
    {
        IloExpr assign_expr = IloExpr(mip_data.env);

        for (int i = 1; i <= graph_data.num_vertices; i++)
            assign_expr += mip_data.assignment[i][j];

        mip_data.model.add(mip_data.span - j + 1 <= config_data.upper_bound * assign_expr);
        assign_expr.end();
    }
}