#ifndef GRAPH_DATA_H
#define GRAPH_DATA_H

#include <iostream>
#include <vector>
#include <fstream>

#include "config_data.h"
#include "../edge.h"

class GraphData
{
public:
    GraphData(ConfigData &config_data)
    {
        std::ifstream fin(config_data.instance_dir);
        if (!fin)
        {
            std::cerr << "Cannot open file\n";
            exit(1);
        }

        std::getline(fin, graph_name);
        fin >> num_vertices >> temp_param >> num_edges;
        for (int i = 0; i < num_edges; i++)
        {
            int u, v;
            fin >> u >> v;
            edges.push_back({u, v});
        }

        fin.close();
    }

    std::string graph_name;
    int num_vertices;
    int temp_param;
    int num_edges;
    std::vector<Edge> edges;
};

#endif