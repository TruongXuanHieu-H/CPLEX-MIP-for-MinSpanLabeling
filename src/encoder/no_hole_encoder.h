#ifndef NO_HOLE_ENCODER_H
#define NO_HOLE_ENCODER_H

#include "encoder.h"

class NoHoleEncoder : public Encoder
{
public:
    IloModel encode_model(ConfigData &config_data, GraphData &graph_data, MIPData &mip_data) override;

private:
    void encode_no_hole(ConfigData &config_data, GraphData &graph_data, MIPData &mip_data);
};

#endif