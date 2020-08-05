# Test code property functions

library(testthat)
library(GCATR)

# Self-complementarity

test_that('is non self-complementary, string with no delimiter, tuple length 3', {
  expect_false(code_check_if_self_complementary('UGGGUG', 3))
})

test_that('is self-complementary, string with no delimiter, tuple length 3', {
  expect_true(code_check_if_self_complementary('CGGACGCCGCGU',3))
})

test_that('is non self-complementary, string split by " "', {
  expect_false(code_check_if_self_complementary('UGG GUG'))
})

test_that('is self-complementary, string split by " "', {
  expect_true(code_check_if_self_complementary('CGG ACG CCG CGU'))
})

test_that('is non self-complementary, string vector', {
  expect_false(code_check_if_self_complementary(c('UGA', 'AUG')))
})

test_that('is self-complementary, string vector', {
  expect_true(code_check_if_self_complementary(c('CGG', 'ACG', 'CCG', 'CGU')))
})

test_that('empty code throws error',{
  expect_error(code_check_if_self_complementary(("")))
})



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

#test with different alphabet
# A -> 1, C-> 2, G-> 3, U ->4

test_that('is non circular, string vector', {
  expect_false(code_check_if_circular(c('433', '343')))
})

#test with different alphabet
# A -> 1, C-> 2, G-> 3, U ->4

test_that('is circular, string vector', {
  expect_true(code_check_if_circular(c('334','332','124','122','132','134','312','314','342','344','114','144','112','132','324','322')))
})

test_that("empty code throws error", {
  expect_error(code_check_if_circular(""))
})

# k- circularity

#in every test set place one test with different alphabet
# A -> 1, C-> 2, G-> 3, U ->4

test_that('error is thrown when negative k value is used',{
  expect_true(code_check_if_k_circular(0,'UGGGUG', 3))
  expect_error(code_check_if_k_circular(-2,'UGG GUG'))
  expect_error(code_check_if_k_circular(-10,c('UGG','GUG')))
})

test_that('is non circular, string with no delimiter, tuple length 3', {
  expect_false(code_check_if_k_circular(1,'UGGGUG', 3))
  expect_false(code_check_if_k_circular(2,'433243332434',3))
  expect_false(code_check_if_k_circular(3,'ACGGUACGUCGGUAC',3))
  expect_false(code_check_if_k_circular(4,'CGUACGUACGUA',3))
  
  
})

test_that('is circular, string with no delimiter, tuple length 3', {
  expect_true(code_check_if_k_circular(1,'UGGCUGGGCUGU', 3))
  expect_true(code_check_if_k_circular(2,'ACGGUACGUCGGUAC',3))
  expect_true(code_check_if_k_circular(3,'234123412341',3))
  expect_true(code_check_if_k_circular(4,'GGUGGCACUACCAGCAGUGACGAUGUCGUUAAUAUUAACAUCGCUGCC',3))
  
  
  
})

test_that('is non circular, string split by " "', {
  expect_false(code_check_if_k_circular(1,'UGG GUG'))
  expect_false(code_check_if_k_circular(2,'UGG CUG GGC UGU'))
  expect_false(code_check_if_k_circular(3,'ACG GUA CGU CGG UAC'))
  expect_false(code_check_if_k_circular(4,'234 123 412 341'))
})

test_that('is circular, string split by " "', {
  expect_true(code_check_if_k_circular(1,'UGG CUG GGC UGU'))
  expect_true(code_check_if_k_circular(2,'ACG GUA CGU CGG UAC'))
  expect_true(code_check_if_k_circular(3,'234 123 412 341'))
  expect_true(code_check_if_k_circular(4,'GGU GGC ACU ACC AGC AGU GAC GAU GUC GUU AAU AUU AAC AUC GCU GCC'))
  
})

# 5. non circular, string vector
test_that('is non circular, string vector', {
  expect_false(code_check_if_k_circular(1,c('UGG','GUG')))
  expect_false(code_check_if_k_circular(2,c('433', '243', '332', '434')))
  expect_false(code_check_if_k_circular(3,c('ACG', 'GUA', 'CGU', 'CGG', 'UAC')))
  expect_false(code_check_if_k_circular(4,c('CGU', 'ACG', 'UAC', 'GUA')))
  
})
# 6. circular,  string vector
test_that('is circular,  string vector', {
  expect_true(code_check_if_k_circular(1,c('UGG','CUG','GGC','UGU')))
  expect_true(code_check_if_k_circular(2,c('ACG','GUA','CGU','CGG','UAC')))
  expect_true(code_check_if_k_circular(3,c('234', '123', '412', '341')))
  expect_true(code_check_if_k_circular(4,c('GGU', 'GGC', 'ACU', 'ACC', 'AGC', 'AGU', 'GAC', 'GAU', 'GUC', 'GUU', 'AAU', 'AUU', 'AAC', 'AUC', 'GCU', 'GCC')))
})

# 7. try empty input
test_that("empty string throws error",{
  expect_error(code_check_if_k_circular(1,c("")))
  expect_error(code_check_if_k_circular(2,c("")))
  expect_error(code_check_if_k_circular(3,c("")))
  expect_error(code_check_if_k_circular(4,c("")))
})

# cn-circularity

test_that('is non-cn-circular, string with no delimiter, tuple length 3', {
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

# test with different alphabet
# A -> 1, C-> 2, G->3, U-> 4

test_that('is non cn-circular, string vector', {
  expect_false(code_check_if_cn_circular(c('433', '343')))
})


test_that('is cn-circular, string vector', {
  expect_true(code_check_if_cn_circular(c('GGU','GGC','ACU','ACC','AGC','AGU','GAC','GAU','GUC','GUU','AAU','AUU','AAC','AUC','GCU','GCC')))
})

test_that('empty code throws error', {
  expect_error(code_check_if_cn_circular(""))
})


# Comma-freeness

test_that('is not comma free, string with no delimiter, tuple length 3', {
  expect_false(code_check_if_comma_free('AUCUCCCAA', 3))
})

test_that('is comma free, string with no delimiter, tuple length 3', {
  expect_true(code_check_if_comma_free('GGUGGCACUACCAGCAGUGACGAUGUCGUUAAUAUUAACAUCGCUGCC',3))
})

test_that('is not comma free, string with split by " "', {
  expect_false(code_check_if_comma_free('AUC UCC CAA'))
})

test_that('is comma free, string with split by " "', {
  expect_true(code_check_if_comma_free('GGU GGC ACU ACC AGC AGU GAC GAU GUC GUU AAU AUU AAC AUC GCU GCC'))
})

test_that('expect error when code is empty', {
  expect_error(code_check_if_comma_free(''))
})

# test with different alphabet
# A -> 1, C-> 2, G->3, U-> 4

test_that('is not comma free, string vector', {
  expect_false(code_check_if_comma_free(c('142', '422', '211')))
})

test_that('is comma free, string vector', {
  expect_true(code_check_if_comma_free(c('332','322')))
})

test_that('empty code throws error', {
  expect_error(code_check_if_comma_free(""))
})