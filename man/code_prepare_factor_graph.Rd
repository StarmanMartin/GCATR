% Generated by roxygen2: do not edit by hand
% Please edit documentation in R/RcppExports.R
\name{code_prepare_factor_graph}
\alias{code_prepare_factor_graph}
\title{Factors edges and vertices of an representing graph of a circular code}
\usage{
code_prepare_factor_graph(
  code,
  show_cycles = FALSE,
  show_longest_path = FALSE,
  tuple_length = -55555L
)
}
\arguments{
\item{code}{is either a string vector or a string. It can be a DNA or RNA sequence.}

\item{show_cycles}{A bool value. If true the all edges which are part of a cycle are colored red.}

\item{show_longest_path}{A bool value. If true the all edges part of the longest path are colored blue.}

\item{tuple_length}{if code is a sequence, length is the tuple length of the code.}
}
\value{
List: Edges and vertices of an graph representing a circular code.
}
\description{
This function factors the set of edges and the set of vertices of an representing graph of a circular code.
This sets can be used to construct the graph. To get a graph object use \link{code_factor_graph}.
The following definition describes a directed graph to an n-nucleotide code.
Recall from graph theory (Clark and Holton, 1991) that a graph G consists of
a finite set of vertices (nodes) V and a finite set of edges E. Here, an edge is a set \{v,w\} of vertices
from V . The graph is called oriented if the edges have an orientation, i.e. edges are considered to be
ordered pairs [v,w] in this case.\cr
Definition 2.1. Let X Bn be an n-nucleotide code (n 2 N). We define a directed graph G(X) =
(V (X),E(X)) with set of vertices V (X) and set of edges E(X) as follows:
N-NUCLEOTIDE CIRCULAR CODES IN GRAPH THEORY 5\cr
V (X) = \{N1...Ni,Ni+1...Nn : N1N2N3...Nn in X, 0 < i < n\}\cr
E(X) = \{[N1...Ni,Ni+1...Nn] : N1N2N3...Nn in X, 0 < i < n\}\cr
The graph G(X) is called the representing graph of X or the graph associated to X.\cr
Basically, the graph G(X) associated to a code X interprets n-nucleotide words from X in (n−1) ways
by pairs of i-nucleotides and (n-i)-nucleotides for 0 < i < n.\cr
\emph{2007 E. FIMMEL, C. J. MICHEL, AND L. STRÜNGMANN. N-nucleotide circular codes in graph theory}
}
\examples{
code_prepare_factor_graph(c("ACG", "CAG"), TRUE, TRUE)
code_prepare_factor_graph("ACGCAG", tuple_length=3, show_cycles=TRUE, show_longest_path=TRUE)
code_prepare_factor_graph("ACG CAG", TRUE, TRUE)

}
