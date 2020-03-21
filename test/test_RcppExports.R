# Check circularity functions

library(testthat)
library(Rcpp)
library(GCATR)

# Maximal circularity:

test_that('is non-circular, string with no delimiter, tuple length 3', {
  expect_false(code_check_if_circular('UGGGUG', 3))
})

test_that('is circular, string with no delimiter, tuple length 3', {
  expect_true(code_check_if_circular('GGUGGCACUACCAGCAGUGACGAUGUCGUUAAUAUUAACAUCGCUGCC ', 3))
})


test_that('is non circular, string split by " "', {
  expect_false(code_check_if_circular('UGG GUG'))
})

test_that('is circular, string split by " "', {
  expect_true(code_check_if_circular('GGU GGC ACU ACC AGC AGU GAC GAU GUC GUU AAU AUU AAC AUC GCU GCC'))
})

test_that('is non circular, string vector', {
  expect_false(code_check_if_circular(c('UGG', 'GUG')))
})


test_that('is circular, string vector', {
  expect_true(code_check_if_circular(c('GGU','GGC','ACU','ACC','AGC','AGU','GAC','GAU','GUC','GUU','AAU','AUU','AAC','AUC','GCU','GCC')))
})

# k- circularity:

test_that('is non circular, string with no delimiter, tuple length 3', {
  expect_false(code_check_if_k_circular(1,'UGGGUG', 3))
  expect_false(code_check_if_k_circular(2,'UGGCUGGGCUGU',3))
  expect_false(code_check_if_k_circular(3,'ACGGUACGUCGGUAC',3))
  expect_false(code_check_if_k_circular(4,'CGUACGUACGUA',3))

  
})

test_that('is circular, string with no delimiter, tuple length 3', {
  expect_true(code_check_if_k_circular(1,'UGGCUGGGCUGU', 3))
  expect_true(code_check_if_k_circular(2,'ACGGUACGUCGGUAC',3))
  expect_true(code_check_if_k_circular(3,'CGUACGUACGUA',3))
  expect_true(code_check_if_k_circular(4,'GGUGGCACUACCAGCAGUGACGAUGUCGUUAAUAUUAACAUCGCUGCC',3))

  
  
})

test_that('is non circular, string split by " "', {
  expect_false(code_check_if_k_circular(1,'UGG GUG'))
  expect_false(code_check_if_k_circular(2,'UGG CUG GGC UGU'))
  expect_false(code_check_if_k_circular(3,'ACG GUA CGU CGG UAC'))
  expect_false(code_check_if_k_circular(4,'CGU ACG UAC GUA'))
})

test_that('is circular, string split by " "', {
  expect_true(code_check_if_k_circular(1,'UGG CUG GGC UGU'))
  expect_true(code_check_if_k_circular(2,'ACG GUA CGU CGG UAC'))
  expect_true(code_check_if_k_circular(3,'CGU ACG UAC GUA'))
  expect_true(code_check_if_k_circular(4,'GGU GGC ACU ACC AGC AGU GAC GAU GUC GUU AAU AUU AAC AUC GCU GCC'))
  
})

# 5. non circular, string vector
test_that('is non circular, string vector', {
  expect_false(code_check_if_k_circular(1,c('UGG','GUG')))
  expect_false(code_check_if_k_circular(2,c('UGG', 'CUG', 'GGC', 'UGU')))
  expect_false(code_check_if_k_circular(3,c('ACG', 'GUA', 'CGU', 'CGG', 'UAC')))
  expect_false(code_check_if_k_circular(4,c('CGU', 'ACG', 'UAC', 'GUA')))
  
})
# 6. circular,  string vector
test_that('is circular,  string vector', {
  expect_true(code_check_if_k_circular(1,c('UGG','CUG','GGC','UGU')))
  expect_true(code_check_if_k_circular(2,c('ACG','GUA','CGU','CGG','UAC')))
  expect_true(code_check_if_k_circular(3,c('CGU', 'ACG', 'UAC', 'GUA')))
  expect_true(code_check_if_k_circular(4,c('GGU', 'GGC', 'ACU', 'ACC', 'AGC', 'AGU', 'GAC', 'GAU', 'GUC', 'GUU', 'AAU', 'AUU', 'AAC', 'AUC', 'GCU', 'GCC')))
})

# cn-circularity

test_that('is non-circular, string with no delimiter, tuple length 3', {
  expect_false(code_check_if_cn_circular('UGGGUG', 3))
})

test_that('is cn-circular, string with no delimiter, tuple length 3', {
  expect_true(code_check_if_cn_circular('GGUGGCACUACCAGCAGUGACGAUGUCGUUAAUAUUAACAUCGCUGCC ', 3))
})


test_that('is non cn-circular, string split by " "', {
  expect_false(code_check_if_cn_circular('UGG GUG'))
})

test_that('is cn-circular, string split by " "', {
  expect_true(code_check_if_cn_circular('GGU GGC ACU ACC AGC AGU GAC GAU GUC GUU AAU AUU AAC AUC GCU GCC'))
})

test_that('is non cn-circular, string vector', {
  expect_false(code_check_if_cn_circular(c('UGG', 'GUG')))
})


test_that('is cn-circular, string vector', {
  expect_true(code_check_if_cn_circular(c('GGU','GGC','ACU','ACC','AGC','AGU','GAC','GAU','GUC','GUU','AAU','AUU','AAC','AUC','GCU','GCC')))
})




