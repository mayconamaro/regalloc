#include "local_search.hpp"
#include "program.hpp"
#include <cstdlib>
#include <limits>

float neighbourhood::reallocation(color_mapping &t, interference_graph &g,
                                  float &fo, int &v, int &c) {
  int n = (int)g.vertices.size();
  srand(time(0));
  v = rand() % n;

  do {
    c = rand() % n;
  } while (t.at(v).at(c) == 1);

  /* If neighbour violates restrictions, its objective function value will be
   * the largest possible */
  for (auto p : g.edges) {
    if (p.first == v && t.at(p.second).at(c) == 1) {
      return std::numeric_limits<float>::max();
    }
  }

  for (auto i : t) {
    if (i.at(c) == 1) {
      return fo;
    }
  }

  return fo + 1;
}

float local_search::first_improvement(interference_graph &g, color_mapping &t,
                                      float fo) {

  return 0;
}

float local_search::random(interference_graph &, color_mapping &, float) {

  return 0; // TODO
}