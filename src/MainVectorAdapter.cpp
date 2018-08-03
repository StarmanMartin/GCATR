
#include <Rcpp.h>
#include "GCATCPP/codes/StdGenCode.h"
#include "GCATCPP/miner/LongestPathMiner.h"
#include "GCATCPP/miner/CircleMiner.h"


#include "RAdapterUtils.h"


using namespace Rcpp;

//' Check if a code is circular.
//' 
//' This function checks if a genetic code is circular.
//' Circular codes in gens for retrieving the reading frames of genes.
//' \emph{2007 Christian MICHEL. CIRCULAR CODES IN GENES}
//'
//' @param code A vertor with codons.
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

//' Check if a code is C_{n} circular.
//' 
//' This function checks the same property as \code{\link{check_if_circular}}. 
//' Yet,  this function checks the property for for all circular permutations of the codons in the code.
//' \emph{2007 Christian MICHEL. CIRCULAR CODES IN GENES}
//'
//' @param code A vertor with codons.
//' @return Boolean value. True if the code C_{n} circular.
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
//' \emph{2007 Christian MICHEL. CIRCULAR CODES IN GENES}
//'
//' @param code A vertor with codons.
//' @return Boolean value. True if the code self complementary.
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
//' any codon (word) the corresponding anti-codons. 
//' \emph{2007 Christian MICHEL. CIRCULAR CODES IN GENES}
//'
//' @param code A vertor with codons.
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

//' Check if a code is self complementary.
//' 
//' The function checks if the code is self complementary. A self complementary code contains for 
//' any codon (word) the corresponding anti-codons. 
//' \emph{2007 Christian MICHEL. CIRCULAR CODES IN GENES}
//'
//' @param code A vertor with codons.
//' @return Boolean value. True if the code self complementary.
//' @examples
//' code_check_if_self_complementary(c("ACG", "CAG"))
//' 
//' @export
// [[Rcpp::export]]
StringVector code_get_acid(StringVector code) {
  StdGenCode a(RAdapterUtils::as_cpp_string_vector(code));
  return acid::acid_to_string(a.get_acid());;
}

//' Check if a code is self complementary.
//' 
//' The function checks if the code is self complementary. A self complementary code contains for 
//' any codon (word) the corresponding anti-codons. 
//' \emph{2007 Christian MICHEL. CIRCULAR CODES IN GENES}
//'
//' @param code A vertor with codons.
//' @return Boolean value. True if the code self complementary.
//' @examples
//' code_check_if_self_complementary(c("ACG", "CAG"))
//' 
//' @export
// [[Rcpp::export]]
StringVector code_get_one_logest_path_as_vector(StringVector code) {
  StdGenCode gc(RAdapterUtils::as_cpp_string_vector(code));
  auto longest_path_collection = miner::LongestPathMiner::mine_path_as_vector(&gc);
  if(longest_path_collection.size() == 0) {
    gc.print_errors();
    return {};
  }
  return RAdapterUtils::as_r_string_vector(longest_path_collection[0]);
}

//' Check if a code is self complementary.
//' 
//' The function checks if the code is self complementary. A self complementary code contains for 
//' any codon (word) the corresponding anti-codons. 
//' \emph{2007 Christian MICHEL. CIRCULAR CODES IN GENES}
//'
//' @param code A vertor with codons.
//' @return Boolean value. True if the code self complementary.
//' @examples
//' code_check_if_self_complementary(c("ACG", "CAG"))
//' 
//' @export
// [[Rcpp::export]]
Rcpp::List code_get_all_logest_path_as_vector(StringVector code) {
  StdGenCode gc(RAdapterUtils::as_cpp_string_vector(code));
  auto longest_path_collection = miner::LongestPathMiner::mine_path_as_vector(&gc);
  if(longest_path_collection.size() == 0) {
    gc.print_errors();
    return {};
  }
  return RAdapterUtils::as_R_matrix(longest_path_collection);
}

//' Check if a code is self complementary.
//' 
//' The function checks if the code is self complementary. A self complementary code contains for 
//' any codon (word) the corresponding anti-codons. 
//' \emph{2007 Christian MICHEL. CIRCULAR CODES IN GENES}
//'
//' @param code A vertor with codons.
//' @return Boolean value. True if the code self complementary.
//' @examples
//' code_check_if_self_complementary(c("ACG", "CAG"))
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

//' Returns a list of circles as vectors.
//' 
//' The function checks if the code is circular. If the code is not circular the functions returns all circles. 
//' \emph{2007 Christian MICHEL. CIRCULAR CODES IN GENES}
//'
//' @param code A vertor with codons.
//' @return List of string vectors.
//' @examples
//' code_get_all_circle_as_vector(c("ACG", "CAG"))
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

