#ifndef CONFIG_DATA_H
#define CONFIG_DATA_H

#include <iostream>

enum class VerticesMode
{
    no_hole,  // All the labels must be used.
    has_hole, // No constraints.
    all_diff, // All the labels must be different.
};

enum class TargetValueMode
{
    abp,  // Antibandwidth
    cabp, // Cyclic Antibandwidth
};

class ConfigData
{
public:
    ConfigData(int argc, char *argv[])
    {
        if (argc != 8)
        {
            std::cerr << "Usage: " << argv[0] << " <graph_file_dir> <target_value> <lower_bound> <upper_bound> <time_limit> <vertices_mode> <target_value_mode>\n";
            exit(1);
        }

        instance_dir = argv[1];
        std::cout << "! Solving for graph " << instance_dir << "\n";

        target_value = std::stod(argv[2]);
        std::cout << "! Target value is set to " << target_value << "\n";

        lower_bound = std::stoi(argv[3]);
        std::cout << "! Lower bound is set to " << lower_bound << "\n";

        upper_bound = std::stoi(argv[4]);
        std::cout << "! Upper bound is set to " << upper_bound << "\n";

        time_limit = std::stoi(argv[5]);
        std::cout << "! Time limit is set to " << time_limit << "\n";

        std::string v_mode = argv[6];
        if (v_mode == "no_hole")
        {
            vertices_mode = VerticesMode::no_hole;
            std::cout << "! Vertices mode is set to No hole\n";
        }
        else if (v_mode == "has_hole")
        {
            vertices_mode = VerticesMode::has_hole;
            std::cout << "! Vertices mode is set to Has hole\n";
        }
        else if (v_mode == "all_diff")
        {
            vertices_mode = VerticesMode::all_diff;
            std::cout << "! Vertices mode is set to All different\n";
        }
        else
        {
            std::cerr << "! Vertices mode " << v_mode << " is undefined\n";
            exit(1);
        }

        std::string target_value_mode = argv[7];
        if (target_value_mode == "abp")
        {
            this->target_value_mode = TargetValueMode::abp;
            std::cout << "! Target value mode is set to Antibandwidth\n";
        }
        else if (target_value_mode == "cabp")
        {
            this->target_value_mode = TargetValueMode::cabp;
            std::cout << "! Target value mode is set to Cyclic Antibandwidth\n";
        }
        else
        {
            std::cerr << "! Target value mode " << target_value_mode << " is undefined\n";
            exit(1);
        }
    }

    std::string instance_dir;
    int target_value;
    int lower_bound;
    int upper_bound;
    int time_limit;
    VerticesMode vertices_mode;
    TargetValueMode target_value_mode;
};

#endif
