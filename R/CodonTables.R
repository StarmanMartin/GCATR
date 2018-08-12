factor_rna_codon_table <- function(rna_codon_list) {
  row_namse=rep("---", 16)
  col_namse=rep("---", 4)
  row_idx = 1;
  col_idx = 1;
  for(first in get_rna_bases()) {
    col_namse[col_idx] = first
    col_idx = col_idx + 1
    for(second in get_rna_bases()) {
      row_namse[row_idx] = paste(first, second, sep="_")
      row_idx = row_idx + 1;
    }
  }
  A <- matrix(rna_codon_list, nrow=4*4,  ncol=4, byrow = TRUE)
  dimnames(A) = list(row_namse, col_namse)
  return(A)      
  
}
#' A Matrix of all RNA codons
#'
#' get_rna_codon_table will generate a 4*16 table based on the following list:\cr
#' UUU UCU UAU UGU\cr
#  UUC UCC UAC UGC\cr
#  UUA UCA UAA UGA\cr
#  UUG UCG UAG UGG\cr
#  CUU CCU CAU CGU\cr
#  CUC CCC CAC CGC\cr
#  CUA CCA CAA CGA\cr
#  CUG CCG CAG CGG\cr
#' AUU ACU AAU AGU\cr
#  AUC ACC AAC AGC\cr
#  AUA ACA AAA AGA\cr
#  AUG ACG AAG AGG\cr
#  GUU GCU GAU GGU\cr
#  GUC GCC GAC GGC\cr
#  GUA GCA GAA GGA\cr
#  GUG GCG GAG GGG
#'
#' @return A matrix object with all RNA codons
#' @examples
#' res <- get_rna_codon_table()
#'
#' @export
get_rna_codon_table <- function() {
  return(factor_rna_codon_table(get_rna_codon_list()))      
  
}

#' A List of all RNA codons
#'
#' get_rna_codon_list will generate the following list:\cr
#' UUU UCU UAU UGU UUC UCC UAC UGC UUA UCA UAA UGA UUG UCG UAG UGG CUU CCU CAU CGU CUC CCC CAC CGC CUA CCA CAA CGA CUG CCG CAG CGG
#' AUU ACU AAU AGU AUC ACC AAC AGC AUA ACA AAA AGA AUG ACG AAG AGG GUU GCU GAU GGU GUC GCC GAC GGC GUA GCA GAA GGA GUG GCG GAG GGG
#'
#' @return A vector object with all RNA codons
#' @examples
#' res <- get_rna_codon_list()
#'
#' @export
get_rna_codon_list <- function() {
  result=rep("---", 64)
  idx = 1;
  for(first in get_rna_bases()) {
    for(second in get_rna_bases()) {
      for(third in get_rna_bases()) {
      result[idx] = paste(first, third, second, sep="")
        idx = idx + 1
      }
    }
  }
  
  return(result)
}