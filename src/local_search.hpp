#ifndef LOCAL_SEARCH_HPP
#define LOCAL_SEARCH_HPP

#include "program.hpp"

namespace local_search {

    float first_improvement(interference_graph&, color_mapping&, float);
    
    float random(interference_graph&, color_mapping&, float);
}

#endif