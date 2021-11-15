#ifndef PROGRAM_HPP
#define PROGRAM_HPP

#include <filesystem>
#include <list>
#include <utility>
#include <vector>

typedef std::vector<std::list<int>> live_info;

typedef struct {
  std::list<int> vertices;
  std::list<std::pair<int, int>> edges;
} interference_graph;

typedef std::vector<std::vector<int>> color_mapping;

namespace program {

live_info parse(std::filesystem::path);

interference_graph build_interference_graph(live_info &);
} // namespace program

#endif