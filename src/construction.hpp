#ifndef CONSTRUCTION_HPP
#define CONSTRUCTION_HPP

#include <utility>
#include "program.hpp"

namespace construction {
    
    std::pair<float, color_mapping> greedy(interference_graph&); 
    
    std::pair<float, color_mapping> random(interference_graph&); 
}

#endif