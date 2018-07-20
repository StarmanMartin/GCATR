
#include <Rcpp.h>
#include "GCATCPP/codes/StdGenCode.h"
#include "GCATCPP/miner/LongestPathMiner.h"
#include "GCATCPP/miner/CircleMiner.h"


#include "RAdapterUtils.h"


using namespace Rcpp;

std::vector <std::string> as_cpp_string_vector(StringVector r_vec);


// [[Rcpp::export]]
bool check_if_circular(StringVector code) {
  StdGenCode a(RAdapterUtils::as_cpp_string_vector(code));
  return a.is_circular();
}

// [[Rcpp::export]]
bool check_if_cn_circular(StringVector code) {
  StdGenCode a(RAdapterUtils::as_cpp_string_vector(code));
  return a.is_cn_circular();
}

// [[Rcpp::export]]
bool check_if_comma_free(StringVector code) {
  StdGenCode a(RAdapterUtils::as_cpp_string_vector(code));
  return a.is_comma_free();
}

// [[Rcpp::export]]
bool check_if_self_complementary(StringVector code) {
  StdGenCode a(RAdapterUtils::as_cpp_string_vector(code));
  return a.is_self_complementary();
}

// [[Rcpp::export]]
StringVector get_acid(StringVector code) {
  StdGenCode a(RAdapterUtils::as_cpp_string_vector(code));
  return acid::acid_to_string(a.get_acid());;
}

// [[Rcpp::export]]
StringVector get_one_logest_path_as_vector(StringVector code) {
  StdGenCode gc(RAdapterUtils::as_cpp_string_vector(code));
  auto longest_path_collection = miner::LongestPathMiner::mine_path_as_vector(&gc);
  if(longest_path_collection.size() == 0) {
    gc.print_errors();
    return {};
  }
  return RAdapterUtils::as_r_string_vector(longest_path_collection[0]);
}

// [[Rcpp::export]]
Rcpp::List get_all_logest_path_as_vector(StringVector code) {
  StdGenCode gc(RAdapterUtils::as_cpp_string_vector(code));
  auto longest_path_collection = miner::LongestPathMiner::mine_path_as_vector(&gc);
  if(longest_path_collection.size() == 0) {
    gc.print_errors();
    return {};
  }
  return RAdapterUtils::as_R_matrix(longest_path_collection);
}

// [[Rcpp::export]]
StringVector get_one_circle_as_vector(StringVector code) {
  StdGenCode gc(RAdapterUtils::as_cpp_string_vector(code));
  auto circle_path_collection = miner::CircleMiner::mine_path_as_vector(&gc);
  if(circle_path_collection.size() == 0) {
    gc.print_errors();
    return {};
  }
  return RAdapterUtils::as_r_string_vector(circle_path_collection[0]);
}

// [[Rcpp::export]]
Rcpp::List get_all_circle_as_vector(StringVector code) {
  StdGenCode gc(RAdapterUtils::as_cpp_string_vector(code));
  auto circle_path_collection = miner::CircleMiner::mine_path_as_vector(&gc);
  if(circle_path_collection.size() == 0) {
    gc.print_errors();
    return {};
  }
  return RAdapterUtils::as_R_matrix(circle_path_collection);
}

