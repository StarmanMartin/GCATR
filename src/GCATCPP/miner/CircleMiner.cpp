//
// Created by Martin on 17.07.2018.
//

#include "CircleMiner.h"

#include "../codes/AbstractCode.h"
#include "../tester/Circular.h"

using namespace miner;

std::vector<std::vector<std::string> > CircleMiner::mine_path_as_vector(AbstractCode *gen_code) {
    auto cycling_paths = CircleMiner::mine_all_path_as_graph(gen_code);
    std::vector<std::vector<std::string>> res(cycling_paths.size());
    size_t i = 0;
    for (const auto &cycling_path : cycling_paths) {
        auto start_edge = cycling_path.get_edges()[0];
        auto start_vertex = *start_edge.get_from();
        auto end_vertex = *start_edge.get_to();
        res[i].push_back(start_vertex.get_label());
        res[i].push_back(end_vertex.get_label());
        while(start_vertex.compare(end_vertex)) {
            end_vertex = cycling_path.get_target_vertex_form_vertex(end_vertex)[0];
            res[i].push_back(end_vertex.get_label());
        }

        ++i;
    }

    return res;
}

graph::Graph CircleMiner::mine_path_as_graph(AbstractCode *gen_code) {
    graph::Graph res(gen_code->get_alphabet());
    auto circles_as_graph = CircleMiner::mine_all_path_as_graph(gen_code);
    for(const auto &g : circles_as_graph) {
        res.add_graph(g);
    }

    return res;

}

std::vector<graph::Graph> CircleMiner::mine_all_path_as_graph(AbstractCode *gen_code) {

    Circular tester;

    auto res = tester.get_circles(gen_code);
    if (res.empty()) {
        gen_code->add_error_msg("Code is circular -> no circle path");
        return res;
    }

    return res;

}