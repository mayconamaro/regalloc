#include <vector>
#include <list>
#include <filesystem>
#include <fstream>
#include <unordered_map>
#include "program.hpp"

live_info program::parse (std::filesystem::path f){
    
    live_info t;
    
    std::fstream file;
    file.open(f, std::ios::in);

    if(file.is_open()){
        
        int program_points = 0;
        file >> program_points;

        for(int i = 0; i < program_points; i++){
            int vars_number = 0;
            file >> vars_number;
            std::list<int> used_vars;
            
            for(int j = 0; j < vars_number; j++){
                
                int var = 0;
                file >> var;
                used_vars.push_back(var);
            }

            t.push_back(used_vars);
        }
    }

    file.close();
    
    return t;
}

bool interferes(int f1, int l1, int f2, int l2){
    
    return !(l1 < f2 || l2 < f1);
}

interference_graph program::build_interference_graph(live_info& l){

    interference_graph t;

    std::unordered_map<int, int> first;
    std::unordered_map<int, int> last;

    for(int i = 0; ((size_t) i) < l.size(); i++){
        for(auto j : l.at(i)){
            if(first.contains(j)){
                int last_point = last.at(j);
                if(i > last_point){
                    last.erase(j);
                    last.insert({j, i});
                }
            }else{
                first.insert({j, i});
                last.insert({j, i});
                t.vertices.push_back(j);
            }
        }
    }

    for(auto i : t.vertices){
        for(auto j : t.vertices){
            if(i != j && interferes(first.at(i), 
                                    last.at(i), 
                                    first.at(j), 
                                    last.at(j))){
                t.edges.push_back({i, j});
            }
        }
    }

    return t;
}