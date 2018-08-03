require(igraph)

plot_graph <- function(vertices_edges_list, red_edges={}, green_edges={}) {
  g <- igraph::make_empty_graph();
  vertices_vec = vertices_edges_list[[2]]
  edges_vec = vertices_edges_list[[1]]
  if(length(vertices_vec) > 0) {
    g <- g +  igraph::vertex(vertices_vec)
    
    g <- g +  igraph::edges(edges_vec, color="darkgray")
    if(length(red_edges) != 0) {
      g <- g +  igraph::edges(red_edges, color="red")
    }
    if(length(green_edges) != 0) {
      g <- g +  igraph::edges(green_edges, color="green")
    }
    plot(g)
  }
}

#' Plots generic graph for a sequence
#' 
#' The following definition relates a directed graph to
#' any n-nucleotide code. Recall from graph theory (Clark and Holton, 1991) that a graph G consists of
#' a finite set of vertices (nodes) V and a finite set of edges E. Here, an edge is a set \{v,w\} of vertices
#' from V . The graph is called oriented if the edges have an orientation, i.e. edges are considered to be
#' ordered pairs [v,w] in this case.\cr
#' Definition 2.1. Let X Bn be an n-nucleotide code (n 2 N). We define a directed graph G(X) =
#' (V (X),E(X)) with set of vertices V (X) and set of edges E(X) as follows:
#' N-NUCLEOTIDE CIRCULAR CODES IN GRAPH THEORY 5\cr
#' V (X) = \{N1...Ni,Ni+1...Nn : N1N2N3...Nn in X, 0 < i < n\}\cr
#' E(X) = \{[N1...Ni,Ni+1...Nn] : N1N2N3...Nn in X, 0 < i < n\}\cr
#' The graph G(X) is called the representing graph of X or the graph associated to X.\cr
#' Basically, the graph G(X) associated to a code X interprets n-nucleotide words from X in (n−1) ways
#' by pairs of i-nucleotides and (n-i)-nucleotides for 0 < i < n.\cr
#' \emph{2007 E. FIMMEL, C. J. MICHEL, AND L. STRÜNGMANN. N-nucleotide circular codes in graph theory}
#'
#' @param seq A gene sequence.
#' @param word_lenth length of the codons.
#' @examples
#' seq_plot_graph("ACGCGA", 3)
#' 
#' @export 
seq_plot_graph <- function(seq, word_length) {
  vertices_edges_list = seq_get_edges_and_vertices_of_gen_graph(seq, word_length=3)
  plot_graph(vertices_edges_list)
}

#' Plots generic graph for a code
#' 
#' The following definition relates a directed graph to
#' any n-nucleotide code. Recall from graph theory (Clark and Holton, 1991) that a graph G consists of
#' a finite set of vertices (nodes) V and a finite set of edges E. Here, an edge is a set \{v,w\} of vertices
#' from V . The graph is called oriented if the edges have an orientation, i.e. edges are considered to be
#' ordered pairs [v,w] in this case.\cr
#' Definition 2.1. Let X Bn be an n-nucleotide code (n 2 N). We define a directed graph G(X) =
#' (V (X),E(X)) with set of vertices V (X) and set of edges E(X) as follows:
#' N-NUCLEOTIDE CIRCULAR CODES IN GRAPH THEORY 5\cr
#' V (X) = \{N1...Ni,Ni+1...Nn : N1N2N3...Nn in X, 0 < i < n\}\cr
#' E(X) = \{[N1...Ni,Ni+1...Nn] : N1N2N3...Nn in X, 0 < i < n\}\cr
#' The graph G(X) is called the representing graph of X or the graph associated to X.\cr
#' Basically, the graph G(X) associated to a code X interprets n-nucleotide words from X in (n−1) ways
#' by pairs of i-nucleotides and (n-i)-nucleotides for 0 < i < n.\cr
#' \emph{2007 E. FIMMEL, C. J. MICHEL, AND L. STRÜNGMANN. N-nucleotide circular codes in graph theory}
#'
#' @param code the code as a vector
#' @examples
#' code_plot_graph(c("ACG", "CGA"))
#' 
#' @export 
code_plot_graph <- function(code, showCircles=FALSE, show_longest_path=FALSE) {
  vertices_edges_list = code_get_edges_and_vertices_of_gen_graph(code)
  circels_vertices_edges_list = {}
  path_vertices_edges_list = {}
  if(showCircles) {
    circels_vertices_edges_list = code_prepare_plot_all_circles(code)[[1]]
  }
  if(show_longest_path) {
    path_vertices_edges_list = code_prepare_plot_longest_path(code)[[1]]
  }
  plot_graph(vertices_edges_list, circels_vertices_edges_list, path_vertices_edges_list)
}

#' @export 
code_plot_circels <- function(code) {
  vertices_edges_list = code_prepare_plot_all_circles(code)
  plot_graph(vertices_edges_list)
}

#' @export 
seq_plot_circels <- function(seq, word_length=3) {
  vertices_edges_list = seq_prepare_plot_all_circles(seq, word_length)
  plot_graph(vertices_edges_list)
}

#' @export 
code_plot_longest_path <- function(code) {
  vertices_edges_list = code_prepare_plot_longest_path(code)
  plot_graph(vertices_edges_list)
}

#' @export 
seq_plot_longest_path <- function(seq, word_length=3) {
  vertices_edges_list = seq_prepare_plot_longest_path(seq, word_length)
  plot_graph(vertices_edges_list)
}