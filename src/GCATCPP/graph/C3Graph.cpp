//
// Created by Martin on 04.08.2018.
//

#include "C3Graph.h"
#include "../codes/AbstractGenCode.h"
#include "../codes/Alphabet.h"
using namespace graph;

C3Graph::C3Graph(const AbstractGenCode & code): Graph(code){

}

C3Graph::C3Graph(const Alphabet &alphabet ) : Graph(alphabet) {

}

void C3Graph::add_word(const std::string & word) {
    if(word.length() != 3) {
        this->add_error_msg("For a C_3 graph the codon length has to be 3");
        return;
    }
    Graph::add_word(word);


    std::string from = word.substr(1,1);
    std::string to = word.substr(2,1) + word.substr(0,1);

    auto from_ptr = this->add_vertices(std::make_shared<Vertex>(from, this->alphabet));
    auto to_ptr = this->add_vertices(std::make_shared<Vertex>(to, this->alphabet));

    this->add_c3_edge(from_ptr, to_ptr);
    this->add_c3_edge(to_ptr, from_ptr);
}

void C3Graph::add_c3_edge(std::shared_ptr<Vertex> from_ptr, std::shared_ptr<Vertex> to_ptr) {
    auto new_edge_ptr = std::make_shared<Edge>(to_ptr, from_ptr, this->alphabet);
    for (int i = 0; i < this->c3_edges.size(); ++i) {
        auto edge = *(this->c3_edges[i]);
        auto comp_val = new_edge_ptr->compare(edge);
        if(comp_val == 0) {
            return;
        } else if (comp_val > 0) {
            this->c3_edges.insert(this->c3_edges.begin() + i, new_edge_ptr);
            return;
        }
    }

    this->c3_edges.push_back(new_edge_ptr);
}

std::vector<Edge> C3Graph::get_c3_edges() const {
    std::vector<Edge> res_vec;
    for (const auto &edge : this->c3_edges) {
        res_vec.emplace_back(Edge(edge.operator*()));
    }
    return res_vec;
}