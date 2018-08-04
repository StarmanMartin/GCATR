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


TEST(GraphTest, ConstructorEdgeTest) {
    graph::Graph g;
    StdGenCode c({"ACG", "CGT"});
    g.parse_code(c);

    std::vector<graph::Edge> v = generate_edge_vec({"AC", "G", "A", "CG", "CG", "T", "C", "GT"});

    test_help::test_equal_vector<graph::Edge>(g.get_edges(), v);
}

TEST(GraphTest, EdgeTest) {
    graph::Graph g = generate_graph_for_code({"ACG", "CGT"});

    std::vector<graph::Edge> v = generate_edge_vec({"AC", "G", "A", "CG", "CG", "T", "C", "GT"});

    test_help::test_equal_vector<graph::Edge>(g.get_edges(), v);
}


TEST(GraphTest, VertexTest) {
    graph::Graph g = generate_graph_for_code({"ACG", "CGT"});

    std::vector<graph::Vertex> v = generate_vertex_vec({"CG", "AC", "GT", "G", "A", "C", "T"});

    test_help::test_equal_vector<graph::Vertex>(g.get_vertices(), v);
}

TEST(GraphTest, CompareTest) {
    graph::Graph g = generate_graph_for_code({"ACG", "CGT"});

    graph::Graph g2 = generate_graph_for_code({"ACG", "CGT"});

    EXPECT_TRUE(g.compare(g2) == 0);

    g2 = generate_graph_for_code({"CGT", "ACG"});

    EXPECT_TRUE(g.compare(g2) == 0);

    g2 = generate_graph_for_code({"CGT", "ATG"});

    EXPECT_FALSE(g.compare(g2) == 0);
}

TEST(GraphTest, RemoveEdgeTest) {
    graph::Graph g = generate_graph_for_code({"ACG"});

    graph::Graph g2;
    g2.add_vertices("A", "CG");

    std::vector<graph::Edge> v = generate_edge_vec({"AC", "G"});

    test_help::test_equal_vector<graph::Edge>(g.remove_edges(g2), v);
}