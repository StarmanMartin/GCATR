//
// Created by Martin on 18.07.2018.
//

#include <memory>

#include "test_utils.cpp"
#include "../codes/StdGenCode.h"
#include "../graph/Graph.h"
#include "../graph/Vertex.h"
#include "../graph/Edge.h"

std::vector<graph::Vertex> generate_vertex_vec(std::vector<std::string> vertices) {
    std::vector<graph::Vertex> v;
    for (auto w : vertices) {
        v.push_back(graph::Vertex(w));
    }

    return v;
}

std::vector<graph::Edge> generate_edge_vec(std::vector<std::string> v) {
    std::vector<graph::Edge> e;
    for (int i = 0; i < v.size(); i += 2) {
        std::shared_ptr<graph::Vertex> from_ptr = std::make_shared<graph::Vertex>(v[i]);
        std::shared_ptr<graph::Vertex> to_ptr = std::make_shared<graph::Vertex>(v[i + 1]);

        e.push_back(graph::Edge(from_ptr, to_ptr));
    }

    return e;
}

graph::Graph generate_graph_for_code(std::vector<std::string> c) {
    graph::Graph g;
    for (auto w : c) {
        g.add_word(w);
    }

    return g;
}


TEST(GraphTest_$, ConstructorEdgeTestSize4) {
    graph::Graph g;
    StdGenCode c({"ACGGG", "CGTTC"});
    g.parse_code(c);

    std::vector<graph::Edge> v = generate_edge_vec({"ACGG", "G", "A", "CGGG", "CGTT", "C", "C", "GTTC","ACG", "GG", "AC", "GGG", "CGT", "TC", "CG", "TTC"});

    test_help::test_equal_vector<graph::Edge>(g.get_edges(), v);
}