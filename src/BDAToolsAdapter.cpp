#include <Rcpp.h>


#include "GCATCPP/bda/BDATools.h"


using namespace BDA;
using namespace Rcpp;

class BdaRObj;
RCPP_EXPOSED_CLASS(BDA::BDATools);

BDA::BDATools* main_bda_ptr = nullptr;


RCPP_MODULE(BDATools){
  using namespace Rcpp;
  
  class_<BDATools>("BDATools")
    .constructor<std::string, int>()
    .method( "run_bda_for_code", &BDATools::run_bda_for_code)
    .method( "get_tuples", &BDATools::get_tuples )
    .method( "add_rule", &BDATools::r_add_rule );

}