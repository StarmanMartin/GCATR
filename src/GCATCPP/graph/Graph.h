//
// Created by Martin on 18.07.2018.
//

#ifndef GCATCPP_GRAPH_H
#define GCATCPP_GRAPH_H

#include <memory>
#include <vector>

#include "Edge.h"
#include "Vertex.h"
#include "../codes/Alphabet.h"
#include "../helper/AbstractErrorManager.h"

class AbstractCode;

namespace graph {

    class Graph : public err::AbstractErrorManager {
    public:

        explicit Graph(const AbstractCode &);

        explicit Graph(Alphabet);

        void parse_code(const AbstractCode &code);

        void add_vertices(const std::string &from, const std::string &to);

        virtual void add_word(const std::string &word);

        void add_graph(const Graph &);

        bool contains_vertex(const Vertex &) const;

        std::vector<Edge> get_path_between(const Vertex &, const Vertex &) const;

        void add_path_as_list_of_vertexes(const std::vector<Vertex> &);

        void add_path_as_list_of_edges(const std::vector<Edge> &, size_t start = 0);
        std::vector<Vertex> get_target_vertex_form_vertex_label(const std::string &vertex_label) const;

        std::vector<Edge> remove_edges(const Graph &to_remove);

        int compare(const Graph &) const;

        bool is_sub_graph(const Graph &) const;

        bool operator==(const Graph &d) const { return !this->compare(d); }

        bool operator<(const Graph &d) const { return compare(d) < 0; }

        bool operator>(const Graph &d) const { return compare(d) > 0; }

        std::vector<Vertex> get_vertices() const;

        std::vector<Edge> get_edges() const;

        std::vector<Vertex> get_target_vertex_form_vertex(const Vertex &vertex) const;

        std::vector<Edge> get_edges_form_vertex(const Vertex &vertex) const;

        std::vector<Edge> get_path_start_edges() const;

        Alphabet get_alphabet();

    protected:

        Alphabet alphabet;

        std::vector<std::shared_ptr<Vertex> > vertices = {};
        std::vector<std::shared_ptr<Edge> > edges = {};

        std::shared_ptr<Vertex> find_vertices(std::string &word);

        std::shared_ptr<Vertex> add_vertices(std::shared_ptr<Vertex>);



    };
}


#endif //GCATCPP_GRAPH_H
