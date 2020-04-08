# Test other functions regarding circularity

# check find and analyse code in sequence
library(testthat)
library(Rcpp)
library(GCATR)

# Test and analyse if code cotanined in sequence

# Code not contained, code as string with tuple length

test_that('code is not contained in sequence', {
  seq <- "DACGTCGCGACGTACGACGTCGTACTCGATGCAAGAC"
  res <- find_and_analysis_code_in_sequence(seq, "SADSDS", tuple_length=3, 0)
  expect_length(res$word, 0)
  expect_length(res$idx_list, 0)
  expect_length(res$rest, 1)
  expect_length(res$parts, 1)
  expect_equal(res$longest_match, 0)
  expect_equal(res$total_match_in_percent, 0)
})

# Code contained, code as string with tuple length
# ERROR: does not correctly calcualte total match in percent or is only longest match taken?
# Longest match not correctly calculated when at the end of the sequence

test_that('code is contained in sequence', {
  seq <- "ACGTCGCGACGTACGACGTCG"
  res <- find_and_analysis_code_in_sequence(seq, "ACGTCG", tuple_length=3, 0)
  print(res)
  expect_equal(res$word, c("ACG", "TCG", "ACG","ACG", "TCG"))
  expect_equal(res$idx_list, c(0,3,12,15,18))
  expect_equal(res$rest,"CGACGT")
  expect_equal(res$parts, c("","ACGTCG", "CGACGT","ACGACGTCG"))
  expect_equal(res$longest_match,9)
  expect_more_than(res$total_match_in_percent,71)
})

# Code not contained, code as string split by space
# Try with numerals instead of letters


test_that('code is not contained in sequence', {
  seq <- "1222134564122341"
  res <- find_and_analysis_code_in_sequence(seq,"5555 6666")
  expect_length(res$word,0)
  expect_length(res$idx_list,0)
  expect_equal(res$rest,"1222134564122341")
  expect_equal(res$parts, c("1222134564122341"))
  expect_equal(res$longest_match,0)
  expect_equal(res$total_match_in_percent,0)
})

# Code is contained in sequence, code as string split by space,
# Numerals instead of letters
test_that('code is contained in sequence', {
  seq <- "1222134564122341"
  res <- find_and_analysis_code_in_sequence(seq,"1345 2341")
  expect_equal(res$word,c("1345", "2341"))
  expect_equal(res$idx_list,c(4,12))
  expect_equal(res$rest,"12226412")
  expect_equal(res$parts, c("1222","1345","6412","2341"))
  expect_equal(res$longest_match,4)
  expect_equal(res$total_match_in_percent,50)
})

# Code not contained in sequence, code as string vector
# Try random ascii characters

test_that('code is not contained in sequence', {
  seq <- "#+aopp&%?!!$"
  res <- find_and_analysis_code_in_sequence(seq,c("asd"))
  expect_length(res$word,0)
  expect_length(res$idx_list,0)
  expect_equal(res$rest,"#+aopp&%?!!$")
  expect_equal(res$parts, c("#+aopp&%?!!$"))
  expect_equal(res$longest_match,0)
  expect_equal(res$total_match_in_percent,0)
})

# Code is contained in sequence, code as string split by space,
# Ascii characters instead of letters

test_that('code is contained in sequence', {
  seq <- "#+oopp&%?!!$"
  res <- find_and_analysis_code_in_sequence(seq,c("&%?"))
  expect_equal(res$word,c("&%?"))
  expect_equal(res$idx_list,c(6))
  expect_equal(res$rest,"#+oopp!!$")
  expect_equal(res$parts, c("#+oopp","&%?","!!$"))
  expect_equal(res$longest_match,3)
  expect_equal(res$total_match_in_percent,25)
})




