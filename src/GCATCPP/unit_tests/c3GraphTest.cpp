//
// Created by Martin on 18.07.2018.
//

#include <memory>

#include "test_utils.cpp"
#include "../codes/StdGenCode.h"
#include "../codes/Alphabet.h"
#include "../graph/C3Graph.h"
#include "../graph/Vertex.h"
#include "../graph/Edge.h"


std::vector<graph::Vertex> c3_generate_vertex_vec(std::vector<std::string> vertices, std::string alpha) {
    Alphabet alphabet(alpha);
    std::vector<graph::Vertex> v;
    for (auto w : vertices) {
        v.push_back(graph::Vertex(w, alphabet));
    }

    return v;
}

std::vector<graph::Edge> c3_generate_edge_vec(std::vector<std::string> v, std::string alpha) {
    Alphabet alphabet(alpha);
    std::vector<graph::Edge> e;
    for (int i = 0; i < v.size(); i += 2) {
        std::shared_ptr<graph::Vertex> from_ptr = std::make_shared<graph::Vertex>(v[i], alphabet);
        std::shared_ptr<graph::Vertex> to_ptr = std::make_shared<graph::Vertex>(v[i + 1], alphabet);

        e.push_back(graph::Edge(from_ptr, to_ptr, alphabet));
    }

    return e;
}

graph::C3Graph c3_generate_graph_for_code(std::vector<std::string> c, std::string alpha) {
    Alphabet alphabet(alpha);
    graph::C3Graph g(alphabet);
    for (auto w : c) {
        g.add_word(w);
    }

    return g;
}

TEST(C3GraphTest, EdgeTest) {
    graph::C3Graph g = c3_generate_graph_for_code({"ACG", "CGT"}, "ACGT");

    std::vector<graph::Edge> v = c3_generate_edge_vec({"TC", "G", "C", "GA", "GA", "C", "G", "TC"}, "ACGT");

    test_help::test_equal_vector<graph::Edge>(g.get_c3_edges(), v);
}


TEST(C3GraphTest, VertexTest) {
    graph::C3Graph g = c3_generate_graph_for_code({"ACG", "CGT"}, "ACGT");

    std::vector<graph::Vertex> v = c3_generate_vertex_vec({"CG", "GA", "AC", "TC", "GT", "G", "A", "C", "T"}, "ACGT");

    test_help::test_equal_vector<graph::Vertex>(g.get_vertices(), v);
}

TEST(C3GraphTest, CompareTest) {
    graph::C3Graph g = c3_generate_graph_for_code({"ACG", "CGT"}, "ACGT");

    graph::C3Graph g2 = c3_generate_graph_for_code({"ACG", "CGT"}, "ACGT");

    EXPECT_TRUE(g.compare(g2) == 0);

    g2 = c3_generate_graph_for_code({"CGT", "ACG"}, "ACGT");

    EXPECT_TRUE(g.compare(g2) == 0);

    g2 = c3_generate_graph_for_code({"CGT", "ATG"}, "ACGT");

    EXPECT_FALSE(g.compare(g2) == 0);
}

TEST(C3GraphTest, RemoveEdgeTest) {
    graph::C3Graph g = c3_generate_graph_for_code({"ACG"}, "ACGT");

    graph::C3Graph g2 = c3_generate_graph_for_code({}, "ACGT");;
    g2.add_vertices("A", "CG");

    std::vector<graph::Edge> v = c3_generate_edge_vec({"AC", "G"}, "ACGT");

    test_help::test_equal_vector<graph::Edge>(g.remove_edges(g2), v);
}