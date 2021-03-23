library(testthat)
library(GCATR)

#start_bda
test_that("BDA to be started", {
  expect_false(is.null(start_bda()))

  obj <- start_bda()
  add_rule(obj, 1,3, "A", "C", "G", "C")
  res <- run_bda_as_matrix(obj)
  
  rna_table <- c("UUU -> 1", "UUC -> 0", "UUA -> 1", "UUG -> 0", "CUU -> 1", "CUC -> 1", "CUA -> 1", "CUG -> 1", "AUU -> 0", "AUC -> 0", "AUA -> 0", "AUG -> 0", "GUU -> 1", "GUC -> 0", "GUA -> 1", "GUG -> 0", "UCU -> 1", "UCC -> 0", "UCA -> 1", "UCG -> 0", "CCU -> 1", "CCC -> 1", "CCA -> 1", "CCG -> 1", "ACU -> 0", "ACC -> 0", "ACA -> 0", "ACG -> 0", "GCU -> 1", "GCC -> 0", "GCA -> 1", "GCG -> 0", "UAU -> 1", "UAC -> 0", "UAA -> 1", "UAG -> 0", "CAU -> 1", "CAC -> 1", "CAA -> 1", "CAG -> 1", "AAU -> 0", "AAC -> 0", "AAA -> 0", "AAG -> 0", "GAU -> 1", "GAC -> 0", "GAA -> 1", "GAG -> 0", "UGU -> 1", "UGC -> 0", "UGA -> 1", "UGG -> 0", "CGU -> 1", "CGC -> 1", "CGA -> 1", "CGG -> 1", "AGU -> 0", "AGC -> 0", "AGA -> 0", "AGG -> 0", "GGU -> 1", "GGC -> 0", "GGA -> 1", "GGG -> 0")
  
  for(i in 1:length(rna_table)) {
    expect_equal(res[i], rna_table[i])
  }
})

#start_dinucleotide_bda
test_that("BDA to be started as dinucleotide", {
  expect_false(is.null(start_bda(2)))
  
  obj <- start_bda(2)
  add_rule(obj, 1,2, "A", "C", "G", "C")
  res <- run_bda(obj)
  
  val <- c( "1", "0", "1", "0", "1", "1", "1", "1", "0", "0", "0", "0", "1", "0", "1", "0")
  dinucs <- c("UU", "UC", "UA", "UG", "CU", "CC", "CA", "CG", "AU", "AC", "AA", "AG", "GU", "GC", "GA", "GG")
  
  for(i in 1:length(res)) {
    expect_equal(res$bda[i], val[i])
    expect_equal(res$code[i], dinucs[i])
  }
})



#code_start_bda
test_that("BDA to be started", {
  expect_false(is.null(code_start_bda("ACG GCG")))
})

# add_bda

# both true, first condition true
test_that("bda correctly returns true for both codons", {
  obj <- code_start_bda(c("CCG", "CAG"))
  add_rule(obj, 1,3, "A", "C", "G", "C")
  run_bda(obj)
  expect_equal(run_bda(obj)$bda, c("1","1"))
})

# both false, first condition true
test_that("bda correctly returns true for both codons", {
  obj <- code_start_bda(c("CCG", "CAG"))
  add_rule(obj, 1,3, "C", "A", "G", "C")
  expect_equal(run_bda(obj)$bda, c("0","0"))
})

# one true one false, first condition true
test_that("bda correctly returns true for both codons", {
  obj <- code_start_bda(c("ACG", "CAG"))
  add_rule(obj,1,3, "A", "C", "G", "C")
  expect_equal(run_bda(obj)$bda, c("0","1"))
})

# both true, first condition false

test_that("bda correctly returns true for both codons", {
  obj <- code_start_bda(c("GGA", "GGT"))
  add_rule(obj,1,3, "A", "C", "C", "C")
  expect_equal(run_bda(obj)$bda, c("1","1"))
})

# both false, first condition false
test_that("bda correctly returns true for both codons", {
  obj <- code_start_bda(c("GGC", "GGT"))
  add_rule(obj, 1,3, "A", "A", "C", "T")
  expect_equal(run_bda(obj)$bda, c("0","0"))
})

# one true one false, first condition false
test_that("bda correctly returns true for both codons", {
  obj <- code_start_bda(c("GGG", "GGT"))
  add_rule(obj, 1,3, "A", "A", "C", "T")
  expect_equal(run_bda(obj)$bda, c("1","0"))
})

#Something wrong here
# run_bda_as_matrix
test_that("bda correctly applied to all rna codons", {
  obj <- start_bda()
  add_rule(obj,1,2, "C", "A", "C", "U")
  res <- run_bda_as_matrix(obj)  
  expect_equal(length(res), 64)
  expect_equal(res[1],"UUU -> 0")
  expect_equal(res[14], "GUC -> 0")
  expect_equal(res[25], "ACU -> 1")
})


