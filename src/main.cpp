#include <ilcplex/ilocplex.h>

#include <iostream>
#include <vector>
#include <memory>

#include "edge.h"
#include "data/config_data.h"
#include "data/graph_data.h"
#include "data/mip_data.h"
#include "encoder/encoder.h"
#include "encoder/all_diff_encoder.h"
#include "encoder/has_hole_encoder.h"
#include "encoder/no_hole_encoder.h"
#include "verifier/verifier.h"
#include "verifier/all_diff_verifier.h"
#include "verifier/has_hole_verifier.h"
#include "verifier/no_hole_verifier.h"

std::unique_ptr<Encoder> get_encoder(VerticesMode vertices_mode)
{
    switch (vertices_mode)
    {
    case VerticesMode::no_hole:
        return std::make_unique<NoHoleEncoder>();

    case VerticesMode::has_hole:
        return std::make_unique<HasHoleEncoder>();

    case VerticesMode::all_diff:
        return std::make_unique<AllDiffEncoder>();

    default:
        exit(1);
    }
}

std::unique_ptr<Verifier> get_verifier(VerticesMode vertices_mode)
{
    switch (vertices_mode)
    {
    case VerticesMode::no_hole:
        return std::make_unique<NoHoleVerifier>();

    case VerticesMode::has_hole:
        return std::make_unique<HasHoleVerifier>();

    case VerticesMode::all_diff:
        return std::make_unique<AllDiffVerifier>();

    default:
        exit(1);
    }
}

int main(int argc, char *argv[])
{
    ConfigData config_data(argc, argv);
    GraphData graph_data(config_data);
    MIPData mip_data(config_data, graph_data);

    std::unique_ptr<Encoder> encoder = get_encoder(config_data.vertices_mode);
    IloModel model = encoder->encode_model(config_data, graph_data, mip_data);

    IloCplex cplex(model);
    cplex.setOut(std::cout);
    cplex.setParam(IloCplex::TiLim, config_data.time_limit);

    if (cplex.solve())
    {
        std::vector<int> solution(graph_data.num_vertices + 1);

        for (int v = 1; v <= graph_data.num_vertices; v++)
            solution[v] = static_cast<int>(cplex.getValue(mip_data.label[v]));

        int solution_span = static_cast<int>(cplex.getValue(mip_data.span));

        std::unique_ptr<Verifier> verifier = get_verifier(config_data.vertices_mode);

        if (verifier->verify(config_data, graph_data, solution, solution_span))
        {
            std::cout << "! --------------------------------------------------------\n";
            std::cout << "! Best span = " << solution_span << "\n";
            std::cout << "! Labeling: ";
            for (int v = 1; v <= graph_data.num_vertices; v++)
                std::cout << solution[v] << " ";
            std::cout << "\n";
            std::cout << "! --------------------------------------------------------\n";
        }
    }
    else
    {
        std::cout << "! --------------------------------------------------------\n";
        std::cout << "! No feasible solution\n";
        std::cout << "! --------------------------------------------------------\n";
    }

    mip_data.env.end();

    return 0;
}