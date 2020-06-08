library(testthat)
library(GCATR)

#start_bda
test_that("BDA to be started", {
  expect_true(start_bda())
})

#code_start_bda
test_that("BDA to be started", {
  expect_true(code_start_bda("ACG GCG"))
})

# add_bda

# both true, first condition true
test_that("bda correctly returns true for both codons", {
  code_start_bda(c("CCG", "CAG"))
  add_bda(1,3, "A", "C", "G", "C")
  expect_equal(run_bda()$bda, c("1","1"))
})

# both false, first condition true
test_that("bda correctly returns true for both codons", {
  code_start_bda(c("CCG", "CAG"))
  add_bda(1,3, "C", "A", "G", "C")
  expect_equal(run_bda()$bda, c("0","0"))
})

# one true one false, first condition true
test_that("bda correctly returns true for both codons", {
  code_start_bda(c("ACG", "CAG"))
  add_bda(1,3, "A", "C", "G", "C")
  expect_equal(run_bda()$bda, c("0","1"))
})

# both true, first condition false

test_that("bda correctly returns true for both codons", {
  code_start_bda(c("GGA", "GGT"))
  add_bda(1,3, "A", "C", "C", "C")
  expect_equal(run_bda()$bda, c("1","1"))
})

# both false, first condition false
test_that("bda correctly returns true for both codons", {
  code_start_bda(c("GGC", "GGT"))
  add_bda(1,3, "A", "A", "C", "T")
  expect_equal(run_bda()$bda, c("0","0"))
})

# one true one false, first condition false
test_that("bda correctly returns true for both codons", {
  code_start_bda(c("GGG", "GGT"))
  add_bda(1,3, "A", "A", "C", "T")
  expect_equal(run_bda()$bda, c("1","0"))
})

# run_bda_as_matrix
start_bda()
add_bda(1, 2, "C", "G", "A", "U")
add_bda(1, 3, "A", "G", "C", "U")
res <- run_bda_as_matrix()
