factor_dna_codon_table <- function(dna_codon_list) {
  return(p_factor_codon_table(dna_codon_list, get_dna_bases()))
}

factor_rna_codon_table <- function(rna_codon_list) {
  return(p_factor_codon_table(rna_codon_list, get_rna_bases()))
}


p_factor_codon_table <- function(rna_codon_list, bases) {
  row_namse=rep("---", 16)
  col_namse=rep("---", 4)
  row_idx = 1;
  col_idx = 1;
  for(first in bases) {
    col_namse[col_idx] = first
    col_idx = col_idx + 1
    for(second in bases) {
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

#' A List of all DNA codons
#'
#' get_dna_codon_list will generate the following list:\cr
#' TTT TCT TAT TGT TTC TCC TAC TGC TTA TCA TAA TGA TTG TCG TAG TGG CTT CCT CAT CGT CTC CCC CAC CGC CTA CCA CAA CGA CTG CCG CAG CGG
#' ATT ACT AAT AGT ATC ACC AAC AGC ATA ACA AAA AGA ATG ACG AAG AGG GTT GCT GAT GGT GTC GCC GAC GGC GTA GCA GAA GGA GTG GCG GAG GGG
#'
#' @return A vector object with all DNA codons
#' @examples
#' res <- get_dna_codon_list()
#'
#' @export
get_dna_codon_list <- function() {
  return(code_transform_tuples("U", "T", get_rna_codon_list()))
}
#' A Matrix of all DNA codons
#'
#' get_dna_codon_table will generate a 4*16 table based on the following list:\cr
#'  TTT TCT TAT TGT\cr
#'  TTC TCC TAC TGC\cr
#'  TTA TCA TAA TGA\cr
#'  TTG TCG TAG TGG\cr
#'  CTT CCT CAT CGT\cr
#'  CTC CCC CAC CGC\cr
#'  CTA CCA CAA CGA\cr
#'  CTG CCG CAG CGG\cr
#'  ATT ACT AAT AGT\cr
#'  ATC ACC AAC AGC\cr
#'  ATA ACA AAA AGA\cr
#'  ATG ACG AAG AGG\cr
#'  GTT GCT GAT GGT\cr
#'  GTC GCC GAC GGC\cr
#'  GTA GCA GAA GGA\cr
#'  GTG GCG GAG GGG
#'
#' @return A matrix object with all DNA codons
#' @examples
#' res <- get_rna_codon_table()
#'
#' @export
get_dna_codon_table <- function() {
  return(factor_dna_codon_table(get_dna_codon_list()))      
}

#' The Genetic Codes
#' 
#' \\emph{genetic_codes_as_df_by_index} returns a data.frame table which represents a Genetic Code. The table is 4*16.
#' This table has row names and column names.
#' \cr Source:\cr
#' \emph{Compiled by Andrzej (Anjay) Elzanowski and Jim Ostell at National Center for Biotechnology Information (NCBI), Bethesda, Maryland, U.S.A.}\cr
#' \emph{Last update of the Genetic Codes: Nov. 18, 2016}
#' \emph{\link{https:#www.ncbi.nlm.nih.gov/Taxonomy/Utils/wprintgc.cgi}}
#'
#' \emph{codons} all codons as strings.\cr
#' \emph{amino_acids} the translated aminop acids in same order.\cr
#' 
#' @param idx the index of a Genetic Code table as int. (check \link{print_all_translation_table})
#' @param a@param acid a String, is optional: DNA or RNA
#'
#' @return Returns a named List with all codons and the translated amino acids:\cr
#' @examples
#' (code <- genetic_codes_as_df_by_index(1))
#' 
#' @export 
genetic_codes_as_df_by_index <- function(idx, acid="RNA") {
  code_table <- cpp_genetic_codes_as_df_by_index(1)
  row.names(code_table) <- c("U_U", "U_C", "U_A", "U_G", "C_U", "C_C", "C_A", "C_G", "A_U", "A_C", "A_A", "A_G", "G_U", "G_C", "G_A", "G_G")
  return(code_table)
}