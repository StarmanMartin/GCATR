//
// Created by Martin on 17.07.2018.
//

#include "CircleMiner.h"

#include "../codes/AbstractCode.h"
#include "../tester/Circular.h"

using namespace miner;

std::vector<std::vector<std::string> > CircleMiner::mine_path_as_vector(AbstractCode *gen_code) {
    auto circle_index = CircleMiner::mine_all_path_as_graph(gen_code);
    std::vector<std::vector<std::string>> res(circle_index.size());
    for (int i = 0; i < circle_index.size(); ++i) {
        auto edges = circle_index[i].get_edges();
        graph::Vertex current_vertex = *edges[0].get_to();
        do {
            for (auto &edge : edges) {
                if (edge.get_from()->compare(current_vertex) == 0) {
                    res[i].push_back((std::string) *edge.get_from());
                    current_vertex = *edge.get_to();
                }
            }
        } while (current_vertex.compare(*edges[0].get_from()) != 0);

        res[i].push_back(current_vertex.get_label());
        res[i].push_back(edges[0].get_to()->get_label());
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