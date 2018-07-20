//
// Created by Martin on 12.07.2018.
//

#ifndef GCATCPP_CIRCULAR_H
#define GCATCPP_CIRCULAR_H

#include "AbstractTester.h"

#include "../graph/Graph.h"

class Circular : public AbstractTester {
public:
    virtual bool test(AbstractGenCode *code);

    std::vector<graph::Graph > get_circles();
    std::vector<graph::Graph > get_longest_path();

protected:
    std::vector<graph::Graph> circle;
    std::vector<graph::Graph> longest_path;
    unsigned int longest_path_size;

    void add_circle(graph::Graph);
    void add_longest_path(graph::Graph);

    virtual bool is_circular(AbstractGenCode *code);

    bool rec_is_circular(AbstractGenCode* ,
                         std::vector<unsigned int>,
                         graph::Graph,
                         std::string,
                         unsigned int);
};


#endif //GCATCPP_CIRCULAR_H