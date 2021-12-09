#ifndef LOCAL_SEARCH_HPP
#define LOCAL_SEARCH_HPP

#include "program.hpp"

namespace local_search {

float first_improvement(interference_graph &, color_mapping &, float);

float random(interference_graph &, color_mapping &, float, int );
} // namespace local_search

namespace neighbourhood {

float realloc_delta(color_mapping &, interference_graph &, float , int ,
                    int );

float reallocation(color_mapping &, interference_graph &, float &, int &,
                   int &);

} // namespace neighbourhood

#endif