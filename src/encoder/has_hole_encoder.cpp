#include "has_hole_encoder.h"

void HasHoleEncoder::encode_model(ConfigData &config_data, GraphData &graph_data, MIPData &mip_data)
{
    encode_symmetry_breaking(config_data, graph_data, mip_data);
    encode_target_value(config_data, graph_data, mip_data);
    encode_span(config_data, graph_data, mip_data);

    mip_data.model.add(IloMinimize(mip_data.env, mip_data.span));
}