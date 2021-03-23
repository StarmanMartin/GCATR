#include <Rcpp.h>


#include "GCATCPP/geneticCode/CodonClusteringAlgorithm.h"
 

using namespace gen_codes;



RCPP_MODULE(CodonClusteringAlgorithm){
  using namespace Rcpp;
  //' CodonClusteringAlgorithm object
  class_<CodonClusteringAlgorithm>("CodonClusteringAlgorithm")
    .constructor<std::vector<std::string>>()
    .method( "get_average_conductance", &CodonClusteringAlgorithm::get_average_conductance)
    .method( "get_conductance_of_cluster", &CodonClusteringAlgorithm::get_conductance_of_cluster )
    .method( "get_min_conductance", &CodonClusteringAlgorithm::get_min_conductance )
    .method( "get_max_conductance", &CodonClusteringAlgorithm::get_max_conductance )
    .method( "r_add_weight", &CodonClusteringAlgorithm::r_add_weight );
}

