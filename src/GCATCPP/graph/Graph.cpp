//
// Created by Martin on 18.07.2018.
//

#include "Graph.h"

#include <utility>

using namespace graph;

#include "../codes/AbstractCode.h"


Graph::Graph(const AbstractCode &a) : alphabet(a.get_alphabet()) {
    this->parse_code(a);
}

Graph::Graph(Alphabet a) : alphabet(std::move(a)) {
}

void Graph::parse_code(const AbstractCode &code) {
    this->alphabet = code.get_alphabet();
    for (const auto &word : code.as_set()) {
        this->add_word(word);
    }
}


std::vector<Edge> Graph::remove_edges(const Graph &to_remove) {
    std::vector<std::shared_ptr<Edge> > new_edges;
    for (const auto &own_edge : this->edges) {
        bool has_found_edge = false;
        for (const auto &edge : to_remove.edges) {
            auto comp_val = own_edge->compare(*edge);
            if (comp_val == 0) {
                has_found_edge = true;
                break;
            }
        }

        if (!has_found_edge) {
            new_edges.push_back(own_edge);
        }
    }

    this->edges = new_edges;
    return this->get_edges();
}

void Graph::add_word(const std::string &word) {
    for (size_t i = 1; i < word.length(); ++i) {
        this->add_vertices(word.substr(0, i), word.substr(i));
    }
}

void Graph::add_graph(const Graph &add_graph) {
    for (const auto &new_vertex : add_graph.edges) {
        this->add_vertices(new_vertex->get_from()->get_label(), new_vertex->get_to()->get_label());
    }
}

void Graph::add_vertices(const std::string &from, const std::string &to) {
    auto from_ptr = this->add_vertices(std::make_shared<Vertex>(from, this->alphabet));
    auto to_ptr = this->add_vertices(std::make_shared<Vertex>(to, this->alphabet));

    auto new_edge_ptr = std::make_shared<Edge>(from_ptr, to_ptr, this->alphabet);

    for (int i = 0; i < this->edges.size(); ++i) {
        auto edge = *(this->edges[i]);
        auto comp_val = new_edge_ptr->compare(edge);
        if (comp_val == 0) {
            return;
        } else if (comp_val > 0) {
            this->edges.insert(this->edges.begin() + i, new_edge_ptr);
            return;
        }
    }

    this->edges.push_back(new_edge_ptr);
}

std::shared_ptr<Vertex> Graph::find_vertices(std::string &word) {
    Vertex new_vertex(word, this->alphabet);
    for (std::shared_ptr<Vertex> vertex: this->vertices) {
        if (vertex->compare(new_vertex) == 0) {
            return vertex;
        }
    }

    return nullptr;
}

std::shared_ptr<Vertex> Graph::add_vertices(std::shared_ptr<Vertex> new_vertex) {
    for (int i = 0; i < this->vertices.size(); ++i) {
        Vertex vertex = *(this->vertices[i]);
        if (new_vertex->compare(vertex) == 0) {
            return this->vertices[i];
        } else if (new_vertex->compare(vertex) > 0) {
            this->vertices.insert(this->vertices.begin() + i, new_vertex);
            return new_vertex;
        }

    }

    this->vertices.push_back(new_vertex);
    return new_vertex;
}

std::vector<Vertex> Graph::get_vertices() const {
    std::vector<Vertex> res_vec;
    for (const auto &vertex : this->vertices) {
        res_vec.emplace_back(vertex.operator*());
    }
    return res_vec;
}

std::vector<Edge> Graph::get_edges() const {
    std::vector<Edge> res_vec;
    for (const auto &edge : this->edges) {
        res_vec.emplace_back(edge.operator*());
    }
    return res_vec;
}

std::vector<Edge> Graph::get_path_start_edges() const {
    std::vector<Edge> local_edges = this->get_edges();
    std::vector<Edge> path_start_edges;
    for (const auto &vertex : this->get_vertices()) {
        bool has_no_incoming = true;
        for (const auto &edge : local_edges) {
            if (edge.get_to()->compare(vertex) == 0) {
                has_no_incoming = false;
                break;
            }
        }

        if (has_no_incoming) {
            auto vec1 = this->get_edges_form_vertex(vertex);
            path_start_edges.insert(path_start_edges.begin(), vec1.begin(), vec1.end());
        }
    }

    if (path_start_edges.empty() && !local_edges.empty()) {
        return {local_edges[0]};
    }

    return path_start_edges;
}

int Graph::compare(const Graph &in_g) const {
    if (this->edges.size() != in_g.edges.size()) {
        return (signed) this->edges.size() - (signed) in_g.edges.size();
    }

    if (this->vertices.size() != in_g.vertices.size()) {
        return (signed) this->vertices.size() - (signed) in_g.vertices.size();
    }

    for (int i = 0; i < this->edges.size(); ++i) {
        auto comp_val = this->edges[i]->compare(*in_g.edges[i]);
        if (comp_val != 0) {
            return comp_val;
        }
    }

    return 0;

}

std::vector<Edge> Graph::get_edges_form_vertex(const Vertex &vertex) const {
    std::vector<Edge> edges;
    for (const auto &e : this->get_edges()) {
        if (e.get_from()->compare(vertex) == 0) {
            edges.push_back(e);
        }
    }

    return edges;
}

Alphabet Graph::get_alphabet() {
    return this->alphabet;
}

void Graph::add_path_as_list_of_vertexes(const std::vector<Vertex> &path,
                                         __gnu_cxx::__normal_iterator<Vertex *, std::vector<Vertex>> from,
                                         __gnu_cxx::__normal_iterator<Vertex *, std::vector<Vertex>> to) {
    int start = from - path.begin();
    int end = to - path.begin();


    for (auto i = start; i < end-1; ++i) {
        this->add_vertices(path[i].get_label(), path[i+1].get_label());
    }
}
