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
    private:
        std::vector <std::shared_ptr<Edge>> undirected_edges;
    };
}


#endif //GCATCPP_C3GRAPH_H
