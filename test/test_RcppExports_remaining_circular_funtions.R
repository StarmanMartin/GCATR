# Test other functions regarding circularity

# check find and analyse code in sequence
library(testthat)
library(Rcpp)
library(GCATR)

test_that('code is contained in sequence', {
  seq <- "ACGTCGCGACGTACGACGTCGTACTCGATGCAAGATC"
  res <- find_and_analysis_code_in_sequence(seq, c("ACG", "TCG"))
  res <- find_and_analysis_code_in_sequence(seq, "ACGCG", tuple_length=3)
  res <- find_and_analysis_code_in_sequence(seq, "ACG TCG")
  print(res)
})
