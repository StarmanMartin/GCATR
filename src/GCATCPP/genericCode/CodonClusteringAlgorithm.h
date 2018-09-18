//
// Created by Martin on 18.09.2018.
//

#ifndef GCATCPP_CLUSTERINGALGORITHM_H
#define GCATCPP_CLUSTERINGALGORITHM_H

#include <string>
#include <map>
#include <vector>
#include <set>

namespace gen_codes {


    class CodonClusteringAlgorithm {
    public:
        explicit CodonClusteringAlgorithm(const std::vector<std::string> &);
        double get_average_conductance();
        double get_max_conductance();
        double get_min_conductance();

    private:
        std::map<std::pair<std::string, std::string>, int> cluster_table;
        std::map<std::string, double> class_conductance_values;
        std::set<std::string> all_acids;

        bool is_calculated;

        void calculate_cluster_table_for_code(const std::vector<std::string>& code);
        void calculate_conductance_values();
        static std::vector<int> all_acids_in_group(int idx);

    };

}

#endif //GCATCPP_CLUSTERINGALGORITHM_H
