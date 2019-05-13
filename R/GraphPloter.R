factor_graph <- function(vertices_edges_list) {
  g <- igraph::make_empty_graph();
  vertices_vec = vertices_edges_list$vertices
  edges_vec = vertices_edges_list$edges
  if(length(vertices_vec) > 0) {
    g <- g +  igraph::vertex(vertices_vec)
    
    g <- g +  igraph::edges(edges_vec, color="darkgray")
    if(!is.null(vertices_edges_list$circular_path_edges)) {
      g <- g +  igraph::edges(vertices_edges_list$circular_path_edges, color="red")
    }
    if(!is.null(vertices_edges_list$longest_path_edges)) {
      g <- g +  igraph::edges(vertices_edges_list$longest_path_edges, color="green")
    }
    if(!is.null(vertices_edges_list$c3_edges)) {
      g <- g +  igraph::edges(vertices_edges_list$c3_edges, color="black",directed=FALSE)
    }

    return(g)
  }
}

#' Prepares a R igraph object.
#' 
#' This function factors a igraph (<http://igraph.org/r/>) object of an representing graph of a circular code.
#' The following definition describes a directed graph to an n-nucleotide code.
#' Recall from graph theory (Clark and Holton, 1991) that a graph G consists of
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
#' @param code is either a string vector or a string.
#' @param show_cycles A bool value. If true the all edges which are part of a cycle are colored red.
#' @param show_longest_path A bool value. If true the all edges part of the longest path are colored blue.
#' @param tuple_length if code is a sequence, length is the tuple length of the code.
#'
#' @return A igraph (<http://igraph.org/r/>) object: A graph representing a circular code.
#'
#' @examples
#' G <- code_factor_graph(c("ACG", "CAG"), TRUE, TRUE)
#' G <- code_factor_graph("ACGCAG", tuple_length=3, show_cycles=TRUE, show_longest_path=TRUE)
#' G <- code_factor_graph("ACG CAG", TRUE, TRUE)
#' plot(G)
#' 
#' @export 
code_factor_graph <- function(code, show_cycles=FALSE, show_longest_path=FALSE, tuple_length=-1) {
  vertices_edges_list = code_prepare_factor_graph(code, show_cycles = show_cycles, show_longest_path = show_longest_path, tuple_length = tuple_length)
  return(factor_graph(vertices_edges_list))
}

#' Factors an representing C3-graph of a circular code
#'
#' This function factors a igraph (<http://igraph.org/r/>) object of an representing graph of a circular code.
#' The difference to the standard Graph is that the edges of the shifted (circular permutated) Codes
#' of the the origin code are included as undirected edges.\cr
#' The following definition describes a directed graph to an n-nucleotide code.
#' Recall from graph theory (Clark and Holton, 1991) that a graph G consists of
#' a finite set of vertices (nodes) V and a finite set of edges E. Here, an edge is a set \{v,w\} of vertices
#' from V . The graph is called oriented if the edges have an orientation, i.e. edges are considered to be
#' ordered pairs [v,w] in this case.\cr
#' Definition 2.1. Let X Bn be an n-nucleotide code (n 2 N). We define a directed graph G(X) =
#' (V (X), EU(X) ,E(X)) with set of vertices V (X), a set of undirected edges EU(X) and set of edges E(X) as follows:
#' N-NUCLEOTIDE CIRCULAR CODES IN GRAPH THEORY 5\cr
#' V (X) = \{N1...Ni,Ni+1...N3 : N1N2N3...Nn in X, 0 < i < 3\}\cr
#' EU (X) = \{[N2,N3N1] : N1N2N3 in X\}\cr
#' E(X) = \{[N1...Ni,Ni+1...Nn] : N1N2N3 in X, 0 < i < 3\}\cr
#' The graph G(X) is called the representing graph of X or the graph associated to X.\cr
#' Basically, the graph G(X) associated to a code X interprets n-nucleotide words from X in (n−1) ways
#' by pairs of i-nucleotides and (n-i)-nucleotides for 0 < i < n.\cr
#' \emph{2007 E. FIMMEL, C. J. MICHEL, AND L. STRÜNGMANN. N-nucleotide circular codes in graph theory}
#'
#' @param code is either a string vector or a string. It can be a DNA or RNA sequence.
#' @param tuple_length if code is a sequence, length is the tuple length of the code.
#'
#' @return List:  A igraph (<http://igraph.org/r/>) object: A graph representing a circular code with C3 extension..
#'
#' @examples
#' G <- code_prepare_factor_gen_c3graph(c("ACG", "CAG"))
#' G <- code_prepare_factor_gen_c3graph("ACGCAG", tuple_length=3)
#' G <- code_prepare_factor_gen_c3graph("ACG CAG")
#' plot(G)
#'
#' @export 
code_factor_c3graph <- function(code, tuple_length=-1) {
  vertices_edges_list = code_prepare_factor_gen_c3graph(code, tuple_length)
  return(factor_graph(vertices_edges_list))
}

#' Prepares a graph G(X) with only the edges which are parte of a cycle.
#'
#' Prepares a R igraph object. Extracts all circular paths of the Graph G(X).
#' If the graph shows no cycle the graph will be empty. Otherwise it returns a igraph object showing all
#' circular paths.\cr
#' \emph{2007 E. FIMMEL, C. J. MICHEL, AND L. STRÜNGMANN. N-nucleotide circular codes in graph theory}
#'
#' @return A igraph (<http://igraph.org/r/>) object: Edges and vertices of only the cycles of an graph representing a circular code.
#'
#' @param code is either a string vector or a string.
#' @param tuple_length if code is a sequence, length is the tuple length of the code.
#'
#' @examples
#' G <- code_factor_cycle(c("ACG", "CAG"))
#' G <- code_factor_cycle("ACGCAG", tuple_length=3)
#' G <- code_factor_cycle("ACG CAG")
#' plot(G)
#'
#' @export
code_factor_cycle <- function(code, tuple_length) {
  vertices_edges_list = code_prepare_factor_all_cycle(code, tuple_length)
  return(factor_graph(vertices_edges_list))
}

#' Prepares a graph G(X) with only longest paths.
#'
#' Prepares a R igraph object. Extracts all longest path of the Graph G(X).
#' If the graph shows a cycle the graph will be empty. Otherwise it returns a igraph object showing all
#' longest paths.\cr
#' \emph{2007 E. FIMMEL, C. J. MICHEL, AND L. STRÜNGMANN. N-nucleotide circular codes in graph theory}
#'
#' @param code is either a string vector or a string.
#' @param tuple_length if code is a sequence, length is the tuple length of the code.
#'
#' @return A igraph (<http://igraph.org/r/>) object: Edges and vertices of only the longest path of an graph representing a circular code.
#'
#' @examples
#' G <- code_factor_longest_path(c("ACG", "CAG"))
#' G <- code_factor_longest_path("ACGCAG", tuple_length=3)
#' G <- code_factor_longest_path("ACG CAG")
#' plot(G)
#'
#' @export
code_factor_longest_path <- function(code, tuple_length = -1) {
  vertices_edges_list = code_prepare_factor_longest_path(code, tuple_length)
  return(factor_graph(vertices_edges_list))
}


