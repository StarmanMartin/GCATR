
#include <Rcpp.h>
#include "GCATCPP/codes/StdGenCode.h"
#include "GCATCPP/miner/LongestPathMiner.h"
#include "GCATCPP/miner/CircleMiner.h"


#include "RAdapterUtils.h"


using namespace Rcpp;

//' Check if a DNA/RNA code is circular.
//' 
//' This function checks if a genetic code is circular.
//' Circular codes is an approach for finding the method used in gens for retrieving the correct reading frames.\cr
//' For more info on this subject read:\cr
//' \link{https://www.ncbi.nlm.nih.gov/pmc/articles/PMC5492142/},\cr
//' \link{http://dpt-info.u-strasbg.fr/~c.michel/Circular_Codes.pdf},\cr
//' \emph{2007 Christian MICHEL. CIRCULAR CODES IN GENES}
//'
//' @param code is a DNA or RNA code as string vector.
//' @return Boolean value. True if the code is circular.
//' @examples
//' code_check_if_circular(c("ACG", "CAG"))
//' 
//' @export 
// [[Rcpp::export]]
bool code_check_if_circular(StringVector code) {
  StdGenCode a(RAdapterUtils::as_cpp_string_vector(code));
  return a.is_circular();
}

//' Check if a DNA/RNA code is cn circular.
//'
//' This function checks if a genetic code is cn circular.
//' Circular codes is an approach for finding the method used in gens for retrieving the correct reading frames.
//' For a code to be cn circular means that each circular permutation of all codons construct a new circular code.
//' For more info on this subject read:\cr
//' \link{https://www.ncbi.nlm.nih.gov/pmc/articles/PMC5492142/},\cr
//' \link{http://dpt-info.u-strasbg.fr/~c.michel/Circular_Codes.pdf},\cr
//' \emph{2007 Christian MICHEL. CIRCULAR CODES IN GENES}
//'
//' @param code is a DNA or RNA code as string vector.
//' @return Boolean value. True if the code is cn circular.
//' @examples
//' code_check_if_cn_circular(c("ACG", "CAG"))
//' 
//' @export 
// [[Rcpp::export]]
bool code_check_if_cn_circular(StringVector code) {
  StdGenCode a(RAdapterUtils::as_cpp_string_vector(code));
  return a.is_cn_circular();
}

//' Check if a code is comma free.
//' 
//' The function checks if the code is comma free. 
//' Comma free is a stronger restricted version of the circular code property.
//' For more info on this subject read:\cr
//' \link{https://www.ncbi.nlm.nih.gov/pmc/articles/PMC5492142/},\cr
//' \link{http://dpt-info.u-strasbg.fr/~c.michel/Circular_Codes.pdf},\cr
//' \emph{2007 Christian MICHEL. CIRCULAR CODES IN GENES}
//'
//' @param code is a DNA or RNA code as string vector.
//' @return Boolean value. True if the code comma free.
//' @examples
//' code_check_if_comma_free(c("ACG", "CAG"))
//' 
//' @export 
// [[Rcpp::export]]
bool code_check_if_comma_free(StringVector code) {
  StdGenCode a(RAdapterUtils::as_cpp_string_vector(code));
  return a.is_comma_free();
}



//' Check if a code is self complementary.
//' 
//' The function checks if the code is self complementary. A self complementary code contains for 
//' any codon (word) in the code the corresponding anti-codons.
//' For more info on this subject read:\cr
//' \link{https://www.ncbi.nlm.nih.gov/pmc/articles/PMC5492142/},\cr
//' \link{http://dpt-info.u-strasbg.fr/~c.michel/Circular_Codes.pdf},\cr
//' \emph{2007 Christian MICHEL. CIRCULAR CODES IN GENES}
//'
//' @param code A vector with codons.
//' @return Boolean value. True if the code self complementary.
//' @examples
//' code_check_if_self_complementary(c("ACG", "CAG"))
//' 
//' @export 
// [[Rcpp::export]]
bool code_check_if_self_complementary(StringVector code) {
  StdGenCode a(RAdapterUtils::as_cpp_string_vector(code));
  return a.is_self_complementary();
}

//' Get acid type of a code
//' 
//' Returns either RNA or DNA depending on the codes Bases. If the code contains only CYTOSINE (C), ADENINE (A), GUANINE (G)
//' the functions returns DNA. If the code contains THYMINE (T) it will also return DNA. On the other side, if the
//' the code contains URACIL (U) bases the function returns RNA. If the code contains URACIL (U) & THYMINE (T) or any other letter
//' then CYTOSINE (A), ADENINE (A), GUANINE (G), URACIL (U) or THYMINE (T) it will return NONE
//' For more info on this subject read:\cr
//' \link{https://www.ncbi.nlm.nih.gov/pmc/articles/PMC5492142/},\cr
//' \link{http://dpt-info.u-strasbg.fr/~c.michel/Circular_Codes.pdf},\cr
//' \emph{2007 Christian MICHEL. CIRCULAR CODES IN GENES}
//'
//' @param code A vector with codons.
//' @return String value. One of NONE, DNA, RNA
//' @examples
//' acid <- code_get_acid(c("ACG", "CAG"))
//' 
//' @export
// [[Rcpp::export]]
StringVector code_get_acid(StringVector code) {
  StdGenCode a(RAdapterUtils::as_cpp_string_vector(code));
  return acid::acid_to_string(a.get_acid());;
}

//' Finds one longest path constructable in a code.
//'
//' Prepares a R path string vector. Extracts all longest paths of the Graph G(X).
//' If the graph shows a cycle the vector will be empty. Otherwise it returns a vector with one longest path.\cr
//' \emph{2007 E. FIMMEL, C. J. MICHEL, AND L. STRÜNGMANN. N-nucleotide circular codes in graph theory}
//'
//' @seealso [code_factor_longest_path(code)] for code, [code_get_all_longest_path_as_vector()] for the results as list
//'
//' @param code A DNA or RNA code as string vector represented by the graph.
//' @examples
//' l_path <- code_get_one_circle_as_vector(c("ACG", "CGA"))
//'
//' @export
// [[Rcpp::export]]
StringVector code_get_one_longest_path_as_vector(StringVector code) {
  StdGenCode gc(RAdapterUtils::as_cpp_string_vector(code));
  auto longest_path_collection = miner::LongestPathMiner::mine_path_as_vector(&gc);
  if(longest_path_collection.size() == 0) {
    gc.print_errors();
    return {};
  }
  return RAdapterUtils::as_r_string_vector(longest_path_collection[0]);
}

//' Finds all longest path constructable in a code.
//'
//' Prepares a List of R path string vector. Extracts all longest path of the Graph G(X).
//' If the graph shows a cycle the list will be empty. Otherwise it returns a list object containing vectors with all
//' longest paths.\cr
//' \emph{2007 E. FIMMEL, C. J. MICHEL, AND L. STRÜNGMANN. N-nucleotide circular codes in graph theory}
//'
//' @seealso [code_factor_longest_path(code)] for code, [code_get_one_longest_path_as_vector()] for one result as vector
//'
//' @param code A DNA or RNA code as string vector represented by the graph.
//' @examples
//' l_path_list <- code_get_all_circle_as_vector(c("ACG", "CGA"))
//'
//' @export
// [[Rcpp::export]]
Rcpp::List code_get_all_longest_path_as_vector(StringVector code) {
  StdGenCode gc(RAdapterUtils::as_cpp_string_vector(code));
  auto longest_path_collection = miner::LongestPathMiner::mine_path_as_vector(&gc);
  if(longest_path_collection.size() == 0) {
    gc.print_errors();
    return {};
  }
  return RAdapterUtils::as_R_matrix(longest_path_collection);
}

//' Finds one circle constructable in a code.
//'
//' Prepares a R path string vector. Extracts all circle path of the Graph G(X).
//' If the graph shows no cycle the vector will be empty. Otherwise it returns a vector with one
//' circle paths.\cr
//' \emph{2007 E. FIMMEL, C. J. MICHEL, AND L. STRÜNGMANN. N-nucleotide circular codes in graph theory}
//'
//' @seealso [code_factor_circles(code)] for code, [code_get_all_circle_as_vector()] for the results as list
//'
//' @param code A DNA or RNA code as string vector represented by the graph.
//' @examples
//' l_path <- code_get_one_circle_as_vector(c("ACG", "CGA"))
//'
//' @export
// [[Rcpp::export]]
StringVector code_get_one_circle_as_vector(StringVector code) {
  StdGenCode gc(RAdapterUtils::as_cpp_string_vector(code));
  auto circle_path_collection = miner::CircleMiner::mine_path_as_vector(&gc);
  if(circle_path_collection.size() == 0) {
    gc.print_errors();
    return {};
  }
  return RAdapterUtils::as_r_string_vector(circle_path_collection[0]);
}

//' Finds all circles constructable in a code.
//'
//' Prepares a List of R path string vector. Extracts all circle path of the Graph G(X).
//' If the graph shows no cycle the list will be empty. Otherwise it returns a list object containing vectors with all
//' circle paths.\cr
//' \emph{2007 E. FIMMEL, C. J. MICHEL, AND L. STRÜNGMANN. N-nucleotide circular codes in graph theory}
//'
//' @seealso [code_factor_circles(code)] for code, [code_get_one_circle_as_vector()] for one result as vector
//'
//' @param code A DNA or RNA code as string vector represented by the graph.
//' @examples
//' c_path_list <- code_get_all_circle_as_vector(c("ACG", "CGA"))
//'
//' @export
// [[Rcpp::export]]
Rcpp::List code_get_all_circle_as_vector(StringVector code) {
  StdGenCode gc(RAdapterUtils::as_cpp_string_vector(code));
  auto circle_path_collection = miner::CircleMiner::mine_path_as_vector(&gc);
  if(circle_path_collection.size() == 0) {
    gc.print_errors();
    return {};
  }
  return RAdapterUtils::as_R_matrix(circle_path_collection);
}

//' Returns all DNA bases
//'
//' @return {"T", "C", "A", "G"}
//' @export 
// [[Rcpp::export]]
Rcpp::StringVector get_dna_bases() {
  std::vector<std::string> result(acid::acid_base_length);
  for(int i = 0; i < acid::acid_base_length; ++i) {
    result[i] = acid::dna[i];
  }
  
  return RAdapterUtils::as_r_string_vector(result);
}

//' Returns all DNA bases
//'
//' @return {"U", "C", "A", "G"}
//' @export
// [[Rcpp::export]]
Rcpp::StringVector get_rna_bases() {
  std::vector<std::string> result(acid::acid_base_length);
  for(int i = 0; i < acid::acid_base_length; ++i) {
    result[i] = acid::rna[i];
  }
  
  return RAdapterUtils::as_r_string_vector(result);
}

//' Analysis a sequence based on a generic code.
//'
//' Finds all appearance of a code ion a sequence. Finds the longest connected matches of words of the code in the sequence.
//' The function also calculates the matching bases of the found words in the sequence.
//'
//' @return Returns a List with all analysing results. The list contains following:\cr
//' \emph{words} all found words of the code in the sequence in the correct order.\cr
//' \emph{idx_list} the first-letter index of all found words of the code in the sequence in the correct order.\cr
//' \emph{rest} all parts of the sequence which are not matching the code.\cr
//' \emph{parts} the sequence separated in matching and non matching parts. Odd indexes are matching, even indexes are not matching.\cr
//' \emph{longest_match} the longest connected matching sequence.\cr
//' \emph{total_match_in_percent} the percentage of the matching parts.
//'
//' @param seq A DNA or RNA sequence.
//' @param code A DNA or RNA code as string vector represented by the graph.
//' @examples
//' code <- c("ACG", "TCG")
//' seq <- "ACGTCGCGACGTACGACGTCGTACTCGATGCAAGATC"
//' res <- find_amd_analysis_code_in_sequence(seq, code)
//'
//' @export
// [[Rcpp::export]]
Rcpp::List find_amd_analysis_code_in_sequence(std::string seq, StringVector code) {
  StdGenCode gc(RAdapterUtils::as_cpp_string_vector(code));
  auto res = gc.find_code_in_sequence(seq);

  return Rcpp::List::create(
    Rcpp::Named("word") = Rcpp::wrap(res.words),
    Rcpp::Named("idx_list") = Rcpp::wrap(res.idx_list),
    Rcpp::Named("rest") = Rcpp::wrap(res.rest),
    Rcpp::Named("parts") = Rcpp::wrap(res.parts),
    Rcpp::Named("longest_match") = res.longest_match,
    Rcpp::Named("total_match_in_percent") = res.total_match_in_percent);
}