//
// Created by Martin on 04.08.2018.
//

#ifndef GCATCPP_C3GRAPH_H
#define GCATCPP_C3GRAPH_H

#include "Graph.h"

namespace graph {
    class C3Graph : public Graph{
    public:
        virtual void add_word(std::string word);
        std::vector<Edge> get_c3_edges() const;
    private:
        std::vector <std::shared_ptr<Edge>> c3_edges;
        void add_c3_edge(std::shared_ptr<Vertex> from_ptr, std::shared_ptr<Vertex> to_ptr);
    };
}


#endif //GCATCPP_C3GRAPH_H
