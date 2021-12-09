#include "smart_ils.hpp"
#include "../local_search.hpp"
#include "../program.hpp"

float metaheuristic::smart_ils(interference_graph &g, color_mapping &t,
                               float fo, int max_iter, int max_times) {

  color_mapping s0 = t;
  float fo_s0 = local_search::first_improvement(g, s0, fo);
  int iter = 0;
  int depth = 1;
  int times = 1;
  float fo_star = fo;

  while (iter < max_iter) {

    iter++;

    // perturbation step
    for (int i = 0; i < depth; i++) {
      int v = -1;
      int c = -1;
      fo_s0 = neighbourhood::reallocation(s0, g, fo, v, c);

      // confirm the neighbour
      s0.at(v).at(c) = 1;
      for (int k = 0; (size_t)k < s0.at(v).size(); k++) {
        if (s0.at(v).at(k) == 1 && k != c) {
          s0.at(v).at(k) = 0;
          break;
        }
      }
    }

    fo_s0 = local_search::first_improvement(g, s0, fo_s0);

    if (fo_s0 < fo_star) {
      fo_star = fo_s0;
      t = s0;
      depth = 1;
      times = 1;
    } else {
      if (times <= max_times) {
        times++;
      } else {
        times = 1;
        depth++;
      }
    }
  }

  return fo_star;
}
