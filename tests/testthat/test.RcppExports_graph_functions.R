library(testthat)
library(GCATR)

# Test function code_factor_graph 


# with string vector
test_that("Graph contains correct edges", {
  edge_matrix <- matrix(nrow = 4, ncol = 2)
  edge_matrix[1,] = c("AC","G")
  edge_matrix[2, ] = c("A", "CG")
  edge_matrix[3,] = c("UA", "U")
  edge_matrix[4,] = c("U", "AU")
  expect_equal(as_edgelist(code_factor_graph(c("ACG", "UAU"))), edge_matrix)
 })

# Order is jumbled for whatever reason thus not matching
test_that("Graph contains correct edges", {
  edges <- as_edgelist(code_factor_graph(c("AGU","GUC","UGA")))
  edge_matrix <- matrix(nrow = 6, ncol = 2)
  edge_matrix[1,] = c("AG","U")
  edge_matrix[2, ] = c("A", "GU")
  edge_matrix[3,] = c("GU", "C")
  edge_matrix[4,] = c("G", "UC")
  edge_matrix[5,] = c("UG", "A")
  edge_matrix[6,] = c("U", "GA")
  expect_equal(as_edgelist(code_factor_graph(c("AGU","GUC","UGA"))), edge_matrix)
})

# with string with tuple length
test_that("Graph contains correct edges", {
  edge_matrix <- matrix(nrow = 4, ncol = 2)
  edge_matrix[1,] = c("AC","G")
  edge_matrix[2, ] = c("A", "CG")
  edge_matrix[3,] = c("UA", "U")
  edge_matrix[4,] = c("U", "AU")
  expect_equal(as_edgelist(code_factor_graph(c("ACGUAU"), tuple_length = 3)), edge_matrix)
})

# with string split by " "
test_that("Graph contains correct edges", {
  edge_matrix <- matrix(nrow = 4, ncol = 2)
  edge_matrix[1,] = c("AC","G")
  edge_matrix[2, ] = c("A", "CG")
  edge_matrix[3,] = c("UA", "U")
  edge_matrix[4,] = c("U", "AU")
  expect_equal(as_edgelist(code_factor_graph(c("ACG UAU"))), edge_matrix)
})


# Test code_factor_cycle
# test with string vector
test_that("Graph/Tuples that violates the rules of ciruclar codes is returned", {
  G <- code_factor_cycle(c("UGG", "GUG"))
  edge_matrix <- matrix(nrow = 2, ncol = 2)
  edge_matrix[1,] = c("UG","G")
  edge_matrix[2, ] = c("G", "UG")
  expect_equal(as_edgelist(code_factor_cycle(c("UGG", "GUG"))), edge_matrix)
})

# test with string split by " "
test_that("Graph/Tuples that violates the rules of ciruclar codes is returned", {
  G <- code_factor_cycle("UGG CUG GGC UGU")
  edge_matrix <- matrix(nrow = 4, ncol = 2)
  edge_matrix[1,] = c("U","GG")
  edge_matrix[2, ] = c("C", "UG")
  edge_matrix[3,] = c("GG","C")
  edge_matrix[4, ] = c("UG", "U")
  expect_equal(as_edgelist(code_factor_cycle("UGG CUG GGC UGU")), edge_matrix)
})

# test with string with tuple length
test_that("Graph/Tuples that violates the rules of ciruclar codes is returned", {
  G <- code_factor_cycle("UGGCUGGGCUGU", 3)
  edge_matrix <- matrix(nrow = 4, ncol = 2)
  edge_matrix[1,] = c("U","GG")
  edge_matrix[2, ] = c("C", "UG")
  edge_matrix[3,] = c("GG","C")
  edge_matrix[4, ] = c("UG", "U")
  expect_equal(as_edgelist(code_factor_cycle("UGG CUG GGC UGU")), edge_matrix)
})

test_that("Ciruclar code returns NULL", {
  G <- code_factor_cycle("GGUGGCACUACCAGCAGUGACGAUGUCGUUAAUAUUAACAUCGCUGCC", 3)
  expect_null(G)
})

# code_factor_longest_path
# I do not fully understand what this function is supposed to do
G <- code_factor_longest_path(c("ACG", "CAG"))
tkplot(G)


# code_factor_c3plot
# I do not fully understand what this function is supposed to do
test_that("Graph contains correct edges", {
  
})

# code_prepare_factor_graph

test_that("Correct edges and vertices are contained", {
  GCATR::code_
  code_prepare_factor_graph(c("ACG", "CAG"), TRUE, TRUE)

  
})



