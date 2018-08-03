#include <Rcpp.h>
#include <algorithm>

#include "GCATCPP/codes/StdGenCode.h"
#include "GCATCPP/graph/Graph.h"
#include "GCATCPP/miner/LongestPathMiner.h"
#include "GCATCPP/miner/CircleMiner.h"

#include "RAdapterUtils.h"



using namespace Rcpp;


std::vector<std::string> get_edges_of_gen_graph(const graph::Graph& g) {
  auto edges = g.get_edges();
  std::vector<std::string> res(edges.size()*2);
  
  for (struct { unsigned int edge; int vertex; } idx = {0, 0};
       idx.edge < edges.size();
       idx.edge++, idx.vertex += 2) {
    res[idx.vertex] = edges[idx.edge].get_from()->get_label();
    res[idx.vertex+1] = edges[idx.edge].get_to()->get_label();
  }
  
  return res;
}

std::vector<std::string> get_vertices_of_gen_graphconst(const graph::Graph& g) {
  auto vertices = g.get_vertices();
  std::vector<std::string> res(vertices.size());
  
  for (int idx = 0; idx < vertices.size(); idx++) {
    res[idx] = vertices[idx].get_label();
  }
  
  return res;
}

Rcpp::List generate_named_vertices_and_edges_list(const graph::Graph& g) {
  std::vector<std::vector<std::string>> edges_and_vertices = {
    get_edges_of_gen_graph(g),
    get_vertices_of_gen_graphconst(g)
  };
  
  auto r_list = RAdapterUtils::as_R_matrix(edges_and_vertices);
  r_list.names() = CharacterVector::create("edges", "vertices");
  
  return r_list;
}

Rcpp::List prepare_plot_all_circles(StdGenCode& gc) {
  graph::Graph graph_circular = miner::CircleMiner::mine_path_as_graph(&gc);
  return generate_named_vertices_and_edges_list(graph_circular);
}

Rcpp::List prepare_plot_longest_path(StdGenCode& gc) {
  graph::Graph graph_circular = miner::LongestPathMiner::mine_path_as_graph(&gc);
  return generate_named_vertices_and_edges_list(graph_circular);
}

Rcpp::List get_edges_and_vertices_of_gen_graph(StdGenCode a) {
  graph::Graph g;
  g.parse_code(a);
  return generate_named_vertices_and_edges_list(g);
}

//' Get edges of an generic graph
//' 
//' The following definition relates a directed graph to
//' any n-nucleotide code. Recall from graph theory (Clark and Holton, 1991) that a graph G consists of
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
//' @param code A vertor with codons.
//' @return List: Edges and vertices of an generic graph. If A -> CG the Letter A is followed by the string CG.
//' @examples
//' code_get_edges_of_gen_graph(c("ACG", "CAG"))
//' 
//' @export 
// [[Rcpp::export]]
Rcpp::List code_get_edges_and_vertices_of_gen_graph(StringVector code) {
  StdGenCode a(RAdapterUtils::as_cpp_string_vector(code));
  return get_edges_and_vertices_of_gen_graph(a);
}


//' Get edges of an generic graph
//' 
//' The following definition relates a directed graph to
//' any n-nucleotide code. Recall from graph theory (Clark and Holton, 1991) that a graph G consists of
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
//' @param seq a nucleotide sequence.
//' @param word_length the length of the word.
//' @return List: Edges and vertices of an generic graph. If A -> CG the Letter A is followed by the string CG.
//' @examples
//' code_get_edges_of_gen_graph(c("ACG", "CAG"))
//' 
//' @export 
// [[Rcpp::export]]
Rcpp::List seq_get_edges_and_vertices_of_gen_graph(std::string seq, int word_length) {
  StdGenCode a(seq, word_length);
  return get_edges_and_vertices_of_gen_graph(a);
}




//' Returns a list of circles as vectors.
//' 
//' The function checks if the code is circular. If the code is not circular the functions returns all circles. 
//' \emph{2007 Christian MICHEL. CIRCULAR CODES IN GENES}
//'
//' @param code A vertor with codons.
//' @examples
//' code_prepare_plot_all_circles(c("ACG", "CAG"))
//' 
// [[Rcpp::export]]
Rcpp::List code_prepare_plot_all_circles(StringVector code) {
  StdGenCode gc(RAdapterUtils::as_cpp_string_vector(code));
  return prepare_plot_all_circles(gc);
}

//' Returns a list of circles as vectors.
//' 
//' The function checks if the code is circular. If the code is not circular the functions returns all circles. 
//' \emph{2007 Christian MICHEL. CIRCULAR CODES IN GENES}
//'
//' @param seq a nucleotide sequence.
//' @param word_length the length of the word.
//' @examples
//' seq_prepare_plot_all_circles("ACGCAG", 3)
//' 
// [[Rcpp::export]]
Rcpp::List seq_prepare_plot_all_circles(std::string seq, int word_length) {
  StdGenCode gc(seq, word_length);
  return prepare_plot_all_circles(gc);
}


//' Returns a list of circles as vectors.
//' 
//' The function checks if the code is circular. If the code is not circular the functions returns all circles. 
//' \emph{2007 Christian MICHEL. CIRCULAR CODES IN GENES}
//'
//' @param code A vertor with codons.
//' @examples
//' code_prepare_plot_all_circles(c("ACG", "CAG"))
//' 
// [[Rcpp::export]]
Rcpp::List code_prepare_plot_longest_path(StringVector code) {
  StdGenCode gc(RAdapterUtils::as_cpp_string_vector(code));
  return prepare_plot_longest_path(gc);
}

//' Returns a list of circles as vectors.
//' 
//' The function checks if the code is circular. If the code is not circular the functions returns all circles. 
//' \emph{2007 Christian MICHEL. CIRCULAR CODES IN GENES}
//'
//' @param seq a nucleotide sequence.
//' @param word_length the length of the word.
//' @examples
//' seq_prepare_plot_all_circles("ACGCAG", 3)
//' 
// [[Rcpp::export]]
Rcpp::List seq_prepare_plot_longest_path(std::string seq, int word_length) {
  StdGenCode gc(seq, word_length);
  return prepare_plot_longest_path(gc);
}