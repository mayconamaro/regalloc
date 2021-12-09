#include "construction.hpp"
#include "program.hpp"
#include <numeric>
#include <random>
#include <utility>
#include <vector>

bool is_valid(color_mapping &t, interference_graph &g, int vertex, int color) {

  for (auto p : g.edges) {
    if (p.first == vertex && t.at(p.second).at(color) == 1) {
      return false;
    }
  }

  return true;
}

std::pair<float, color_mapping> construction::greedy(interference_graph &g) {

  std::vector<int> colors(g.vertices.size(), 0);
  color_mapping t(g.vertices.size(), colors);

  std::vector<int> available_colors;

  for (int i = 0; ((size_t)i) < g.vertices.size(); i++) {

    available_colors.push_back(i);
  }

  std::vector<int> used_colors(available_colors.size(), 0);

  for (auto v : g.vertices) {
    int pos = 0;

    while (!is_valid(t, g, v, available_colors.at(pos))) {
      pos++;
    }

    t.at(v).at(available_colors.at(pos)) = 1;

    if (used_colors.at(pos) == 0) {
      used_colors.at(pos) = 1;
    }
  }

  return std::make_pair(
      std::accumulate(used_colors.begin(), used_colors.end(), 0), t);
}

std::pair<float, color_mapping> construction::random(interference_graph &g) {

  srand(time(0));
  std::vector<int> colors(g.vertices.size(), 0);
  color_mapping t(g.vertices.size(), colors);

  std::vector<int> available_colors;

  for (int i = 0; ((size_t)i) < g.vertices.size(); i++) {

    available_colors.push_back(i);
  }

  std::vector<int> used_colors(available_colors.size(), 0);

  for (auto v : g.vertices) {
    int pos = 0;

    do {
      pos = rand() % available_colors.size();
    } while (!is_valid(t, g, v, available_colors.at(pos)));

    t.at(v).at(available_colors.at(pos)) = 1;

    if (used_colors.at(pos) == 0) {
      used_colors.at(pos) = 1;
    }
  }

  return std::make_pair(
      std::accumulate(used_colors.begin(), used_colors.end(), 0), t);
}
