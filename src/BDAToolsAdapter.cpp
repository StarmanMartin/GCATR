#include <Rcpp.h>
#include <memory>

#include "RAdapterUtils.h"

#include "GCATCPP/bda/BDATools.h"
#include "GCATCPP/codes/StdGenCode.h"
using namespace Rcpp;

// This is a simple example of exporting a C++ function to R. You can
// source this function into an R session using the Rcpp::sourceCpp 
// function (or via the Source button on the editor toolbar). Learn
// more about Rcpp at:
//
//   http://www.rcpp.org/
//   http://adv-r.had.co.nz/Rcpp.html
//   http://gallery.rcpp.org/
//

BDA::BDATools* main_bda_ptr = (BDA::BDATools*) NULL;


// [[Rcpp::export]]
bool add_bda_rule(int i_1, int i_2, std::string Q_11, std::string Q_12, std::string Q_21, std::string Q_22) {
  if(main_bda_ptr == NULL) {
    Rcpp::Rcerr << "Run BDA constructer for code first: " << " start_bda_for_code(StringVector) " << "\n";
    return false;
  }
  
  if(Q_11.length() != 1 || Q_12.length()!= 1 || Q_21.length()!= 1 || Q_22.length()!= 1) {
    Rcpp::Rcerr << "Q_11, Q_12, Q_21, Q_22 have to be a single letter: " << "A, C, G, T, U" << "\n";
    return false;
  }
  
  auto return_val = main_bda_ptr->add_rule((unsigned)i_1, (unsigned)i_2, Q_11[0], Q_12[0], Q_21[0], Q_22[0]);
  main_bda_ptr->print_errors();
  return return_val;
}

// [[Rcpp::export]]
bool start_bda_for_code(StringVector code) {
  auto a = std::make_shared<StdGenCode>(RAdapterUtils::as_cpp_string_vector(code));
  if(!a->test_code()) {
    return false;
  }
  
  if(main_bda_ptr != NULL) {
    delete main_bda_ptr;
  }
  
  a->print_errors();
  
  main_bda_ptr = new BDA::BDATools(a);
  
  return true;
}

// [[Rcpp::export]]
StringVector run_bda() {
  
  if(main_bda_ptr == NULL) {
    Rcpp::Rcerr << "Run BDA constructer for code first: " << " start_bda_for_code(StringVector) " << "\n";
    return {};
  }
  
  auto return_val = RAdapterUtils::as_r_string_vector(main_bda_ptr->run_bda_for_code());
  main_bda_ptr->print_errors();
  return return_val;
}