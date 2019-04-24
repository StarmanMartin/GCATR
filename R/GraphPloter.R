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
#' The funciton prepares graph G(X) object for a code. The following definition relates a directed graph to
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
#' @seealso [seq_factor_graph(seq, word_length)] for sequences
#'
#' @param code is either a string vector or a string. It can be a DNA or RNA sequence.
#' @param show_cycles A bool value. If true the all edges which are part of a cycle are colored red.
#' @param show_longest_path A bool value. If true the all edges part of the longest path are colored blue.
#' @param tuple_length if code is a sequence, length is the tuple length of the code.
#'
#' @return A igraph (<http://igraph.org/r/>) object: An graph representing a circular code.
#'
#' @examples
#' G <- code_factor_graph(c("ACG", "CAG"), TRUE, TRUE)
#' G <- code_factor_graph("ACGCAG", tuple_length=3, show_cycles=TRUE, show_longest_path=TRUE)
#' G <- code_factor_graph("ACG CAG", TRUE, TRUE)

#' plot(G)
#' 
#' @export 
code_factor_graph <- function(code, show_cycles=FALSE, show_longest_path=FALSE, tuple_length=-1) {
  vertices_edges_list = code_prepare_factor_gen_graph(code, show_cycles = show_cycles, show_longest_path = show_longest_path, tuple_length = tuple_length)
  return(factor_graph(vertices_edges_list))
}

#' Prepares a graph G(X) object with C3 extension.
#'
#' Prepares a R igraph object. Extents the Graph G(X) from code_factor_graph by the so called C3 edges.
#' If the graph shows a cycle with alternating edges of the C3 edges and the usual edges follows that the
#' at least one circular permutation of the code is not a circular code. Only works for word length of 3.\cr
#' \emph{2007 E. FIMMEL, C. J. MICHEL, AND L. STRÜNGMANN. N-nucleotide circular codes in graph theory}
#'
#' @seealso [seq_factor_c3graph(seq)] for sequences
#'
#' @param code is either a string vector or a string. It can be a DNA or RNA sequence.
#' @param tuple_length if code is a sequence, length is the tuple length of the code.
#'
#' @return List:  A igraph (<http://igraph.org/r/>) object: An graph representing a circular code with C3 extension..
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

#' Prepares a graph G(X) with only those edges which are parte of a cycle.
#'
#' Prepares a R igraph object. Extracts all circular paths of the Graph G(X).
#' If the graph shows no cycle the graph will be empty. Otherwise it returns a igraph object showing all
#' circular paths.\cr
#' \emph{2007 E. FIMMEL, C. J. MICHEL, AND L. STRÜNGMANN. N-nucleotide circular codes in graph theory}
#'
#' @seealso [seq_factor_circles(seq)] for sequence, [code_get_all_circle_as_vector()] for the results as vector
#'
#' @return A igraph (<http://igraph.org/r/>) object: Edges and vertices of only the cycles of an graph representing a circular code.
#'
#' @param code is either a string vector or a string. it can be a DNA or RNA sequence.
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
#' @seealso [code_factor_circles(code)] for code, [code_get_all_longest_path_as_vector()] for the results as vector
#'
#' @param code is either a string vector or a string. it can be a DNA or RNA sequence.
#' @param tuple_length if code is a sequence, length is the tuple length of the code.
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


#' @export
test_pdf_reder <- function() {
  require(knitr);
  require(rmarkdown);
  
  dirname <- "CircularCodeReport";
  idx <- 0;
  while (dir.exists(dirname)) {
    idx <- idx + 1;
    dirname <- paste0("CircularCodeReport_", idx, collapse = NULL)
  }
  
  startwd <- getwd();
  dir.create(dirname);
  setwd(dirname);
  
  (template_file <- system.file("data", "CircularCodeReport.Rmd", package = "GCATR"))
  output_t="CircularCodeReport.md"
  
  
  knit(template_file, output = output_t, code="ACG CGA"); 
  render(output_t, output_format = "pdf_document")
  
  setwd(startwd);
}

