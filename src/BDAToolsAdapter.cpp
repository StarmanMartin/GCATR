#include <Rcpp.h>


#include "GCATCPP/bda/BDATools.h"


using namespace BDA;
using namespace Rcpp;

RCPP_EXPOSED_CLASS(BDA::BDATools);

// Approach 4: Module docstrings
RCPP_MODULE(BDATools){
  using namespace Rcpp;
  //' BDA object
  class_<BDATools>("BDATools")
    .constructor<std::string, int>("BDA tool update 2")
    .method( "run_bda_for_code", &BDATools::run_bda_for_code)
    .method( "get_tuples", &BDATools::get_tuples )
    .method( "add_rule", &BDATools::r_add_rule );

}

//' Tuple Generator: get_all_rna_tuples
//' 
//' Generats a lexically sorted list of all tuples over the RNA Alphabet of length tuple_size
//' 
//' @return A lexically sorted list of all tuples over the RNA Alphabet of length tuple_size\cr
//' 
//' @param tuple_length a number, the length of the block or tuple used 
//' 
//' @examples
//' res <- get_all_rna_tuples(3)
//' 
//' @export
// [[Rcpp::export]]
Rcpp::StringVector get_all_rna_tuples(int tuple_length) {
  return Rcpp::wrap(BDATools::get_all_rna_tuples(tuple_length));
}