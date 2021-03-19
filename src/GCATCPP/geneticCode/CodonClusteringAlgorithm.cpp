//
// Created by Martin on 18.09.2018.
//

#include <algorithm>
#include <iterator>
#include <sstream>
#include <iostream>
#include <regex>
#include "CodonClusteringAlgorithm.h"
#include "../helper/FileManager.h"


gen_codes::CodonClusteringAlgorithm::CodonClusteringAlgorithm(const std::vector<std::string> &code) : is_calculated(
        false) {
    this->calculate_cluster_table_for_code(code);
}

void gen_codes::CodonClusteringAlgorithm::calculate_cluster_table_for_code(const std::vector<std::string> &code) {
    this->cluster_table.clear();
    this->all_acids.clear();
    this->class_conductance_values.clear();
    this->mapping_table.clear();

    for (int idx = 0; idx < code.size(); idx += 2) {
        this->mapping_table.insert(std::pair<std::string, std::string>(code[idx], code[idx + 1]));
    }
}

void gen_codes::CodonClusteringAlgorithm::setup_cluster() {
    if (this->is_setup) {
        return;
    }

    this->is_setup = true;
    for (const auto &elem : this->mapping_table) {
        auto acid_groups = gen_codes::CodonClusteringAlgorithm::all_tuples_in_cluster(elem.first);

        auto translated_from_amino_acids = gen_codes::CodonClusteringAlgorithm::split_encoded_amino_acid(elem.second);
        for (const auto &single_from_acid : translated_from_amino_acids) {
            this->all_acids.insert(single_from_acid);
            for (const std::string &acidIdx : acid_groups) {
                auto translated_to_amino_acids = gen_codes::CodonClusteringAlgorithm::split_encoded_amino_acid(
                        this->mapping_table[acidIdx]);
                bool in_cluster = std::find(translated_to_amino_acids.begin(), translated_to_amino_acids.end(),
                                            single_from_acid) != translated_to_amino_acids.end();
                this->cluster_set[single_from_acid].push_back(
                        gen_codes::ClusterDistance(elem.first, acidIdx, in_cluster));
                for (const auto &single_to_acid : translated_to_amino_acids) {
                    std::pair<std::string, std::string> key(single_from_acid, single_to_acid);
                    if (!this->cluster_table.count(key)) {
                        this->cluster_table[key] = 0;
                    }

                    this->cluster_table[key] += 1;
                }
            }
        }
    }
}

std::vector<std::string> gen_codes::CodonClusteringAlgorithm::all_tuples_in_cluster(const std::string &tuple) {
    std::vector<std::string> a;
    std::stringstream ss_key_regexp;
    for (size_t i = 0; i < tuple.length(); ++i) {
        if (i != 0) {
            ss_key_regexp << "|";
        }
        ss_key_regexp << "(" << tuple.substr(0, i) << "[^" << tuple.substr(i, 1) << "]" << tuple.substr(i + 1) << ")";

    }
    std::regex key_regexp(ss_key_regexp.str());
    for (const auto &elem : this->mapping_table) {
        if (std::regex_search(elem.first, key_regexp)) {
            a.push_back(elem.first);
        }
    }

    return a;
}

double gen_codes::CodonClusteringAlgorithm::get_average_conductance() {
    this->calculate_conductance_values();
    double conductance_average = 0;
    int conductance_average_counter = 0;

    for (const auto &conductance_value :  this->class_conductance_values) {
        conductance_average += conductance_value.second;
        ++conductance_average_counter;
    }

    conductance_average /= (double) conductance_average_counter;

    return conductance_average;
}

double gen_codes::CodonClusteringAlgorithm::get_max_conductance() {
    this->calculate_conductance_values();
    double conductance_max = 1;

    for (const auto &conductance_value :  this->class_conductance_values) {
        conductance_max = std::min(conductance_value.second, conductance_max);
    }

    return conductance_max;
}

double gen_codes::CodonClusteringAlgorithm::get_min_conductance() {
    this->calculate_conductance_values();
    double conductance_min = 0;

    for (const auto &conductance_value :  this->class_conductance_values) {
        conductance_min = std::max(conductance_value.second, conductance_min);
    }

    return conductance_min;
}

void gen_codes::CodonClusteringAlgorithm::calculate_conductance_values() {
    if (this->is_calculated) {
        return;
    }

    this->setup_cluster();

    this->is_calculated = true;

    for (const auto &from_acid : this->all_acids) {
        this->_get_conductance_of_cluster(from_acid);
    }
}

std::string gen_codes::CodonClusteringAlgorithm::generate_value_table_file_csv_string(const std::string &filePath,
                                                                                      const std::string &fileName) {

    return std_m::FileManager::getInstance().write_file(filePath + "/" + fileName, ".csv",
                                                        this->generate_value_table_csv_string());
}

std::string gen_codes::CodonClusteringAlgorithm::generate_value_table_csv_string() {
    this->setup_cluster();
    auto csv_vec_length = static_cast<unsigned int>(this->all_acids.size() + 1);
    std::vector<std::string> csv_res(csv_vec_length * csv_vec_length);
    int idx = 0;
    for (const auto &from_acid : this->all_acids) {
        csv_res[idx + 1] = from_acid;
        int inner_idx = csv_vec_length * (idx + 1) + 1;
        for (const auto &to_acid : this->all_acids) {
            std::pair<std::string, std::string> key(from_acid, to_acid);
            csv_res[inner_idx++] = std::to_string(this->cluster_table[key]);
        }
        csv_res[(csv_vec_length * (idx + 1))] = "\n" + from_acid;
        ++idx;
    }


    const char *const delim = ";";

    std::stringstream imploded;
    std::copy(csv_res.begin(), csv_res.end(),
              std::ostream_iterator<std::string>(imploded, delim));

    return imploded.str();
}

std::vector<std::vector<std::string> > gen_codes::CodonClusteringAlgorithm::generate_value_table_vec() {
    auto csv_vec_length = static_cast<unsigned int>(this->all_acids.size());
    std::vector<std::vector<std::string> > value_table(csv_vec_length);
    int idx = 0;
    for (const auto &from_acid : this->all_acids) {
        std::vector<std::string> value_row(csv_vec_length);
        int inner_idx = 0;
        for (const auto &to_acid : this->all_acids) {
            std::pair<std::string, std::string> key(from_acid, to_acid);
            value_row[inner_idx++] = std::to_string(this->cluster_table[key]);
        }
        value_table[idx++] = value_row;
    }

    return value_table;
}

std::vector<std::string> gen_codes::CodonClusteringAlgorithm::split_encoded_amino_acid(std::string str) {
    static const std::string token = "_";
    std::vector<std::string> result;
    while (!str.empty()) {
        auto index = str.find(token);
        if (index != std::string::npos && index < str.length()) {
            result.push_back(str.substr(0, index));
            str = str.substr(index + token.size());
            if (str.empty()) {
                result.push_back(str);
            }
        } else {
            result.push_back(str);
            return result;
        }
    }

    return result;
}

std::vector<std::string> gen_codes::CodonClusteringAlgorithm::all_acids_in_order() {
    std::vector<std::string> output;
    std::copy(this->all_acids.begin(), this->all_acids.end(), output.begin());
    return output;
}

double gen_codes::CodonClusteringAlgorithm::get_conductance_of_cluster(const std::string &from_acid) {
    this->setup_cluster();
    return this->_get_conductance_of_cluster(from_acid);
}

double gen_codes::CodonClusteringAlgorithm::_get_conductance_of_cluster(const std::string &from_acid) {
    double denominator = 0;
    double numerator = 0;
    for (const auto &elm : this->cluster_set[from_acid]) {
        if (not elm.in_cluster) {
            numerator += elm.weight;
        }
        denominator += elm.weight;
    }


    this->class_conductance_values[from_acid] = numerator / denominator;
}

void gen_codes::CodonClusteringAlgorithm::add_weight(unsigned int pos, const std::string &from, const std::string &to,
                                                     int weight) {
    bool has_target = to.length() != 0;

    if (has_target && (from.length() != to.length() || from == to)) {
        throw std::invalid_argument("Length of from and to must be the same");
    }

    if (pos < 1) {
        throw std::invalid_argument("pos mus be in 1, ...., tuple size");
    }
    this->setup_cluster();
    pos--;

    for (const auto &acid : this->all_acids) {
        for (auto &elm : this->cluster_set[acid]) {
            if (pos == elm.i_1 && elm.v_1.substr(pos, from.length()) == from) {
                if (!has_target || elm.v_2.substr(pos, from.length()) == to) {
                    elm.weight += weight;
                }
            }
        }
    }

}

void gen_codes::CodonClusteringAlgorithm::add_weight(unsigned int pos, const std::string &from, int weight) {
    this->add_weight(pos, from, "", weight);
}


void gen_codes::CodonClusteringAlgorithm::add_weight(unsigned int pos, int weight) {
    this->add_weight(pos, "", weight);
}

void
gen_codes::CodonClusteringAlgorithm::add_weight_stable_base(unsigned int pos, const std::string &base, int weight) {
    if (pos < 1) {
        throw std::invalid_argument("pos mus be in 1, ...., tuple size");
    }
    this->setup_cluster();
    pos--;

    for (const auto &acid : this->all_acids) {
        for (auto &elm : this->cluster_set[acid]) {
            if (pos != elm.i_1 && elm.v_1.substr(pos, base.length()) == base) {
                elm.weight += weight;
            }
        }
    }
}
