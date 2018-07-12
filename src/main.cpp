
#include <Rcpp.h>
#include "GCATCPP/codes/StdGenCode.h"

using namespace Rcpp;

std::vector <std::string> as_cpp_string_vector(StringVector r_vec);

// [[Rcpp::export]]
bool check_if_circular(StringVector code) {
  StdGenCode a(as_cpp_string_vector(code));
  return a.is_circular();
}

std::vector <std::string> as_cpp_string_vector(StringVector r_vec) {
  std::vector <std::string> vstrings(r_vec.size());
  int i;
  for (i = 0; i < r_vec.size(); i++) {
    vstrings[i] = Rcpp::as<std::string>(r_vec(i));
  }
  
  return vstrings;
}