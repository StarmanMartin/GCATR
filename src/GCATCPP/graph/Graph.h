//
// Created by Martin on 18.07.2018.
//

#ifndef GCATCPP_GRAPH_H
#define GCATCPP_GRAPH_H

#include <memory>
#include <vector>

#include "Edge.h"
#include "Vertex.h"
#include "../helper/AbstractErrorManager.h"

class AbstractGenCode;

namespace graph {

    class Graph : public err::AbstractErrorManager {
    public:
        void parse_code(const AbstractGenCode &);

        void add_vertices(std::string from, std::string to);

        virtual void add_word(std::string word);

        void add_graph(const Graph &);


        std::vector<Edge> remove_edges(const Graph &to_remove);

        int compare(const Graph &) const;

        bool operator==(const Graph &d) const { return !this->compare(d); }

        bool operator<(const Graph &d) const { return compare(d) < 0; }

        bool operator>(const Graph &d) const { return compare(d) > 0; }

        std::vector<Vertex> get_vertices() const;

        std::vector<Edge> get_edges() const;

    protected:
        std::vector<std::shared_ptr<Vertex> > vertices = {};
        std::vector<std::shared_ptr<Edge> > edges = {};

        std::shared_ptr<Vertex> find_vertices(std::string &word);

        std::shared_ptr<Vertex> add_vertices(std::shared_ptr<Vertex>);
    };
}


#endif //GCATCPP_GRAPH_H
