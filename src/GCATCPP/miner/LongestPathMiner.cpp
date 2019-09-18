//
// Created by Martin on 18.07.2018.
//

#include "LongestPathMiner.h"

#include "../codes/AbstractCode.h"
#include "../tester/Circular.h"

using namespace miner;

std::vector<std::vector<std::string> > LongestPathMiner::mine_path_as_vector(AbstractCode* gen_code) {

    auto longest_path_list = LongestPathMiner::mine_all_path_as_graph(gen_code);
    std::vector<std::vector<std::string>> res(longest_path_list.size());
    size_t i = 0;
    for (const auto &cycling_path : longest_path_list) {
        size_t num_of_edges = cycling_path.get_vertices().size()-1;
        res[i].push_back(*cycling_path.get_path_start_edges()[0].get_from());
        while (num_of_edges) {
            auto end_vertex = cycling_path.get_target_vertex_form_vertex_label(res[i].back())[0];
            res[i].push_back(end_vertex);
            --num_of_edges;
        }

        ++i;
    }

    return res;
}

graph::Graph LongestPathMiner::mine_path_as_graph(AbstractCode *gen_code) {
    graph::Graph res(gen_code->get_alphabet());
    auto circles_as_graph = LongestPathMiner::mine_all_path_as_graph(gen_code);
    for(const auto &g : circles_as_graph) {
        res.add_graph(g);
    }

    return res;
}

std::vector<graph::Graph> LongestPathMiner::mine_all_path_as_graph(AbstractCode *gen_code) {

    Circular codeTester;
    auto res = codeTester.get_longest_path(gen_code);
    if (res.empty()) {
        gen_code->add_error_msg("Code is not circular -> infinite longest path");
    }

    return res;

}