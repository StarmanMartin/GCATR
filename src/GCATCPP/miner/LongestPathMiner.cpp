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
            for (int j = 0; j < edges.size(); ++j) {
                if(edges[j].get_to()->compare(*current_start_vertex) == 0) {
                    found_extension = true;
                    res[i].insert(res[i].begin(), edges[j].get_from()->get_label());
                    current_start_vertex = edges[j].get_from();
                } else if(edges[j].get_from()->compare(*current_end_vertex) == 0) {
                    found_extension = true;
                    res[i].push_back(edges[j].get_to()->get_label());
                    current_end_vertex = edges[j].get_to();
                }
            }
        } while (found_extension);
    }

    return res;
}

graph::Graph LongestPathMiner::mine_path_as_graph(AbstractCode *gen_code) {
    graph::Graph res;
    auto circles_as_graph = LongestPathMiner::mine_all_path_as_graph(gen_code);
    for(auto g : circles_as_graph) {
        res.add_graph(g);
    }

    return res;
}

std::vector<graph::Graph> LongestPathMiner::mine_all_path_as_graph(AbstractCode *gen_code) {

    Circular codeTester;
    if (!codeTester.test(gen_code)) {
        gen_code->add_error_msg("Code is not circular -> infinite longest path");
        std::vector<graph::Graph> res;
        return res;
    }

    return codeTester.get_longest_path();

}