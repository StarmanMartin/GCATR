# Test other functions regarding circularity

library(testthat)
library(Rcpp)
library(GCATR)

# Test and analyse if code cotanined in sequence

# Code not contained, code as string with tuple length

test_that('code is not contained in sequence', {
  seq <- "DACGTCGCGACGTACGACGTCGTACTCGATGCAAGAC"
  res <- find_and_analysis_code_in_sequence(seq, "SADSDS", tuple_length=3, 0)
  print(res)
  expect_length(res$word, 0)
  expect_length(res$idx_list, 0)
  expect_equal(res$rest, "DACGTCGCGACGTACGACGTCGTACTCGATGCAAGAC")
  expect_equal(res$parts, c("DACGTCGCGACGTACGACGTCGTACTCGATGCAAGAC"))
  expect_equal(res$longest_match, 0)
  expect_equal(res$total_match_in_percent, 0)
})

# Code contained, code as string with tuple length

test_that('code is contained in sequence', {
  seq <- "ACGTCGCGACGTACGACGTCG"
  res <- find_and_analysis_code_in_sequence(seq, "ACGTCG", tuple_length=3, 0)
  expect_equal(res$word, c("ACG", "TCG", "ACG","ACG", "TCG"))
  expect_equal(res$idx_list, c(0,3,12,15,18))
  expect_equal(res$rest,"CGACGT")
  expect_equal(res$parts, c("","ACGTCG", "CGACGT","ACGACGTCG"))
  expect_equal(res$longest_match,9)
  expect_gt(res$total_match_in_percent,71)
  expect_lt(res$total_match_in_percent, 72)
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

# Code is contained in sequence, code as string vector,
# Ascii characters 

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


# Try testing with frameshift

test_that('code is contained in sequence in frameshift 1', {
  seq <- "513455123345633"
  res <- find_and_analysis_code_in_sequence(seq,"13453456", tuple_length = 4, 1)
  expect_equal(res$word,c("1345", "3456"))
  expect_equal(res$idx_list, c(1,9))
  expect_equal(res$rest,"5123335")
  expect_equal(res$parts, c("","1345","5123","3456", "335"))
  expect_equal(res$longest_match,4)
  expect_gt(res$total_match_in_percent,53)
  expect_lt(res$total_match_in_percent,53.5)
})

test_that('code is not contained in sequence in frameshift 1', { 
  seq <- "1345512334"
  res <- find_and_analysis_code_in_sequence(seq,"1345", tuple_length = 4, 1)
  expect_length(res$word,0)
  expect_length(res$idx_list, 0)
  expect_equal(res$rest,"3455123341")
  expect_equal(res$parts, c("3455123341"))
  expect_equal(res$longest_match,0)
  expect_equal(res$total_match_in_percent,0)
})


test_that('code is contained in sequence in frameshift 2', {
  seq <- "331345512339"
  res <- find_and_analysis_code_in_sequence(seq,"1345", tuple_length = 4, 2)
  expect_equal(res$word,c("1345"))
  expect_equal(res$idx_list, c(2))
  expect_equal(res$rest,"51233933")
  expect_equal(res$parts, c("","1345","51233933"))
  expect_equal(res$longest_match,4)
  expect_gt(res$total_match_in_percent,33)
  expect_lt(res$total_match_in_percent,33.5)
})


test_that('code is not contained in sequence in frameshift 2', {
  seq <- "3134551235"
  res <- find_and_analysis_code_in_sequence(seq,"1345", tuple_length = 4, 2)
  expect_length(res$word,0)
  expect_length(res$idx_list, 0)
  expect_equal(res$rest,"3455123531")
  expect_equal(res$parts, c("3455123531"))
  expect_equal(res$longest_match,0)
  expect_equal(res$total_match_in_percent,0)
})

# try negative frameshifts
# -14 % 15 = 1 [(-14 +15 ) %15 = 1]

test_that('code is contained in sequence in frameshift 1', {
  seq <- "513455123345633"
  res <- find_and_analysis_code_in_sequence(seq,"13453456", tuple_length = 4, -14)
  print(res)
  expect_equal(res$word,c("1345", "3456"))
  expect_equal(res$idx_list, c(1,9))
  expect_equal(res$rest,"5123335")
  expect_equal(res$parts, c("","1345","5123","3456", "335"))
  expect_equal(res$longest_match,4)
  expect_gt(res$total_match_in_percent,53)
  expect_lt(res$total_match_in_percent,53.5)
})


# -29 % 10 = 1  [(-29 +  3*10 ) % 15 = 1]

test_that('code is not contained in sequence in frameshift 1', { 
  seq <- "1345512334"
  res <- find_and_analysis_code_in_sequence(seq,"1345", tuple_length = 4, -29)
  expect_length(res$word,0)
  expect_length(res$idx_list, 0)
  expect_equal(res$rest,"3455123341")
  expect_equal(res$parts, c("3455123341"))
  expect_equal(res$longest_match,0)
  expect_equal(res$total_match_in_percent,0)
})

# -22 % 12 = 2 [-22 + 2*12)% 12 = 2]

test_that('code is contained in sequence in frameshift 2', {
  seq <- "331345512339"
  res <- find_and_analysis_code_in_sequence(seq,"1345", tuple_length = 4, -22)
  expect_equal(res$word,c("1345"))
  expect_equal(res$idx_list, c(2))
  expect_equal(res$rest,"51233933")
  expect_equal(res$parts, c("","1345","51233933"))
  expect_equal(res$longest_match,4)
  expect_gt(res$total_match_in_percent,33)
  expect_lt(res$total_match_in_percent,33.5)
})



# -38 % 10 = 2 [(-38 + 4*10) % 10 = 2]
test_that('code is not contained in sequence in frameshift 2', {
  seq <- "3134551235"
  res <- find_and_analysis_code_in_sequence(seq,"1345", tuple_length = 4, -38)
  expect_length(res$word,0)
  expect_length(res$idx_list, 0)
  expect_equal(res$rest,"3455123531")
  expect_equal(res$parts, c("3455123531"))
  expect_equal(res$longest_match,0)
  expect_equal(res$total_match_in_percent,0)
})


# Generate code by min value


# check with tuple length 3 and basic alphabet
test_that('code generated by min value contains each initial value of each of the 20 equivalence classes', {
  first_codon_of_each_class <- c("AAC", "AAG", "AAU", "ACC", "ACG", "ACU", "AGC", "AGG", "AGU", "AUC", "AUG", "AUU", "CCG", "CCU","CGG", "CGU", "CUG", "CUU", "GGU", "GUU")
  code <- generate_code_by_min_value(c("A", "C", "G", "U"), 3)
  expect_equivalent(code, first_codon_of_each_class)
})

# Test with tuple length 2 and numerals
test_that('code generated by min value contains each initial value of each of the 6 equivalence classes', {
  first_codon_of_each_class = c("12", "13", "14", "23", "24", "34")
  code <- generate_code_by_min_value(c("1", "2", "3", "4"), 2)
  expect_equivalent(code, first_codon_of_each_class)
  
}) 


# Test tuple shift

# Code as string with tuple length, shift 1

test_that('tuples are shifted correctly', {
  shifted_code <- shift_tuples(1, "CAGGGAUGA", tuple_length = 3)
  expect_equal(shifted_code, c("AGC", "GAG", "GAU"))
})

# Code as string with tuple length, shift 2

test_that('tuples are shifted correctly', {
  shifted_code <- shift_tuples(2, "CAGGGAUGA", tuple_length = 3)
  expect_equal(shifted_code, c("GCA", "AGG", "AUG"))
})

# Code as string split by " ", shift 1

test_that('tuples are shifted correctly', {
  shifted_code <- shift_tuples(1, "CAG GGA UGA")
  expect_equal(shifted_code, c("AGC", "GAG", "GAU"))
})

# Code as string split by " ", shift 2

test_that('tuples are shifted correctly', {
  shifted_code <- shift_tuples(2, "CAG GGA UGA")
  expect_equal(shifted_code, c("GCA", "AGG", "AUG"))
})

# Code as string vector, shift 1

test_that('tuples are shifted', {
  shifted_code <- shift_tuples(1, c("CAG","GGA","UGA"))
  expect_equal(shifted_code, c("AGC", "GAG", "GAU"))
})

# Code as string vector, shift 2

test_that('tuples are shifted', {
  shifted_code <- shift_tuples(2, c("CAG","GGA","UGA"))
  expect_equal(shifted_code, c("GCA", "AGG", "AUG"))
})

# Code as string with tuple length, try shift equivalent to 2
# 5 % 3 = 2

test_that('tuples are shifted correctly', {
  shifted_code <- shift_tuples(5, "CAGGGAUGA", tuple_length = 3)
  expect_equal(shifted_code, c("GCA", "AGG", "AUG"))
})

# Code as string with tuple length, try negative shift equivalent to 1
# -2 % 3 = 1 [(-2 + 3) % 3 = 1]

test_that('tuples are shifted correctly', {
  shifted_code <- shift_tuples(-2, "CAGGGAUGA", tuple_length = 3)
  expect_equal(shifted_code, c("AGC", "GAG", "GAU"))
})
# Try with frame shift equal to tuple length

test_that('tuples are shifted correctly', {
  shifted_code <- shift_tuples(3, "CAGGGAUGA", tuple_length = 3)
  expect_equal(shifted_code, c("CAG", "GGA", "UGA"))
})

# Try with negative tuple size or tuple size 0
test_that('error is thrown', {
  expect_error(shift_tuples(1, "CAGGGAUGA", tuple_length = 0))
  expect_error(shift_tuples(1, "CAGGGAUGA", tuple_length = -2))
  expect_error(shift_tuples(1, "CAGGGAUGA", tuple_length = 1))
})


# Test code transformation

test_that('code is transformed correctly', {
  expect_equal(code_transform_tuples("1234", "2345","133422",tuple_length = 3 ), c("244","533"))
  # fails cause of incorrect order
  expect_equal(code_transform_tuples("FHGJ", "KLMN","GGHFJG",tuple_length = 2 ), c("MM","LK", "NM"))
  expect_equal(code_transform_tuples("k$.?", "1234", "k $ . $ ? . "),c("1","2", "3", "2", "4", "3", "1"))
})







