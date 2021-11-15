#ifndef PROGRAM_HPP
#define PROGRAM_HPP

#include <vector>
#include <list>
#include <utility>
#include <filesystem>

typedef std::vector<std::list<int>> live_info;

typedef struct {
    std::list<int> vertices;
    std::list<std::pair<int, int>> edges;
} interference_graph;

typedef std::vector<std::pair<int, int>> color_mapping;

namespace program {
    
    live_info parse(std::filesystem::path);

    interference_graph build_interference_graph(live_info&);
}

#endif