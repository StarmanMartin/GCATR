library(testthat)
library(GCATR)

#code_get_acid
# string split by " "
test_that("DNA should be returned, when only A C and G is used", {
  expect_equal(code_get_acid("ACG GCA"), "DNA")
})
#string as vector
test_that("RNA should be returned if tuples uses A C G and T", {
  expect_equal(code_get_acid(c("ACG", "ATT")), "DNA")
})
#string with tuple length
test_that("RNA should be returned if tuples uses A C G and T", {
  expect_equal(code_get_acid(c("ACG", "ATT")), "DNA")
})

test_that("NONE is returned if no valid bases are contained", {
  expect_equal(code_get_acid("123"), "NONE")
})

test_that("NONE is returned if DNA and RNA bases are mixed", {
  expect_equal(code_get_acid("ACT ACU"), "NONE")
})


#get_dna_bases
test_that("correct DNA bases are returned", {
  expect_equal(sort(get_dna_bases()),sort(c("T", "C", "G", "A")))
})

#get_rna_bases
test_that("correct RNA bases are returned", {
  expect_equal(sort(get_rna_bases()),sort(c("U", "C", "G", "A")))
})


#get_rna_codon_table
test_that("Rna codon table contains all codons", {
  all_codons <- c( "UUU","UUC", "UUA", "UUG", "CUU", "CUC", "CUA", "CUG", "AUU", "AUC", "AUA", "AUG", "GUU", "GUC", "GUA", "GUG", "UCU", "UCC", "UCA", "UCG", "CCU", "CCC", "CCA", "CCG", "ACU", "ACC", "ACA", "ACG", "GCU",
                  "GCC", "GCA", "GCG", "UAU", "UAC", "UAA", "UAG", "CAU", "CAC", "CAA", "CAG", "AAU", "AAC", "AAA", "AAG", "GAU", "GAC", "GAA", "GAG", "UGU", "UGC", "UGA", "UGG", "CGU", "CGC", "CGA", "CGG", "AGU", "AGC",
                  "AGA", "AGG", "GGU", "GGC", "GGA", "GGG")
  all_rna_codons <- as.vector(get_rna_codon_table())
  expect_equal(all_rna_codons, all_codons)
})

#get_rna_codon_list
test_that("Rna codon table contains all codons", {
  all_codons <- sort(c( "UUU","UUC", "UUA", "UUG", "CUU", "CUC", "CUA", "CUG", "AUU", "AUC", "AUA", "AUG", "GUU", "GUC", "GUA", "GUG", "UCU", "UCC", "UCA", "UCG", "CCU", "CCC", "CCA", "CCG", "ACU", "ACC", "ACA", "ACG", "GCU",
                   "GCC", "GCA", "GCG", "UAU", "UAC", "UAA", "UAG", "CAU", "CAC", "CAA", "CAG", "AAU", "AAC", "AAA", "AAG", "GAU", "GAC", "GAA", "GAG", "UGU", "UGC", "UGA", "UGG", "CGU", "CGC", "CGA", "CGG", "AGU", "AGC",
                   "AGA", "AGG", "GGU", "GGC", "GGA", "GGG"))
  all_rna_codons <- sort(as.vector(get_rna_codon_list()))
  expect_equal(all_rna_codons, all_codons)
})


# code_pfd_report
test_that("pdf is created in the right dir", {
  unlink("GCATR_Report", recursive = TRUE)
  code_pdf_report(c("ACG", "CAG"))
  fn <- "./GCATR_Report/GCATR_Report.pdf"
  expect_true(file.exists(fn))
})

