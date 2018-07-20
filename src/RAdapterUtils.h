//
// Created by Martin on 19.07.2018.
//

#ifndef GCATCPP_RADAPTERUTILS_H
#define GCATCPP_RADAPTERUTILS_H

#include <Rcpp.h>
using namespace Rcpp;

class RAdapterUtils {
public:
  static std::vector <std::string> as_cpp_string_vector(StringVector r_vec);
  static StringVector as_r_string_vector(std::vector <std::string>);
  
  static Rcpp::List as_R_matrix(std::vector<std::vector<std::string> > );
};


#endif //GCATCPP_RADAPTERUTILS_H
