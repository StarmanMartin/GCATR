library(testthat)
library(GCATR)

# code_factor_graph 
# with string vector
test_that("Graph contains correct edges", {
  edge_vector <- c("AC", "G", "A", "CG", "UA", "U", "U", "AU")
  sorted_edge_vector <- sort(edge_vector)
  sorted_factored_graph <- sort(as_edgelist(code_factor_graph(c("ACG", "UAU"))))
  expect_equal(sorted_edge_vector, sorted_factored_graph)
 })

test_that("Graph contains correct edges", {
  edges <- as_edgelist(code_factor_graph(c("AGU","GUC","UGA")))
  sorted_edge_vector <- sort(edges)
  sorted_factored_graph <- sort(as_edgelist(code_factor_graph(c("AGU","GUC","UGA"))))
  expect_equal(sorted_factored_graph, sorted_edge_vector)
})

# with string with tuple length
test_that("Graph contains correct edges", {
  edge_vector <- c("AC", "G", "A", "CG", "UA", "U", "U", "AU")
  sorted_edge_vector <- sort(edge_vector)
  sorted_factored_graph <- sort(as_edgelist(code_factor_graph("ACGUAU", tuple_length = 3)))
  expect_equal(sorted_edge_vector, sorted_factored_graph)
})

# with string split by " "
test_that("Graph contains correct edges", {
  edge_vector <- c("AC", "G", "A", "CG", "UA", "U", "U", "AU")
  sorted_edge_vector <- sort(edge_vector)
  sorted_factored_graph <- sort(as_edgelist(code_factor_graph("ACG UAU")))
  expect_equal(sorted_edge_vector, sorted_factored_graph)
})


# Test code_factor_cycle
# test with string vector
test_that("Graph/Tuples that violates the rules of circular codes is returned", {
  edges <- as_ids(E(code_factor_cycle(c("UGG", "GUG"))))
  edge_vector <- c("UG|G", "G|UG")
  sorted_edge_vector <- sort(edge_vector)
  sorted_factored_cycle <- sort(edges)
  expect_equal(sorted_edge_vector, sorted_factored_cycle)
})

# test with string split by " "
test_that("Graph/Tuples that violate the rules of ciruclar codes are returned", {
  edges <- as_ids(E((code_factor_cycle("UGG CUG GGC UGU"))))
  edge_vector <- c("U|GG", "C|UG", "GG|C", "UG|U")
  sorted_edge_vector <- sort(edge_vector)
  sorted_factored_cyle <- sort(edges)
  expect_equal(sorted_factored_cyle, sorted_edge_vector)
})

# test with string with tuple length
test_that("Graph/Tuples that violates the rules of ciruclar codes is returned", {
  edges <- as_ids(E((code_factor_cycle("UGGCUGGGCUGU", tuple_length = 3))))
  edge_vector <- c("U|GG", "C|UG", "GG|C", "UG|U")
  sorted_edge_vector <- sort(edge_vector)
  sorted_factored_cyle <- sort(edges)
  expect_equal(sorted_factored_cyle, sorted_edge_vector)
})

test_that("Circuclar code returns NULL", {
  G <- code_factor_cycle("GGUGGCACUACCAGCAGUGACGAUGUCGUUAAUAUUAACAUCGCUGCC", 3)
  expect_null(G)
})

# code_factor_longest_path
test_that("No longest path found as path would be infinite", {
  expect_null(code_factor_longest_path("UGGGUG", 3))
})

test_that("Longest path has correct length", {
  G <- code_factor_longest_path("ACG GCA AAG")
  dist <- distances(G)
  dist <- do.call(data.frame, lapply(dist, function(x) {
    replace(x, is.infinite(x) | is.na(x), 0)
  })
  )
  expect_equal(max(dist), 2)
})

test_that("Longest path has correct length", {
  G <- code_factor_longest_path("ACG GCA AAG CGG")
  dist <- distances(G)
  dist <- do.call(data.frame, lapply(dist, function(x) {
    replace(x, is.infinite(x) | is.na(x), 0)
  })
  )
  expect_equal(max(dist), 4)
})

test_that("Code has circle and thus no longest path", {
  G <- code_factor_longest_path("AGCGGATCTT",2)
  expect_null(G)
})

# code_get_one_cycles_as_vector
# with string vector
test_that("correct edges are contained", {
  sorted_edges <- sort(code_get_one_cycles_as_vector(c("UGG","CUG","GGC","UGU")))
  edge_vector <- c("U", "GG", "C", "UG", "U")
  sorted_edge_vector <- sort(edge_vector)
  expect_equal(sorted_edges, sorted_edge_vector)
})

test_that("circular code returns empty vector", {
  vector <- code_get_one_cycles_as_vector("GGUGGCACUACCAGCAGUGACGAUGUCGUUAAUAUUAACAUCGCUGCC", 3)
  expect_length(vector,0)
})

#with string split by " "
test_that("correct edges are contained", {
  sorted_edges <- sort(code_get_one_cycles_as_vector("UGG CUG GGC UGU"))
  edge_vector <- c("U", "GG", "C", "UG", "U")
  sorted_edge_vector <- sort(edge_vector)
  expect_equal(sorted_edges, sorted_edge_vector)
})

# string with tuple length
test_that("correct edges are contained", {
  sorted_edges <- sort(code_get_one_cycles_as_vector("UGGGUG", tuple_length = 3))
  edge_vector <- c("UG", "G", "UG")
  sorted_edge_vector <- sort(edge_vector);
  expect_equal(sorted_edge_vector, sorted_edges)
})

# code_get_all_cycles_as_vector
# with string vector
test_that("correct edges are contained", {
  edge_list <- code_get_all_cycles_as_vector(c("AG","CG","GA","TC","TT"))
  first_circle <- c("A", "G", "A")
  second_circle <- c("T", "T")
  expect_equal(unlist(edge_list[1]), first_circle)
  expect_equal(unlist(edge_list[2]), second_circle)
})

#with string split by " "
test_that("correct edges are contained", {
  edge_list <- code_get_all_cycles_as_vector("AG CG GA TC TT")
  first_circle <- c("A", "G", "A")
  second_circle <- c("T", "T")
  expect_equal(unlist(edge_list[1]), first_circle)
  expect_equal(unlist(edge_list[2]), second_circle)
})

# string with tuple length
test_that("correct edges are contained", {
  edge_list <- code_get_all_cycles_as_vector("AGCGGATCTT", tuple_length = 2)
  first_circle <- c("A", "G", "A")
  second_circle <- c("T", "T")
  expect_equal(unlist(edge_list[1]), first_circle)
  expect_equal(unlist(edge_list[2]), second_circle)
})

test_that("circular code returns empty vector", {
  vectorList <- code_get_all_cycles_as_vector("GGUGGCACUACCAGCAGUGACGAUGUCGUUAAUAUUAACAUCGCUGCC", 3)
  expect_length(vectorList,0)
})


#code_get_one_longest_path_as_vector
# string split by " "
test_that("correct edges are contained", {
  longest_path <- code_get_one_longest_path_as_vector("ACG GCA AAG")
  vector <- c("AC", "G", "CA")
  expect_equal(longest_path, vector)
})

# string as vector
test_that("correct edges are contained", {
  longest_path <- code_get_one_longest_path_as_vector(c("ACG","GCA", "AAG"))
  vector <- c("AC", "G", "CA")
  expect_equal(longest_path, vector)
})

#string with tuple length
test_that("correct edges are contained", {
  longest_path <- code_get_one_longest_path_as_vector("ACGGCAAAG", 3)
  vector <- c("AC", "G", "CA")
  expect_equal(longest_path, vector)
})

test_that("code that has circle does return empty vector", {
  vector <- code_get_one_longest_path_as_vector("AGCGGATCTT",2)
  expect_length(vector,0)
})

# code_get_all_longest_path_as_vector
# test with string vector

test_that("correct longest paths are returned", {
  edge_list <- code_get_all_longest_path_as_vector("ATG GTA")
  first_path <- c("AT", "G", "TA")
  second_path <- c("GT", "A", "TG")
  expect_equal(unlist(edge_list[1]), first_path)
  expect_equal(unlist(edge_list[2]), second_path)
})
# string split by " "
test_that("correct longest paths are returned", {
  edge_list <- code_get_all_longest_path_as_vector("ACG GCA AAG")
  first_path <- c("AC", "G", "CA")
  second_path <- c("GC", "A", "AG")
  third_path <- c("GC", "A", "CG")
  fourth_path <- c("AA", "G", "CA")
  expect_equal(unlist(edge_list[1]), first_path)
  expect_equal(unlist(edge_list[2]), second_path)
  expect_equal(unlist(edge_list[3]), third_path)
  expect_equal(unlist(edge_list[4]), fourth_path)
})

# string with tuple length
test_that("correct longest paths are returned", {
  edge_list <- code_get_all_longest_path_as_vector("ACGGCAAAG", 3)
  first_path <- c("AC", "G", "CA")
  second_path <- c("GC", "A", "AG")
  third_path <- c("GC", "A", "CG")
  fourth_path <- c("AA", "G", "CA")
  expect_equal(unlist(edge_list[1]), first_path)
  expect_equal(unlist(edge_list[2]), second_path)
  expect_equal(unlist(edge_list[3]), third_path)
  expect_equal(unlist(edge_list[4]), fourth_path)
})

test_that("code that has circle does return empty list", {
  vector <- code_get_one_longest_path_as_vector("AGCGGATCTT",2)
  expect_length(vector,0)
})





