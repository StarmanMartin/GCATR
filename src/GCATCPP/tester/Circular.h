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
    std::vector<graph::Edge> part_of_circular_path;
    std::set<graph::Vertex> visited_edges;
    Alphabet alphabet;

    std::vector<graph::Graph> circle;
    std::vector<graph::Graph> longest_path;
    unsigned int longest_path_size;
    bool is_quick_test;

    void add_circle(const std::vector<graph::Vertex> &circle_path);
    void add_longest_path(const std::vector<graph::Vertex> &circle_path);

    virtual bool is_circular(AbstractCode *code);

    bool rec_is_circular(graph::Graph *code, const graph::Edge &current_edge);

    static std::vector<graph::Vertex> get_path_of_path_tree(const std::vector<std::vector<graph::Vertex>> &path_tree, size_t from);

    static std::vector<int> check_if_path_is_circular(const std::vector<std::vector<graph::Vertex>> &path_tree);

    static void update_path_tree(std::vector<std::vector<graph::Vertex>> &vector);
};


#endif //GCATCPP_CIRCULAR_H
