//
// Created by Martin on 12.07.2018.
//

#include "Circular.h"
#include <string>
#include <iostream>
#include <regex>
#include <climits>

#define CONTAINS_IN(Y, X) (std::find(X.begin(), X.end(), Y) != X.end())
#define FINDS_IN(Y, X) std::find(X.begin(), X.end(), Y)

bool Circular::test(AbstractCode *code) {
    this->longest_path = {};
    this->circle = {};
    this->longest_path_size = 0;
    this->is_quick_test = true;
    return this->is_circular(code);
}


bool Circular::is_circular(AbstractCode *code) {
    graph::Graph g(*code);
    bool is_code_circular = true;
    this->visited_edges.clear();
    auto path_start_edges = g.get_path_start_edges();
    auto all_edges = g.get_edges();
    all_edges.insert(all_edges.begin(), path_start_edges.begin(), path_start_edges.end());

    for (const auto &current_edge : all_edges) {
        if (!CONTAINS_IN(current_edge, this->visited_edges)) {
            std::vector<graph::Vertex> path;
            is_code_circular = is_code_circular & this->rec_is_circular(&g,
                                                                        current_edge,
                                                                        path);
        }
    }


    return is_code_circular;
}

bool Circular::rec_is_circular(graph::Graph *main_graph,
                               const graph::Edge &current_edge,
                               std::vector<graph::Vertex> path) {
    path.push_back(*current_edge.get_from());
    bool is_code_circular = true;
    auto it = FINDS_IN(*current_edge.get_to(), path);
    if (it != path.end()) {
        path.push_back(*current_edge.get_to());
        graph::Graph gPath(main_graph->get_alphabet());
        gPath.add_path_as_list_of_vertexes(path, it, path.end());
        this->add_circle(gPath);
        is_code_circular = false;
    }

    if (CONTAINS_IN(current_edge, this->visited_edges)) {
        return is_code_circular;
    }

    this->visited_edges.push_back(current_edge);


    auto next_edges = main_graph->get_edges_form_vertex(*current_edge.get_to());

    if (next_edges.empty()) {
        path.push_back(*current_edge.get_to());
        graph::Graph gPath(main_graph->get_alphabet());
        gPath.add_path_as_list_of_vertexes(path, path.begin(), path.end());
        this->add_longest_path(gPath);
    } else {for (const auto &next_paths : next_edges) {
            is_code_circular = is_code_circular && this->rec_is_circular(main_graph, next_paths, path);
        }
    }

    return is_code_circular;
}

void Circular::add_circle(const graph::Graph &circle_path) {
    this->longest_path_size = UINT_MAX;
    this->longest_path = {};
    ///*DEBUG*/   std::cout << "\n\n" << circle_path.get_vertices().size() << "\n\n";
    for (const auto &graph : this->circle) {
        if (graph.compare(circle_path) == 0) {
            return;
        }
    }

    this->circle.push_back(circle_path);
}

void Circular::add_longest_path(graph::Graph circle_path) {
    if (this->longest_path_size > circle_path.get_edges().size()) { return; }

    if (this->longest_path_size < circle_path.get_edges().size()) {
        this->longest_path_size = (unsigned int) circle_path.get_edges().size();
        this->longest_path = {circle_path};
    } else {
        for (const auto &graph : this->longest_path) {
            if (graph.compare(circle_path) == 0) {
                return;
            }
        }

        this->longest_path.push_back(circle_path);
    }
}

std::vector<graph::Graph> Circular::get_circles(AbstractCode *code) {
    this->is_quick_test = false;
    this->longest_path = {};
    this->circle = {};
    this->longest_path_size = 0;
    this->is_circular(code);
    return this->circle;
}

std::vector<graph::Graph> Circular::get_longest_path(AbstractCode *code) {

    this->longest_path = {};
    this->circle = {};
    this->longest_path_size = 0;
    this->is_quick_test = false;
    this->is_circular(code);
    return this->longest_path;

}
