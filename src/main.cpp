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
    cplex.setParam(IloCplex::Param::MIP::Display, 2);
    cplex.setParam(IloCplex::Param::TimeLimit, config_data.time_limit);

    if (cplex.solve())
    {
        std::vector<int> solution(graph_data.num_vertices);

        for (int v = 0; v < graph_data.num_vertices; v++)
        {
            solution[v] = static_cast<int>(cplex.getValue(mip_data.label[v]));
        }
        int solution_span = static_cast<int>(cplex.getValue(mip_data.span));

        std::cout << "! --------------------------------------------------------\n";
        switch (cplex.getStatus())
        {
        case IloAlgorithm::Optimal:
            std::cout << "! Status: OPTIMAL\n";
            break;

        case IloAlgorithm::Feasible:
            std::cout << "! Status: FEASIBLE (time limit or other stopping criterion reached)\n";
            break;

        default:
            std::cout << "! Status: " << cplex.getStatus() << "\n";
            break;
        }
        std::cout << "! Best span = " << solution_span << "\n";
        std::cout << "! Labeling: ";
        for (int v = 0; v < graph_data.num_vertices; v++)
        {
            std::cout << solution[v] << " ";
        }
        std::cout << "\n";
        std::cout << "! --------------------------------------------------------\n";

        std::unique_ptr<Verifier> verifier = get_verifier(config_data.vertices_mode);
        if (verifier->verify(config_data, graph_data, solution, solution_span))
        {
            std::cout << "! All verification passed\n";
        }
    }
    else
    {
        std::cout << "! --------------------------------------------------------\n";
        switch (cplex.getStatus())
        {
        case IloAlgorithm::Infeasible:
            std::cout << "! Problem is INFEASIBLE\n";
            break;

        case IloAlgorithm::InfeasibleOrUnbounded:
            std::cout << "! Problem is INFEASIBLE OR UNBOUNDED\n";
            break;

        case IloAlgorithm::Unbounded:
            std::cout << "! Problem is UNBOUNDED\n";
            break;

        case IloAlgorithm::Unknown:
            std::cout << "! Problem is UNKNOWN\n";
            std::cout << "! CPLEX Status = " << cplex.getCplexStatus() << "\n";
            break;

        default:
            std::cout << "! Solver failed.\n";
            std::cout << "! Status = " << cplex.getStatus() << "\n";
            std::cout << "! CPLEX status = " << cplex.getCplexStatus() << "\n";
            break;
        }
        std::cout << "! --------------------------------------------------------\n";
    }

    mip_data.env.end();

    return 0;
}