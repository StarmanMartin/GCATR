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
    this->alphabet = code->get_alphabet();

    for (const auto &current_edge : all_edges) {
        if (!CONTAINS_IN(*current_edge.get_from(), this->visited_edges)) {
            is_code_circular = is_code_circular & this->rec_is_circular(&g, current_edge);
            if (!is_code_circular && this->is_quick_test) {
                return false;
            }
        }
    }


    return is_code_circular;
}

std::vector<int> Circular::check_if_path_is_circular(const std::vector<std::vector<graph::Vertex>> &path_tree) {
    graph::Vertex last = path_tree.back()[0];
    std::vector<int> indexes;
    for (size_t i = 0; i < path_tree.size() - 1; ++i) {
        if (last == path_tree[i][0]) {
            indexes.push_back(i);
        }
    }

    return indexes;
}

std::vector<graph::Vertex>
Circular::get_path_of_path_tree(const std::vector<std::vector<graph::Vertex>> &path_tree, size_t from = 0) {
    std::vector<graph::Vertex> current_path;
    current_path.reserve(path_tree.size());
    for (size_t i = from; i < path_tree.size(); ++i) {
        current_path.push_back(path_tree[i][0]);
    }

    return current_path;
}

void Circular::update_path_tree(std::vector<std::vector<graph::Vertex>> &path_tree) {
    graph::Vertex last = path_tree.back()[0];
    for (size_t i = 0; i < path_tree.size() - 1; ++i) {
        path_tree[i].erase(std::remove(path_tree[i].begin() + 1, path_tree[i].end(), last), path_tree[i].end());
    }
}

bool Circular::rec_is_circular(graph::Graph *main_graph,
                               const graph::Edge &a) {

    size_t idx = 0;

    std::vector<std::vector<graph::Vertex>> path = {{*a.get_from()}};
    auto begin_cyclic_idxes = check_if_path_is_circular(path);

    while (true) {
        std::vector<graph::Vertex> next_elements;
        if (!begin_cyclic_idxes.empty()) {
            if (this->is_quick_test) return false;
            for(const auto &begin_cyclic_idx : begin_cyclic_idxes) {
                auto c_path = this->get_path_of_path_tree(path, begin_cyclic_idx);
                this->add_circle(c_path);
            }
        } else {
            this->update_path_tree(path);
            next_elements = main_graph->get_target_vertex_form_vertex(path[idx][0]);
        }

        if (next_elements.empty()) {
            this->add_longest_path(this->get_path_of_path_tree(path));
            path[idx].erase(path[idx].begin());
            while (path[idx].empty()) {
                if (idx == 0) {
                    return this->circle.empty();
                } else {
                    path.pop_back();
                    idx--;
                    path[idx].erase(path[idx].begin());
                }
            }
        } else {
            path.push_back(next_elements);
            std::copy(next_elements.begin(), next_elements.end(),
                      std::inserter(this->visited_edges, this->visited_edges.end()));

            idx++;
        }

        begin_cyclic_idxes = check_if_path_is_circular(path);
    }
}

void Circular::add_circle(const std::vector<graph::Vertex> &circle_path) {
    this->longest_path_size = UINT_MAX;
    this->longest_path = {};

    graph::Graph circle_graph(this->alphabet);
    circle_graph.add_path_as_list_of_vertexes(circle_path);

    ///*DEBUG*/   std::cout << "\n\n" << circle_path.get_vertices().size() << "\n\n";
    for (const auto &graph : this->circle) {
        if (graph.is_sub_graph(circle_graph)) {
            return;
        }
    }

    for (const graph::Edge &e : circle_graph.get_edges()) {
        this->part_of_circular_path.push_back(e);
    }

    this->circle.push_back(circle_graph);
}

void Circular::add_longest_path(const std::vector<graph::Vertex> &circle_path) {


    if (this->longest_path_size > circle_path.size()) { return; }

    graph::Graph circle_graph(this->alphabet);
    circle_graph.add_path_as_list_of_vertexes(circle_path);

    if (this->longest_path_size < circle_path.size()) {
        this->longest_path_size = (unsigned int) circle_path.size();
        this->longest_path = {circle_graph};
    } else {
        for (const auto &graph : this->longest_path) {
            if (graph.compare(circle_graph) == 0) {
                return;
            }
        }

        this->longest_path.push_back(circle_graph);
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
