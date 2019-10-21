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

    for (size_t i = 0; i < this->edges.size(); ++i) {
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
    for (size_t i = 0; i < this->vertices.size(); ++i) {
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

    for (size_t i = 0; i < this->edges.size(); ++i) {
        auto comp_val = this->edges[i]->compare(*in_g.edges[i]);
        if (comp_val != 0) {
            return comp_val;
        }
    }

    return 0;

}

bool Graph::is_sub_graph(const Graph &in_g) const {
    if (this->edges.size() < in_g.edges.size()) {
        return false;
    }

    if (this->vertices.size() < in_g.vertices.size()) {
        return false;
    }

    int in_idx = 0;
    for (const auto &edge : in_g.edges) {
        size_t comp_val = 0;
        if (in_idx >= this->edges.size()) {
            return false;
        }

        do {

            comp_val = this->edges[in_idx]->compare(*edge);
        } while ((++in_idx) < this->edges.size() && comp_val > 0);

        if (comp_val != 0) {
            return false;
        }
    }

    return true;

}

std::vector<Vertex> Graph::get_target_vertex_form_vertex_label(const std::string &vertex_label) const {
    Vertex a(vertex_label, this->alphabet);
    return this->get_target_vertex_form_vertex(a);
}

std::vector<Vertex> Graph::get_target_vertex_form_vertex(const Vertex &vertex) const {
    std::vector<Vertex> edges;
    for (const auto &e : this->get_edges()) {
        if (e.get_from()->compare(vertex) == 0) {
            edges.push_back(*e.get_to());
        }
    }

    return edges;
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


bool Graph::contains_vertex(const Vertex &in_vertex) const {
    auto it = this->vertices.begin();
    while (it != this->vertices.end() && (*it)->get_index() > in_vertex.get_index()) {
        it++;
    }

    return it != this->vertices.end() && (*it)->get_index() == in_vertex.get_index();
}

std::vector<Edge> Graph::get_path_between(const Vertex &a, const Vertex &b) const {
    bool has_both = this->contains_vertex(a) && this->contains_vertex(b);
    if (!has_both) {
        return {};
    }

    size_t idx = 0;

    std::vector<std::vector<Edge>> path = {this->get_edges_form_vertex(a)};
    bool has_found = false;

    for (const auto &e : path[idx]) {
        if (e >> b) {
            has_found = true;
        }
    }
    while (!has_found) {
        auto next_elements = this->get_edges_form_vertex(*path[idx][0].get_to());
        if (next_elements.empty()) {
            path[idx].pop_back();
            if (path[idx].empty()) {
                path.pop_back();
                idx--;
                if (idx == -1) {
                    return {};
                }
            }
        } else {
            path.push_back(next_elements);
            idx++;

            for (const auto &e : path[idx]) {
                if (e >> b) {
                    has_found = true;
                    break;
                }
            }
        }
    }

    std::vector<Edge> return_path;
    return_path.reserve(path.size());
    for (const auto &e : path) {
        return_path.push_back(e[0]);
    }

    return return_path;
}

void Graph::add_path_as_list_of_edges(const std::vector<Edge> &path, size_t start) {

    size_t end = path.size();

    for (size_t i = start; i < end - 1; ++i) {
        this->add_vertices(path[i].get_from()->get_label(), path[i].get_to()->get_label());
    }
}

void Graph::add_path_as_list_of_vertexes(const std::vector<Vertex> &path) {

    size_t end = path.size() - 1;

    for (size_t i = 0; i < end; ++i) {
        this->add_vertices(path[i].get_label(), path[i + 1].get_label());
    }

}
