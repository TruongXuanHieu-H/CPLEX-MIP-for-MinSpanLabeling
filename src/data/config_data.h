#ifndef CONFIG_DATA_H
#define CONFIG_DATA_H

#include <iostream>

enum class VerticesMode
{
    no_hole,  // All the labels must be used.
    all_diff, // All the labels must be different.
    has_hole, // No constraints.
};

enum class TargetValueType
{
    abp, // Linear target
    cabp,
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
        else if (v_mode == "all_diff")
        {
            vertices_mode = VerticesMode::all_diff;
            std::cout << "! Vertices mode is set to All different\n";
        }
        else if (v_mode == "has_hole")
        {
            vertices_mode = VerticesMode::has_hole;
            std::cout << "! Vertices mode is set to Has hole\n";
        }
        else
        {
            std::cerr << "! Vertices mode " << v_mode << " is undefined\n";
            exit(1);
        }

        std::string t_v_type = argv[7];
        if (t_v_type == "abp")
        {
            target_value_type = TargetValueType::abp;
        }
        else if (t_v_type == "cabp")
        {
            target_value_type = TargetValueType::cabp;
        }
        else
        {
            std::cerr << "! Target value type " << t_v_type << " is undefined\n";
            exit(1);
        }
    }

    std::string instance_dir;
    TargetValueType target_value_type;
    int target_value;
    int lower_bound;
    int upper_bound;
    int time_limit;
    VerticesMode vertices_mode;
};

#endif
