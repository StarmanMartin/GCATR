//
// Created by Martin on 12.07.2018.
//

#ifndef GCATCPP_CIRCULAR_H
#define GCATCPP_CIRCULAR_H

#include "AbstractTester.h"

#include "../graph/Graph.h"

class Circular : public AbstractTester {
public:
    bool test(AbstractCode *code) override;


    std::vector<graph::Graph > get_circles(AbstractCode *code);
    std::vector<graph::Graph > get_longest_path(AbstractCode *code);

protected:
    std::vector<graph::Graph> circle;
    std::vector<graph::Graph> longest_path;
    unsigned int longest_path_size;
    bool is_quick_test;

    void add_circle(graph::Graph);
    void add_longest_path(graph::Graph);

    virtual bool is_circular(AbstractCode *code);

    bool rec_is_circular(AbstractCode* ,
                         std::vector<unsigned int>,
                         graph::Graph,
                         std::string,
                         unsigned int);
};


#endif //GCATCPP_CIRCULAR_H
