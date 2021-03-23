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
#' @description  Use this object to run more advanced methods. 
#' 
#' @name start_cluster_algorithm
#' 
#' @param code is a string vector. It is an alternating list of code words and their translations.
#' 
#' @example 
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
#' 
#' @example 
#' ca_obj <-  start_cluster_algorithm(c("AC", "01", "AA", "01", "CA", "11", "CC", "10"))
#' # XC -1+4-> XA
#' cluster_add_weights(ca_obj, 2, 4, "C", "A")
#' 
#' @example 
#' ca_obj <-  start_cluster_algorithm(c("AC", "01", "AA", "01", "CA", "11", "CC", "10"))
#' # XC -1+4-> XY
#' cluster_add_weights(ca_obj, 2, 4, "C")
#' 
#' @example 
#' ca_obj <-  start_cluster_algorithm(c("AC", "01", "AA", "01", "CA", "11", "CC", "10"))
#' # XY -1+4-> XZ
#' cluster_add_weights(ca_obj, 2, 4)
#' 
#' @export
cluster_add_weights <- function(ca_obj, pos, weight, origen.base="", target.base="") {
  ca_obj$r_add_weight(pos, origen.base, target.base, weight)
}