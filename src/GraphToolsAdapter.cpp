#include <Rcpp.h>
#include <algorithm>

#include "GCATCPP/codes/CodeFactory.h"
#include "GCATCPP/graph/Graph.h"
#include "GCATCPP/graph/C3Graph.h"
#include "GCATCPP/miner/LongestPathMiner.h"
#include "GCATCPP/miner/CircleMiner.h"

#include "RAdapterUtils.h"


using namespace Rcpp;

std::vector<std::string> edges_to_string_vector(const std::vector<graph::Edge> &edges) {
    std::vector<std::string> res(edges.size() * 2);

    for (struct {
             unsigned int edge;
             int vertex;
         } idx = {0, 0};
         idx.edge < edges.size();
         idx.edge++, idx.vertex += 2) {
        res[idx.vertex] = edges[idx.edge].get_from()->get_label();
        res[idx.vertex + 1] = edges[idx.edge].get_to()->get_label();
    }

    return res;
}

std::vector<std::string> get_edges_of_gen_graph(const graph::Graph &g) {
    auto edges = g.get_edges();
    return edges_to_string_vector(edges);
}

std::vector<std::string> get_vertices_of_gen_graphconst(const graph::Graph &g) {
    auto vertices = g.get_vertices();
    std::vector<std::string> res(vertices.size());

    for (int idx = 0; idx < vertices.size(); idx++) {
        res[idx] = vertices[idx].get_label();
    }

    return res;
}

Rcpp::List generate_named_vertices_and_edges_list(const graph::Graph &g) {
    std::vector<std::vector<std::string>> edges_and_vertices = {
            get_edges_of_gen_graph(g),
            get_vertices_of_gen_graphconst(g)
    };

    auto r_list = RAdapterUtils::as_R_matrix(edges_and_vertices);
    r_list.names() = CharacterVector::create("edges", "vertices");

    return r_list;
}

Rcpp::List prepare_factor_all_circles(AbstractCode &gc) {
    graph::Graph graph_circular = miner::CircleMiner::mine_path_as_graph(&gc);
    return generate_named_vertices_and_edges_list(graph_circular);
}

Rcpp::List prepare_factor_longest_path(AbstractCode &gc) {
    graph::Graph graph_circular = miner::LongestPathMiner::mine_path_as_graph(&gc);
    return generate_named_vertices_and_edges_list(graph_circular);
}

Rcpp::List prepare_factor_graph(AbstractCode &a, bool show_circles, bool show_longest_path) {
    graph::Graph g(a);
    std::vector<std::string> circular_path;
    std::vector<std::string> longest_path;
    if (show_circles) {
        graph::Graph graph_circular = miner::CircleMiner::mine_path_as_graph(&a);
        circular_path = get_edges_of_gen_graph(graph_circular);
        g.remove_edges(graph_circular);
    }

    if (show_longest_path) {
        graph::Graph graph_l_path = miner::LongestPathMiner::mine_path_as_graph(&a);
        longest_path = get_edges_of_gen_graph(graph_l_path);
        g.remove_edges(graph_l_path);
    }

    std::vector<std::vector<std::string>> edges_and_vertices = {
            get_edges_of_gen_graph(g),
            get_vertices_of_gen_graphconst(g),
            longest_path,
            circular_path
    };

    auto r_list = RAdapterUtils::as_R_matrix(edges_and_vertices);
    r_list.names() = CharacterVector::create("edges", "vertices", "longest_path_edges", "circular_path_edges");

    return r_list;
}


Rcpp::List prepare_factor_gen_c3graph(AbstractGenCode &gc) {
    graph::C3Graph g(gc);

    std::vector<std::vector<std::string>> edges_and_vertices = {
            get_edges_of_gen_graph(g),
            get_vertices_of_gen_graphconst(g),
            edges_to_string_vector(g.get_c3_edges())
    };

    auto r_list = RAdapterUtils::as_R_matrix(edges_and_vertices);
    r_list.names() = CharacterVector::create("edges", "vertices", "c3_edges");

    return r_list;
}

//' Factors edges and vertices of an representing C3-graph of a circular code
//'
//' This function factors the set of edges and the set of vertices of an representing graph of a circular code.
//' This sets can be used to construct the graph. To get a graph object use \link{code_factor_c3graph}.\cr
//' The difference to the standard Graph is that the edges of the shifted (circular permutated) Codes
//' of the the origin code are included as undirected edges.\cr
//' The following definition describes a directed graph to an n-nucleotide code.
//' Recall from graph theory (Clark and Holton, 1991) that a graph G consists of
//' a finite set of vertices (nodes) V and a finite set of edges E. Here, an edge is a set \{v,w\} of vertices
//' from V . The graph is called oriented if the edges have an orientation, i.e. edges are considered to be
//' ordered pairs [v,w] in this case.\cr
//' Definition 2.1. Let X Bn be an n-nucleotide code (n 2 N). We define a directed graph G(X) =
//' (V (X), EU(X) ,E(X)) with set of vertices V (X), a set of undirected edges EU(X) and set of edges E(X) as follows:
//' N-NUCLEOTIDE CIRCULAR CODES IN GRAPH THEORY 5\cr
//' V (X) = \{N1...Ni,Ni+1...N3 : N1N2N3...Nn in X, 0 < i < 3\}\cr
//' EU (X) = \{[N2,N3N1] : N1N2N3 in X\}\cr
//' E(X) = \{[N1...Ni,Ni+1...Nn] : N1N2N3 in X, 0 < i < 3\}\cr
//' The graph G(X) is called the representing graph of X or the graph associated to X.\cr
//' Basically, the graph G(X) associated to a code X interprets n-nucleotide words from X in (n−1) ways
//' by pairs of i-nucleotides and (n-i)-nucleotides for 0 < i < n.\cr
//' \emph{2007 E. FIMMEL, C. J. MICHEL, AND L. STRÜNGMANN. N-nucleotide circular codes in graph theory}
//'
//' @param code is either a string vector or a string. It can be a DNA or RNA sequence.
//' @param tuple_length if code is a sequence, length is the tuple length of the code.
//'
//' @return List: Edges and vertices of an C3-graph representing a circular code.
//'
//' @examples
//' code_prepare_factor_gen_c3graph(c("ACG", "CAG"))
//' code_prepare_factor_gen_c3graph("ACGCAG", tuple_length=3)
//' code_prepare_factor_gen_c3graph("ACG CAG")
//'
// [[Rcpp::export]]
Rcpp::List code_prepare_factor_gen_c3graph(StringVector code, int tuple_length = -1) {
    auto code_vec = RAdapterUtils::as_cpp_string_vector(code);
    auto gc = CodeFactory::rFactorGenCode(code_vec, tuple_length);
    return prepare_factor_gen_c3graph(*gc);

}

//' Factors edges and vertices of an representing graph of a circular code
//' 
//' This function factors the set of edges and the set of vertices of an representing graph of a circular code.
//' This sets can be used to construct the graph. To get a graph object use \link{code_factor_graph}.
//' The following definition describes a directed graph to an n-nucleotide code.
//' Recall from graph theory (Clark and Holton, 1991) that a graph G consists of
//' a finite set of vertices (nodes) V and a finite set of edges E. Here, an edge is a set \{v,w\} of vertices
//' from V . The graph is called oriented if the edges have an orientation, i.e. edges are considered to be
//' ordered pairs [v,w] in this case.\cr
//' Definition 2.1. Let X Bn be an n-nucleotide code (n 2 N). We define a directed graph G(X) =
//' (V (X),E(X)) with set of vertices V (X) and set of edges E(X) as follows:
//' N-NUCLEOTIDE CIRCULAR CODES IN GRAPH THEORY 5\cr
//' V (X) = \{N1...Ni,Ni+1...Nn : N1N2N3...Nn in X, 0 < i < n\}\cr
//' E(X) = \{[N1...Ni,Ni+1...Nn] : N1N2N3...Nn in X, 0 < i < n\}\cr
//' The graph G(X) is called the representing graph of X or the graph associated to X.\cr
//' Basically, the graph G(X) associated to a code X interprets n-nucleotide words from X in (n−1) ways
//' by pairs of i-nucleotides and (n-i)-nucleotides for 0 < i < n.\cr
//' \emph{2007 E. FIMMEL, C. J. MICHEL, AND L. STRÜNGMANN. N-nucleotide circular codes in graph theory}
//'
//' @param code is either a string vector or a string. It can be a DNA or RNA sequence.
//' @param show_cycles A bool value. If true the all edges which are part of a cycle are colored red.
//' @param show_longest_path A bool value. If true the all edges part of the longest path are colored blue.
//' @param tuple_length if code is a sequence, length is the tuple length of the code.
//'
//' @return List: Edges and vertices of an graph representing a circular code.
//'
//' @examples
//' code_prepare_factor_graph(c("ACG", "CAG"), TRUE, TRUE)
//' code_prepare_factor_graph("ACGCAG", tuple_length=3, show_cycles=TRUE, show_longest_path=TRUE)
//' code_prepare_factor_graph("ACG CAG", TRUE, TRUE)
//' 
// [[Rcpp::export]]
Rcpp::List code_prepare_factor_graph(StringVector code, bool show_cycles = false, bool show_longest_path = false, int tuple_length = -1) {
    auto code_vec = RAdapterUtils::as_cpp_string_vector(code);
    Rcpp::Rcout << code_vec.size() << " - " << tuple_length << "\n";
    auto gc = CodeFactory::rFactor(code_vec, tuple_length);
    return prepare_factor_graph(*gc, show_cycles, show_longest_path);
}


//' Returns a list, with only the cycles in the graph of a circular code.
//' 
//' This function is based on the represent graph of a circular code (see \link{code_prepare_factor_graph}).
//' The function only returns a list of edges and vertices. To get a graph object use \link{code_factor_cycle}.
//' The function checks if the code is circular. If the code is not circular the functions returns all cycles in the representing graph.
//' \emph{2007 Christian MICHEL. CIRCULAR CODES IN GENES}
//'
//' @param code is either a string vector or a string. It can be a DNA or RNA sequence.
//' @param tuple_length if code is a sequence, length is the tuple length of the code.
//'
//' @return List: Edges and vertices of only the cycles of an graph representing a circular code.
//'
//' @examples
//' code_prepare_factor_all_cycle(c("ACG", "CAG"))
//' code_prepare_factor_all_cycle("ACGCAG", tuple_length=3)
//' code_prepare_factor_all_cycle("ACG CAG")
//' 
// [[Rcpp::export]]
Rcpp::List code_prepare_factor_all_cycle(StringVector code, int tuple_length = -1) {
    auto code_vec = RAdapterUtils::as_cpp_string_vector(code);
    auto gc = CodeFactory::rFactor(code_vec, tuple_length);
    return prepare_factor_all_circles(*gc);
}


//' Returns a list, with only the longest path(s) in the graph of a circular code.
//'
//' This function is based on the represent graph of a circular code (see \link{code_prepare_factor_graph}).
//' The function only returns a list of edges and vertices. To get a graph object use \link{code_factor_longest_path}.
//' The function checks if the code is circular. If the code is not circular the functions returns the logest paths.
//' \emph{2007 Christian MICHEL. CIRCULAR CODES IN GENES}
//'
//' @param code A vertor with codons.' @param length if code is a sequence, length is the tuple length of the code.
//' @param tuple_length if code is a sequence, length is the tuple length of the code.
//'
//' @return List: Edges and vertices of only the longest path of an graph representing a circular code.
//'
//' @examples
//' code_prepare_factor_longest_path(c("ACG", "CAG"))
//' code_prepare_factor_longest_path("ACGCAG", tuple_length=3)
//' code_prepare_factor_longest_path("ACG CAG")
//' 
// [[Rcpp::export]]
Rcpp::List code_prepare_factor_longest_path(StringVector code, int tuple_length = -1) {
    auto code_vec = RAdapterUtils::as_cpp_string_vector(code);
    auto gc = CodeFactory::rFactor(code_vec, tuple_length);
    return prepare_factor_longest_path(*gc);
}