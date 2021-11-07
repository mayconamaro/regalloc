#include <iostream>
#include <filesystem>
#include <cstdlib>
#include <utility>
#include "program.hpp"
#include "construction.hpp"
#include "local_search.hpp"
#include "metaheuristics/smart_ils.hpp"

int main(int argc, char *argv[]){

    if(argc <= 1) {

        std::cout << "How to use this program" 
                  << std::endl 
                  << std::endl
                  << argv[0] << " " << "[FILE]" 
                  << std::endl;

        std::exit(0);
    }

    std::filesystem::path file(argv[1]);

    live_info l = program::parse(file);
    interference_graph i = program::build_interference_graph(l);
    
    std::pair<float, color_mapping> p = construction::greedy(i);
    float fo = p.first;
    color_mapping initial = p.second;
    
    fo = local_search::random(i, initial, fo);
    fo = metaheuristic::smart_ils(i, initial, fo);

    std::cout << fo << std::endl;
}