#ifndef HAS_HOLE_ENCODER_H
#define HAS_HOLE_ENCODER_H

#include "encoder.h"

class HasHoleEncoder : public Encoder
{
public:
    IloModel encode_model(ConfigData &config_data, GraphData &graph_data, MIPData &mip_data) override;
};

#endif