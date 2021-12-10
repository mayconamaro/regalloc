#include "local_search.hpp"
#include "program.hpp"
#include <cassert>
#include <cstdlib>
#include <limits>
#include <random>

float neighbourhood::realloc_delta(color_mapping &t, interference_graph &g,
                                   float fo, int v, int c) {

  /* If neighbour violates restrictions, its objective function value will be
   * the largest possible */
  for (auto p : g.edges) {
    if (p.first == v && t.at(p.second).at(c) == 1) {
      return std::numeric_limits<float>::max();
    }
  }

  int previous_color = 0;
  int colors_to_add = 1;
  int colors_to_remove = 1;

  for (int i = 0; (size_t)i < t.size(); i++) {
    if (t.at(i).at(c) == 1 && i != v) {
      colors_to_add = 0;
      break;
    }
  }

  for (int j = 0; (size_t)j < t.at(v).size(); j++) {
    if (t.at(v).at(j) == 1 && j != c) {
      previous_color = j;
      break;
    }
  }

  for (int i = 0; (size_t)i < t.size(); i++) {
    if (t.at(i).at(previous_color) == 1 && i != v) {
      colors_to_remove = 0;
      break;
    }
  }

  return fo + colors_to_add - colors_to_remove;
}

float neighbourhood::reallocation(color_mapping &t, interference_graph &g,
                                  float &fo, int &v, int &c) {
  int n = (int)g.vertices.size();
  srand(time(0));
  v = (int) (rand() % n);

  do {
    c = (int) (rand() % n);
  } while (t.at(v).at(c) == 1);

  return neighbourhood::realloc_delta(t, g, fo, v, c);
}

float local_search::first_improvement(interference_graph &g, color_mapping &t,
                                      float fo) {
  float new_fo;
  float fo_star = fo;
  bool improved = false;

  for (int i = 0; (size_t)i < t.size() && !improved; i++) {
    for (int j = 0; (size_t)j < t.at(i).size(); j++) {

      if (t.at(i).at(j) == 1) // skip if already allocated
        continue;

      new_fo = neighbourhood::realloc_delta(t, g, fo, i, j);

      if (new_fo < fo_star) {

        t.at(i).at(j) = 1;

        // remove the previous allocation
        for (int k = 0; (size_t)k < t.at(i).size(); k++) {
          if (t.at(i).at(k) == 1 && k != j) {
            t.at(i).at(k) = 0;
            break;
          }
        }

        fo_star = new_fo;
        improved = true;
        break;
      }
    }
  }

  return fo_star;
}

float local_search::random(interference_graph &g, color_mapping &t, float fo,
                           int max_iter) {

  int iter = 0;

  float new_fo;
  float fo_star = fo;

  int i, j = -1;

  while (iter < max_iter) {

    new_fo = neighbourhood::reallocation(t, g, fo, i, j);

    if (new_fo < fo_star) {

      t.at(i).at(j) = 1;

      // remove the previous allocation
      for (int k = 0; (size_t)k < t.at(i).size(); k++) {
        if (t.at(i).at(k) == 1 && k != j) {
          t.at(i).at(k) = 0;
          break;
        }
      }

      fo_star = new_fo;
      iter = 0;
    } else {
      iter++;
    }
  }

  return fo_star;
}