#include "construction.hpp"
#include "local_search.hpp"
#include "metaheuristics/multi_start.hpp"
#include "metaheuristics/smart_ils.hpp"
#include "program.hpp"
#include <cstdlib>
#include <filesystem>
#include <iostream>
#include <utility>

//#define DEBUG

int main(int argc, char *argv[]) {

  if (argc <= 2) {

    std::cout << "How to use this program" << std::endl
              << std::endl
              << argv[0] << " "
              << "[FILE]"
              << " "
              << "[G | P]" << std::endl
              << std::endl
              << "G means the input file is a graph, P means it is a program"
              << std::endl;

    std::exit(0);
  }

  std::filesystem::path file(argv[1]);

  interference_graph i;

  if (argv[2][0] == 'P') {
    live_info l = program::parse(file);
    i = program::build_interference_graph(l);
  }

  if (argv[2][0] == 'G') {
    
  }

#ifdef DEBUG
  /* Check if the graph is complete -- debug use only */
  int n = (int)i.vertices.size();
  bool complete = true;
  for (int i1 = 0; i1 < n; i1++) {
    for (int j1 = i1 + 1; j1 < n; j1++) {
      bool found = false;
      for (auto p1 : i.edges) {
        if (((p1.first == i1 && p1.second == j1) ||
             (p1.first == j1 && p1.second == i1)) &&
            i1 != j1) {
          found = true;
          break;
        }
      }
      if (!found)
        complete = false;
    }
  }
  if (complete) {
    std::cout
        << "complete graph, the optimal solution is the number os variables"
        << std::endl;
    std::exit(0);
  }
#endif

  std::pair<float, color_mapping> p = construction::random(i);
  float fo = p.first;
  color_mapping initial = p.second;

#ifdef DEBUG
  /* Print the initial solution */
  for (int k = 0; k < (int)initial.size(); k++) {
    for (int m = 0; m < (int)initial.at(k).size(); m++) {
      if (initial.at(k).at(m) == 1) {
        std::cout << "variable " << k << " bound to register " << m
                  << std::endl;
        break;
      }
    }
  }
#endif

  std::cout << "Starting solution value: " << fo << std::endl;

  fo = metaheuristic::multi_start(i, initial, fo, 40);

#ifdef DEBUG
  for (int k = 0; k < (int)initial.size(); k++) {
    for (int m = 0; m < (int)initial.at(k).size(); m++) {
      if (initial.at(k).at(m) == 1) {
        std::cout << "variable " << k << " bound to register " << m
                  << std::endl;
        break;
      }
    }
  }
#endif

  std::cout << "Final solution value: " << fo << std::endl;
}