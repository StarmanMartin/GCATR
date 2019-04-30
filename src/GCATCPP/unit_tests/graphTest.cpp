//
// Created by Martin on 18.07.2018.
//

#include <memory>

#include "test_utils.cpp"
#include "../codes/StdGenCode.h"
#include "../codes/CodeFactory.h"
#include "../graph/Graph.h"
#include "../graph/Vertex.h"
#include "../graph/Edge.h"
#include "../codes/Alphabet.h"

std::vector<graph::Vertex> generate_vertex_vec(std::vector<std::string> vertices, const std::string &alpha) {
    Alphabet alphabet(alpha);
    std::vector<graph::Vertex> v;
    for (const auto &w : vertices) {
        v.emplace_back(w, alphabet);
    }

    return v;
}

std::vector<graph::Edge> generate_edge_vec(std::vector<std::string> v, const std::string &alpha) {
    Alphabet alphabet(alpha);
    std::vector<graph::Edge> e;
    for (int i = 0; i < v.size(); i += 2) {
        std::shared_ptr<graph::Vertex> from_ptr = std::make_shared<graph::Vertex>(v[i], alphabet);
        std::shared_ptr<graph::Vertex> to_ptr = std::make_shared<graph::Vertex>(v[i + 1], alphabet);

        e.emplace_back(graph::Edge(from_ptr, to_ptr, alphabet));
    }

    return e;
}

graph::Graph generate_graph_for_code(std::vector<std::string> c, const std::string &alpha) {
    Alphabet alphabet(alpha);
    graph::Graph g(alphabet);
    for (const auto &w : c) {
        g.add_word(w);
    }

    return g;
}

TEST(GraphTest, ConstructorLongTest) {
    std::string code = "01010101 10101011 01010110 10101101 10110100 01101000 11010001 10100010 01000100 10001001 00010010 00100101 01001011 10010111 00101110 01011101 10111011 01110110 11101101 11011010 10110100 01101000 11010001";

    auto c = CodeFactory::factor(code);
    graph::Graph g(*c);

   EXPECT_EQ(g.get_edges().size(), 140);
}


TEST(GraphTest, ConstructorEdgeTest) {

    StdGenCode c({"ACG", "CGT"});
    graph::Graph g(c);

    std::vector<graph::Edge> v = generate_edge_vec({"AC", "G", "A", "CG", "CG", "T", "C", "GT"}, "ACGT");

    test_help::test_equal_vector<graph::Edge>(g.get_edges(), v);
}

TEST(GraphTest, EdgeTest) {
    graph::Graph g = generate_graph_for_code({"ACG", "CGT"}, "ACGT");

    std::vector<graph::Edge> v = generate_edge_vec({"AC", "G", "A", "CG", "CG", "T", "C", "GT"}, "ACGT");

    test_help::test_equal_vector<graph::Edge>(g.get_edges(), v);
}


TEST(GraphTest, VertexTest) {
    graph::Graph g = generate_graph_for_code({"ACG", "CGT"}, "ACGT");

    std::vector<graph::Vertex> v = generate_vertex_vec({"CG", "AC", "GT", "G", "A", "C", "T"}, "ACGT");

    test_help::test_equal_vector<graph::Vertex>(g.get_vertices(), v);
}

TEST(GraphTest, CompareTest) {
    graph::Graph g = generate_graph_for_code({"ACG", "CGT"}, "ACGT");

    graph::Graph g2 = generate_graph_for_code({"ACG", "CGT"}, "ACGT");

    EXPECT_TRUE(g.compare(g2) == 0);

    g2 = generate_graph_for_code({"CGT", "ACG"}, "ACGT");

    EXPECT_TRUE(g.compare(g2) == 0);

    g2 = generate_graph_for_code({"CGT", "ATG"}, "ACGT");

    EXPECT_FALSE(g.compare(g2) == 0);
}

TEST(GraphTest, RemoveEdgeTest) {
    graph::Graph g = generate_graph_for_code({"ACG"}, "ACGT");

    graph::Graph g2 = generate_graph_for_code({}, "ACGT");
    g2.add_vertices("A", "CG");

    std::vector<graph::Edge> v = generate_edge_vec({"AC", "G"}, "ACGT");

    test_help::test_equal_vector<graph::Edge>(g.remove_edges(g2), v);
}