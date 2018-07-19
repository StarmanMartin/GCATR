
#include <Rcpp.h>
#include "GCATCPP/codes/StdGenCode.h"

#include "RAdapterUtils.h"


using namespace Rcpp;

std::vector <std::string> as_cpp_string_vector(StringVector r_vec);




// [[Rcpp::export]]
bool check_if_circular(StringVector code) {
  StdGenCode a(RAdapterUtils::as_cpp_string_vector(code));
  return a.is_circular();
}

// [[Rcpp::export]]
StringVector get_acid(StringVector code) {
  StdGenCode a(RAdapterUtils::as_cpp_string_vector(code));
  return acid::acid_to_string(a.get_acid());;
}

