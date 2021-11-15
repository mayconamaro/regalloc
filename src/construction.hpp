#ifndef CONSTRUCTION_HPP
#define CONSTRUCTION_HPP

#include "program.hpp"
#include <utility>

namespace construction {

std::pair<float, color_mapping> greedy(interference_graph &);

std::pair<float, color_mapping> random(interference_graph &);
} // namespace construction

#endif