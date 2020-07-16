//
// Created by martins on 16.07.20.
//

#include "PathEndVerticesMiner.h"
#include "../graph/Graph.h"

std::vector<std::string> miner::PathEndVerticesMiner::mine_vertices_as_vector(AbstractCode *a) {
    graph::Graph g(*a);

    std::set<std::string> inV;
    std::set<std::string> outV;

    for(const auto &v : g.get_edges()) {
        inV.insert(v.get_from()->get_label());
        outV.erase(v.get_from()->get_label());

        if(inV.find(v.get_to()->get_label()) == inV.end()) {
            outV.insert(v.get_to()->get_label());
        }
    }

    return std::vector<std::string>(outV.begin(), outV.end());
}
