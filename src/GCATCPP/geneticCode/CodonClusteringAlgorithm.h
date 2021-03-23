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

        std::string v_1;
        std::string v_2;

        bool in_cluster;

        ClusterDistance(const std::string &acid_1, const std::string &acid_2, bool in_cluster) :
                weight(1),
                v_1(acid_1),
                v_2(acid_2),
                in_cluster(in_cluster) {
            for (int i = 0; i < acid_1.length(); ++i) {
                if (acid_1.substr(i, 1) != acid_2.substr(i, 1)) {
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

        double get_conductance_of_cluster(const std::string &);

        double get_min_conductance();

        std::string generate_value_table_csv_string();

        std::vector<std::vector<std::string> > generate_value_table_vec();

        std::vector<std::string> all_acids_in_order();

        std::string generate_value_table_file_csv_string(const std::string &filePath, const std::string &fileName);

        void add_weight(unsigned int pos, const std::string &from, const std::string &to, int weight);
        void r_add_weight(unsigned int pos, const std::string &from, const std::string &to, int weight);

        void add_weight(unsigned int pos, const std::string &from, int weight);

        void add_weight(unsigned int pos, int weight);

        void add_weight_stable_base(unsigned int pos, const std::string &base, int weight);

    private:
        std::map<std::string, std::vector<ClusterDistance>> cluster_set;
        std::map<std::pair<std::string, std::string>, int> cluster_table;
        std::map<std::string, std::string> mapping_table;
        std::map<std::string, double> class_conductance_values;
        std::set<std::string> all_acids;

        bool is_calculated;
        bool is_setup = false;

        void calculate_cluster_table_for_code(const std::vector<std::string> &code);

        void calculate_conductance_values();

        void setup_cluster();

        std::vector<std::string> all_tuples_in_cluster(const std::string &tuple);

        static std::vector<std::string> split_encoded_amino_acid(std::string s);

        double _get_conductance_of_cluster(const std::string &from_acid);


    };


}

#endif //GCATCPP_CLUSTERINGALGORITHM_H
