#ifndef ALL_DIFF_ENCODER_H
#define ALL_DIFF_ENCODER_H

#include "encoder.h"

class AllDiffEncoder : public Encoder
{
public:
    IloModel encode_model(ConfigData &config_data, GraphData &graph_data, MIPData &mip_data) override;

private:
    void encode_all_diff(ConfigData &config_data, GraphData &graph_data, MIPData &mip_data);
};

#endif