#' @title Cluster Algorithm object
#' 
#' @description  Use this object to run more advanced BDA methods.  
#' 
#' @name CodonClusteringAlgorithm
#' 
#' @export CodonClusteringAlgorithm
loadModule(module = "CodonClusteringAlgorithm", TRUE)

#' @title Start a Cluster Algorithm object
#' 
#' @description  This function starts a cluster algorithm for a selected genetic translation table.
#' The conductance is a number which reflects the robustness of a genetic translation table.
#' The conductance the ration of the codons translating one amino acid which differ in only one position and the
#' codons translating the same amino acid but differ in more then one position.
#'
#' @param codeIdx a Number, the index of the genetic translation table. (see \link{print_all_translation_tables})
#' 
#' @name start_cluster_algorithm_of_codeidx
#' 
#' @examples 
#' # For the SGC
#' ca_obj <-  start_cluster_algorithm_of_codeidx(1)
#' 
#' @export
start_cluster_algorithm_of_codeidx <- function(codeIdx=1) {
  code_sep = GCATR::genetic_codes_by_index(codeIdx);
  code <- c()
  for(code.idx in seq_along(code_sep$codons)) {
    code <- c(code, c(code_sep$codons[code.idx], code_sep$amino_acids[code.idx]))
  }
  
  ca_obj <- new(CodonClusteringAlgorithm, code)
  return(ca_obj)
}

#' @title Start a Cluster Algorithm object
#' 
#' @description  This function starts a cluster algorithm for a BDA.
#' The conductance is a number which reflects the robustness of a genetic translation table.
#' The conductance the ration of the codons translating one amino acid which differ in only one position and the
#' codons translating the same amino acid but differ in more then one position.
#'
#' @param bda_obj BDA object (see \link{BDATools})
#' 
#' @name start_cluster_algorithm_on_bda
#' 
#' @examples 
#' # For a simple BDA
#' bda_obj<-start_bda()
#' add_rule(bda_obj, 1, 2, "C", "G", "A", "U")
#' ca_obj <-  start_cluster_algorithm_on_bda(bda_obj)
#' 
#' @export
start_cluster_algorithm_on_bda <- function(bda_obj) {
  code_sep = GCATR::run_bda(bda_obj);

  code <- c()
  for(code.idx in seq_along(code_sep$code)) {
    code <- c(code, c(code_sep$code[code.idx], code_sep$bda[code.idx]))
  }
  
  ca_obj <- new(CodonClusteringAlgorithm, code)
  return(ca_obj)
}

#' @title Start a Cluster Algorithm object
#' 
#' @description  Use this object to run more advanced methods. 
#' 
#' @name start_cluster_algorithm
#' 
#' @param code is a string vector. It is an alternating list of code words and their translations.
#' 
#' @examples 
#' # AC -> 01 & AA -> 01 &  CA -> 11 & CC -> 10
#' ca_obj <-  start_cluster_algorithm(c("AC", "01", "AA", "01", "CA", "11", "CC", "10"))
#' 
#' @export
start_cluster_algorithm <- function(code) {
  ca_obj <- new(CodonClusteringAlgorithm, code)
  return(ca_obj)
}


#' @title Add weights to a Cluster Algorithm object
#' 
#' @description ToDo
#' 
#' @name cluster_add_weights
#' 
#' @param code is a CodonClusteringAlgorithm object
#' @param pos is an integer between 1 and code tuple size
#' @param origen.base is a string. The symbol at the position of the outgoing word (optional if target.base is not set)
#' @param target.base is a string. The symbol at the position of the ingoing word (optional)
#'  
#' @examples 
#' ca_obj <-  start_cluster_algorithm(c("AC", "01", "AA", "01", "CA", "11", "CC", "10"))
#' # XC -1+4-> XA
#' cluster_add_weights(ca_obj, 2, 4, "C", "A")
#' 
#' @examples 
#' ca_obj <-  start_cluster_algorithm(c("AC", "01", "AA", "01", "CA", "11", "CC", "10"))
#' # XC -1+4-> XY
#' cluster_add_weights(ca_obj, 2, 4, "C")
#' 
#' @examples 
#' ca_obj <-  start_cluster_algorithm(c("AC", "01", "AA", "01", "CA", "11", "CC", "10"))
#' # XY -1+4-> XZ
#' cluster_add_weights(ca_obj, 2, 4)
#' 
#' @export
cluster_add_weights <- function(ca_obj, pos, weight, origen.base="", target.base="") {
  ca_obj$r_add_weight(pos, origen.base, target.base, weight)
}


#' @title Add weights´matrix to a Cluster Algorithm object
#' 
#' @description ToDo
#' 
#' @name cluster_set_matrix_weight
#' 
#' @param code is a CodonClusteringAlgorithm object
#' @param weight.matrix.list the length of the list must be equal to the tuple size of the code. Each element must be a matrix of length 
#' 
#' 
#' @examples
#' ca_obj <-  start_cluster_algorithm(c("AC", "01", "AA", "01", "CA", "11", "CC", "10"))
#' # GC -2+4-> GA
#' w.m <- generate_weight_matrix()
#' w.m[[2]]["C", "A"] <- 4
#' w.m[[1]]["G", "G"] <- 2
#' cluster_set_matrix_weight(ca_obj, w.m)
#' 
#' @export
cluster_set_matrix_weight <- function(ca_obj, weight.matrix.list) {
  tuple_size <- ca_obj$get_word_length()
  if(length(weight.matrix.list) != tuple_size) {
    stop("weight.matrix.list length must be equal to the tuple size of the code")
  }
  
  ca_obj$reset_all_weights(0)
  
  for(w.m.idx in seq_along(weight.matrix.list)) {
    w.m <- weight.matrix.list[[w.m.idx]]
    for(row.base in row.names(w.m)) {
      for(col.base in colnames(w.m)) {
        ca_obj$r_add_weight(w.m.idx, row.base, col.base, w.m[row.base, col.base])
      }
    }
  }
}

#' @title Generate a default weight matrix list
#'
#' @examples
#' # default tuple length is 3, default alphabet is RNA
#' w.m <- generate_weight_matrix()
#' # w.m is:
#' # [[1]]
#' #   T C A G
#' # T 0 1 1 1
#' # C 1 0 1 1
#' # A 1 1 0 1
#' # G 1 1 1 0
#' # 
#' # [[2]]
#' #   T C A G
#' # T 0 1 1 1
#' # C 1 0 1 1
#' # A 1 1 0 1
#' # G 1 1 1 0
#' # 
#' # [[3]]
#' #   T C A G
#' # T 0 1 1 1
#' # C 1 0 1 1
#' # A 1 1 0 1
#' # G 1 1 1 0
#'
#' @export
generate_weight_matrix <- function(ca_obj, tuple_length=3, alphabet=NULL) {
  if(is.null(alphabet)) {
    alphabet <- GCATR::get_dna_bases()
  }
  

  w.m <- matrix(1,length(alphabet), length(alphabet))
  row.names(w.m) <- alphabet
  colnames(w.m) <- alphabet
  for(elem in alphabet) {
    w.m[elem,elem] <- 0
  }
  
  
  return(rep(list(w.m),tuple_length))
}

#' @export
get_average_conductance <- function(ca_obj) {
  return(ca_obj$get_average_conductance())
}

#' @export
get_weighted_average_conductance <- function(ca_obj) {
  return(ca_obj$get_weighted_average_conductance())
}

#' @export
get_conductance_of_cluster <- function(ca_obj, cluster) {
  return(ca_obj$get_conductance_of_cluster(cluster))
}

#' @export
get_conductance_of_all_cluster <- function(ca_obj) {
  clusters <- ca_obj$get_all_cluster()
  vals <- c()
  for(cluster in clusters) {
    vals <- c(vals, ca_obj$get_conductance_of_cluster(cluster))
  }
  
  return(list(cluster=clusters, conductance=vals))
}

#' @export
get_min_conductance <- function(ca_obj) {
  return(ca_obj$get_min_conductance())
}

#' @export
get_max_conductance <- function(ca_obj) {
  return(ca_obj$get_max_conductance())
}

#' @export
cluster_reset_all_weights <- function(ca_obj, weight=1) {
  return(ca_obj$reset_all_weights(weight))
}
