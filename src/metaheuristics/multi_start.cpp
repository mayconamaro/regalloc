#include "multi_start.hpp"
#include "../construction.hpp"
#include "../local_search.hpp"
#include "../program.hpp"
#include <utility>

// TODO
float metaheuristic::multi_start(interference_graph &g, color_mapping &t,
                                 float fo, int max_iter) {

  float fo_star = fo;
  int iter = 0;

  while (iter < max_iter) {

    std::pair<float, color_mapping> p = construction::greedy(g);
    color_mapping t_new = p.second;

    float fo_new = local_search::first_improvement(g, t_new, p.first);

    if (fo_new < fo_star) {
      t = t_new;
      fo_star = fo_new;
      iter = 0;
    } else {
      iter++;
    }
  }

  return fo_star;
}
