#include <Rcpp.h>
using namespace Rcpp;

#include "GCATCPP/genericCode/CodonClusteringAlgorithm.h"
#include "GCATCPP/genericCode/CodonTranslTables.h"

#include "RAdapterUtils.h"

//' @export 
// [[Rcpp::export]]
double get_average_conductance_of_code(std::string codeName, std::string acid="DNA") {
  auto code = gen_codes::CodonTranslTables::getInstance().getCodeByName(codeName, RAdapterUtils::string_to_acid(acid));
  gen_codes::CodonClusteringAlgorithm cca(code);
  
  return cca.get_average_conductance();
}

//' @export 
// [[Rcpp::export]]
double get_max_conductance_of_code(std::string codeName, std::string acid="DNA") {
  auto code = gen_codes::CodonTranslTables::getInstance().getCodeByName(codeName, RAdapterUtils::string_to_acid(acid));
  gen_codes::CodonClusteringAlgorithm cca(code);
  
  return cca.get_max_conductance();
}

//' @export 
// [[Rcpp::export]]
double get_min_conductance_of_code(std::string codeName, std::string acid="DNA") {
  auto code = gen_codes::CodonTranslTables::getInstance().getCodeByName(codeName, RAdapterUtils::string_to_acid(acid));
  
  gen_codes::CodonClusteringAlgorithm cca(code);
  
  return cca.get_min_conductance();
}

//' @export 
// [[Rcpp::export]]
double get_average_conductance_of_codeidx(int codeIdx, std::string acid="DNA") {
  auto code = gen_codes::CodonTranslTables::getInstance().getCodeByIndex(codeIdx, RAdapterUtils::string_to_acid(acid));
  gen_codes::CodonClusteringAlgorithm cca(code);
  
  return cca.get_average_conductance();
}

//' @export 
// [[Rcpp::export]]
double get_max_conductance_of_codeidx(int codeIdx, std::string acid="DNA") {
  auto code = gen_codes::CodonTranslTables::getInstance().getCodeByIndex(codeIdx, RAdapterUtils::string_to_acid(acid));
  gen_codes::CodonClusteringAlgorithm cca(code);
  
  return cca.get_max_conductance();
}

//' @export 
// [[Rcpp::export]]
double get_min_conductance_of_codeidx(int codeIdx, std::string acid="DNA") {
  auto code = gen_codes::CodonTranslTables::getInstance().getCodeByIndex(codeIdx, RAdapterUtils::string_to_acid(acid));
  gen_codes::CodonClusteringAlgorithm cca(code);
  
  return cca.get_min_conductance();
}

//' @export 
// [[Rcpp::export]]
void print_all_translation_table() {
  auto code = gen_codes::CodonTranslTables::getInstance().getAllCodesText();
  Rcpp::Rcout << code;
}