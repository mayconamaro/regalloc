#include "construction.hpp"
#include "local_search.hpp"
#include "metaheuristics/multi_start.hpp"
#include "metaheuristics/smart_ils.hpp"
#include "program.hpp"
#include <cstdlib>
#include <filesystem>
#include <iostream>
#include <utility>

int main(int argc, char *argv[]) {

  if (argc <= 1) {

    std::cout << "How to use this program" << std::endl
              << std::endl
              << argv[0] << " "
              << "[FILE]" << std::endl;

    std::exit(0);
  }

  std::filesystem::path file(argv[1]);

  live_info l = program::parse(file);

  interference_graph i = program::build_interference_graph(l);

  std::pair<float, color_mapping> p = construction::random(i);
  float fo = p.first;
  color_mapping initial = p.second;

  for (int k = 0; k < (int)initial.size(); k++) {
    for (int m = 0; m < (int)initial.at(k).size(); m++) {
      if (initial.at(k).at(m) == 1) {
        std::cout << "variable " << k << " bound to register " << m
                  << std::endl;
        break;
      }
    }
  }

  std::cout << "fo: " << fo << std::endl;

  fo = metaheuristic::smart_ils(i, initial, fo, 100, 5);

  std::cout << "meta applied! " << std::endl;
  for (int k = 0; k < (int)initial.size(); k++) {
    for (int m = 0; m < (int)initial.at(k).size(); m++) {
      if (initial.at(k).at(m) == 1) {
        std::cout << "variable " << k << " bound to register " << m
                  << std::endl;
        break;
      }
    }
  }

  std::cout << "fo: " << fo << std::endl;
}