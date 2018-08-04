//
// Created by Martin on 18.07.2018.
//

#include "Graph.h"

using namespace graph;

#include "../codes/AbstractGenCode.h"

void Graph::parse_code(const AbstractGenCode& code) {
    for(auto word : code.as_vector()) {
        this->add_word(word);
    }
}



std::vector< Edge > Graph::remove_edges(const Graph& to_remove) {
    std::vector< std::shared_ptr<Edge> > new_edges;
    for(auto own_edge : this->edges) {
        bool has_found_edge = false;
        for(auto edge : to_remove.edges) {
            auto comp_val = own_edge->compare(*edge);
            if(comp_val == 0) {
                has_found_edge = true;
                break;
            }
        }

        if(!has_found_edge) {
            new_edges.push_back(own_edge);
        }
    }

    this->edges = new_edges;
    return this->get_edges();
}

void Graph::add_word(std::string word) {
    for (size_t i = 1; i < word.length(); ++i) {
        this->add_vertices(word.substr(0, i), word.substr(i));
    }
}

void Graph::add_graph(const Graph& add_graph) {
    for (auto new_vertex : add_graph.edges) {
        this->add_vertices(new_vertex->get_from()->get_label(), new_vertex->get_to()->get_label());
    }
}

void Graph::add_vertices(std::string from, std::string to) {
    auto from_ptr = this->add_vertices(std::make_shared<Vertex>(from));
    auto to_ptr = this->add_vertices(std::make_shared<Vertex>(to));

    auto new_edge_ptr = std::make_shared<Edge>(from_ptr, to_ptr);

    for (int i = 0; i < this->edges.size(); ++i) {
        auto edge = *(this->edges[i]);
        auto comp_val = new_edge_ptr->compare(edge);
        if(comp_val == 0) {
            return;
        } else if (comp_val > 0) {
            this->edges.insert(this->edges.begin() + i, new_edge_ptr);
            return;
        }
    }

    this->edges.push_back(new_edge_ptr);
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
    for (auto vertex : this->vertices) {
        res_vec.push_back(Vertex(vertex.operator*()));
    }
    return res_vec;
}

std::vector<Edge> Graph::get_edges() const {
    std::vector<Edge> res_vec;
    for (auto edge : this->edges) {
        res_vec.push_back(Edge(edge.operator*()));
    }
    return res_vec;
}

int Graph::compare(const Graph &in_g) const {
    if(this->edges.size() != in_g.edges.size()) {
        return (signed)this->edges.size() - (signed)in_g.edges.size();
    }

    if(this->vertices.size() != in_g.vertices.size()) {
        return (signed)this->vertices.size() - (signed)in_g.vertices.size();
    }

    for(int i = 0; i < this->edges.size(); ++i) {
        auto comp_val = this->edges[i]->compare(*in_g.edges[i]);
        if(comp_val != 0) {
            return comp_val;
        }
    }

    return 0;

}