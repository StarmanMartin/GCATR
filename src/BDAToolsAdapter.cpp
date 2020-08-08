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