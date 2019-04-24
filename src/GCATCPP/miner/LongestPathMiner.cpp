//
// Created by Martin on 18.07.2018.
//

#include "LongestPathMiner.h"

#include "../codes/AbstractCode.h"
#include "../tester/Circular.h"

using namespace miner;

std::vector<std::vector<std::string> > LongestPathMiner::mine_path_as_vector(AbstractCode* gen_code) {

    auto circle_index = LongestPathMiner::mine_all_path_as_graph(gen_code);
    std::vector<std::vector<std::string>> res(circle_index.size());
    for (int i = 0; i < circle_index.size(); ++i) {
        auto edges = circle_index[i].get_edges();
        bool found_extension = false;
        std::shared_ptr<graph::Vertex> current_end_vertex = edges[0].get_to();
        std::shared_ptr<graph::Vertex> current_start_vertex = edges[0].get_from();
        res[i] = {current_start_vertex->get_label(), current_end_vertex->get_label()};
        do {
            found_extension = false;
            //Todo first find beginning then find path
            for (auto &edge : edges) {
                if(edge.get_to()->compare(*current_start_vertex) == 0) {
                    found_extension = true;
                    res[i].insert(res[i].begin(), edge.get_from()->get_label());
                    current_start_vertex = edge.get_from();
                } else if(edge.get_from()->compare(*current_end_vertex) == 0) {
                    found_extension = true;
                    res[i].push_back(edge.get_to()->get_label());
                    current_end_vertex = edge.get_to();
                }
            }
        } while (found_extension);
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