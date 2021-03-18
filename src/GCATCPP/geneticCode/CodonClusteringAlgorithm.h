//
// Created by Martin on 18.09.2018.
//

#ifndef GCATCPP_CLUSTERINGALGORITHM_H
#define GCATCPP_CLUSTERINGALGORITHM_H

#include <string>
#include <map>
#include <utility>
#include <vector>
#include <set>

namespace gen_codes {

    struct ClusterDistance {
        unsigned int i_1;

        int weight;

        std::string Q_1;
        std::string Q_2;

        ClusterDistance(const std::string &acid_1, const std::string &acid_2) : weight(1) {
            for(int i = 0; i < acid_1.length(); ++i) {
                if(acid_1.substr(i,1) != acid_2.substr(i,1)) {
                    this->Q_1 = acid_1.substr(i,1);
                    this->Q_2 = acid_2.substr(i,1);
                    this->i_1 = i;
                    return;
                }
            }
        }
    };

    typedef struct BDA_Rules BDA_Rule;

    class CodonClusteringAlgorithm {
    public:
        explicit CodonClusteringAlgorithm(const std::vector<std::string> &);

        double get_average_conductance();

        double get_max_conductance();

        double get_min_conductance();

        std::string generate_value_table_csv_string();

        std::vector<std::vector<std::string> > generate_value_table_vec();

        std::vector<std::string> all_acids_in_order();

        std::string generate_value_table_file_csv_string(const std::string &filePath, const std::string &fileName);

    private:
        std::map<std::pair<std::string, std::string>, std::vector<ClusterDistance>> cluster_table;
        std::map<std::string, std::string> mapping_table;
        std::map<std::string, double> class_conductance_values;
        std::set<std::string> all_acids;

        bool is_calculated;

        void calculate_cluster_table_for_code(const std::vector<std::string> &code);

        void calculate_conductance_values();

        void setup_cluster();

        std::vector<std::string> all_tuples_in_cluster(const std::string &tuple);

        static std::vector<std::string> split_encoded_amino_acid(std::string s);
    };


}

#endif //GCATCPP_CLUSTERINGALGORITHM_H
