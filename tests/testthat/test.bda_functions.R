library(testthat)
library(GCATR)

#start_bda
test_that("BDA to be started", {
  expect_false(is.null(start_bda()))
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


