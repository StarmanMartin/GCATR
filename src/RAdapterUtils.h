//
// Created by Martin on 19.07.2018.
//

#ifndef GCATCPP_RADAPTERUTILS_H
#define GCATCPP_RADAPTERUTILS_H

#define TUPLE_LENGTH_EMPTY -55555

#include <Rcpp.h>
#include <memory>
#include "GCATCPP/codes/Acid.h"
#include "GCATCPP/codes/AbstractGenCode.h"
#include "GCATCPP/codes/AbstractCode.h"

using namespace Rcpp;

class RAdapterUtils {
public:
  
  static std::vector <std::string> as_cpp_string_vector(StringVector r_vec);
  static StringVector as_r_string_vector(const std::vector <std::string> &);
  
  static Rcpp::List as_R_matrix(std::vector<std::vector<std::string> > );
  
  static acid::acids string_to_acid(std::string );
  
  static std::shared_ptr<AbstractGenCode> factorGenCodeWrapper(std::vector <std::string> cVec, int tuple_length);
  static std::shared_ptr<AbstractCode> factorCodeWrapper(std::vector <std::string> cVec, int tuple_length);
};


#endif //GCATCPP_RADAPTERUTILS_H
