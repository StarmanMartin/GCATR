//
// Created by Martin on 19.07.2018.
//

#include "RAdapterUtils.h"
#include <stdexcept>

std::vector <std::string> RAdapterUtils::as_cpp_string_vector(StringVector r_vec) {
  if(r_vec.length() == 0) {
      throw std::invalid_argument("Vector should not be empty!");
  }


  std::vector <std::string> vstrings(r_vec.size());
  int i;
  for (i = 0; i < r_vec.size(); i++) {
    vstrings[i] = Rcpp::as<std::string>(r_vec(i));
  }
  
  return vstrings;
}

StringVector RAdapterUtils::as_r_string_vector(const std::vector <std::string> &r_vec) {
  return wrap(r_vec);
}


Rcpp::List RAdapterUtils::as_R_matrix(std::vector<std::vector<std::string> >r_vec ) {
  return wrap( r_vec );
  
}

acid::acids RAdapterUtils::string_to_acid(std::string acid_name) {
  if( acid_name == "DNA") {
     return acid::acids::DNA;
  } 
  if( acid_name == "RNA") {
    return acid::acids::RNA;
  } 
  
  return acid::acids::NONE;
}