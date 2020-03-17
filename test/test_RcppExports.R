# Check circularity functions

# Maximal circularity:

# 1. non circular, string with no delimiter, tuple length 3
library(testthat)
library(Rcpp)
library(GCATR)
print(code_check_if_k_circular(1,"UGGGUG", 3))

test_that("is not circular", {
    expect_false(code_check_if_circular("UGGGUG", 3))
})

# 2.circular, string with no delimiter, tuple length 3
test_that("is circular", {
  expect_true(code_check_if_circular("GGUGGCACUACCAGCAGUGACGAUGUCGUUAAUAUUAACAUCGCUGCC ", 3))
})

# 3. non circular, string split by " "
test_that("is not circular", {
  expect_false(code_check_if_circular("UGG GUG"))
})

# 4.circular, string split by " "
test_that("is circular", {
  expect_true(code_check_if_circular("GGU GGC ACU ACC AGC AGU GAC GAU GUC GUU AAU AUU AAC AUC GCU GCC"))
})

# 5.non circular, string vector
test_that("is circular", {
  expect_false(code_check_if_circular(c('UGG', 'GUG')))
})


# 6.circular, string vector
test_that("is circular", {
  expect_true(code_check_if_circular(c('GGU','GGC','ACU','ACC','AGC','AGU','GAC','GAU','GUC','GUU','AAU','AUU','AAC','AUC','GCU','GCC')))
})

# k- circularity:

# 1. non 1-circular, string with no delimiter, tuple length 3
test_that("is not 1-circular", {
  expect_false(code_check_if_k_circular(1,"UGGGUG", 3))
})

# 2. 1-circular, string with no delimiter, tuple length 3
test_that("is not 1-circular", {
  expect_true(code_check_if_k_circular(1,"UGGCUGGGCUGU", 3))
})

# 3. non 1-circular, string split by " "
test_that("is not 1-circular", {
  expect_false(code_check_if_k_circular(1,"UGG GUG"))
})

# 4. 1-circular,  string split by " "
test_that("is not 1-circular", {
  expect_true(code_check_if_k_circular(1,"UGG CUG GGC UGU"))
})

# 5. non 1-circular, string vector
test_that("is not 1-circular", {
  expect_false(code_check_if_k_circular(1,c('UGG','GUG')))
})
# 6. 1-circular,  string vector
test_that("is not 1-circular", {
  expect_true(code_check_if_k_circular(1,c('UGG','CUG','GGC','UGU')))
})




