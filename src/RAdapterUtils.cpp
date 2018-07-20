//
// Created by Martin on 19.07.2018.
//

#include "RAdapterUtils.h"

std::vector <std::string> RAdapterUtils::as_cpp_string_vector(StringVector r_vec) {
  std::vector <std::string> vstrings(r_vec.size());
  int i;
  for (i = 0; i < r_vec.size(); i++) {
    vstrings[i] = Rcpp::as<std::string>(r_vec(i));
  }
  
  return vstrings;
}

StringVector RAdapterUtils::as_r_string_vector(std::vector <std::string> r_vec) {
  return wrap(r_vec);
}

Rcpp::List RAdapterUtils::as_R_matrix(std::vector<std::vector<std::string> >r_vec ) {
  return wrap( r_vec );
  
}