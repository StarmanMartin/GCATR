//
// Created by Martin on 18.09.2018.
//

#include <algorithm>
#include <iterator>
#include <sstream>
#include <iostream>
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

    auto mapping_table = std::map<std::string, std::string>();
    for (int idx = 0; idx < code.size(); idx += 2) {
        mapping_table.insert(std::pair<std::string, std::string>(code[idx], code[idx+1]));
    }

    for (int idx = 0; idx < code.size(); idx += 2) {
        auto acid_groups = gen_codes::CodonClusteringAlgorithm::all_acids_in_cluster(idx);

        auto translated_from_amino_acids = gen_codes::CodonClusteringAlgorithm::split_encoded_amino_acid(code[idx + 1]);
        for (const auto& single_from_acid : translated_from_amino_acids) {
            this->all_acids.insert(single_from_acid);
            for (int acidIdx : acid_groups) {
                auto translated_to_amino_acids = gen_codes::CodonClusteringAlgorithm::split_encoded_amino_acid(
                        code[acidIdx + 1]);
                for (const auto& single_to_acid : translated_to_amino_acids) {
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

std::vector<int> gen_codes::CodonClusteringAlgorithm::all_acids_in_cluster(int idx) {
    idx /= 2;
    int startSecond = (idx / 4) * 4;
    int startFirst = idx % 16;
    int startThird = (idx % 4) + (idx / 16) * 16;
    std::vector<int> a;
    for (int i = 0; i < 4; i++) {
        int firstLetter = startFirst + (i * 16);
        if (firstLetter != idx) {
            a.push_back(firstLetter * 2);
        }

        int secondLetter = startSecond + i;
        if (secondLetter != idx) {
            a.push_back(secondLetter * 2);
        }

        int thirdLetter = startThird + (i * 4);
        if (thirdLetter != idx) {
            a.push_back(thirdLetter * 2);
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

    this->is_calculated = true;

    for (const auto &from_acid : this->all_acids) {

        double denominator = 0;
        double numerator = 0;
        for (const auto &to_acid : this->all_acids) {
            std::pair<std::string, std::string> key(from_acid, to_acid);
            if (to_acid != from_acid) {
                numerator += this->cluster_table[key];
            }
            denominator += this->cluster_table[key];

        }

        this->class_conductance_values[from_acid] = numerator / denominator;
    }
}

void gen_codes::CodonClusteringAlgorithm::generate_value_table_file_csv_string(const std::string& filePath,const std::string& fileName) {
    if(!std_m::FileManager::getInstance().is_dir(filePath)) { // Dir does not exists;
        return;
    }

    std_m::FileManager::getInstance().write_file(filePath + "/" + fileName, ".csv", this->generate_value_table_csv_string());
}

std::string gen_codes::CodonClusteringAlgorithm::generate_value_table_csv_string() {
    auto csv_vec_length = static_cast<unsigned int>(this->all_acids.size() + 1);
   std::vector<std::string> csv_res(csv_vec_length*csv_vec_length);
   int idx = 0;
   for (const auto &from_acid : this->all_acids) {
       csv_res[idx+1] = from_acid;
       int inner_idx = csv_vec_length * (idx + 1) + 1;
       for (const auto &to_acid : this->all_acids) {
           std::pair<std::string, std::string> key(from_acid, to_acid);
           csv_res[inner_idx++] = std::to_string(this->cluster_table[key]);
       }
       csv_res[(csv_vec_length * (idx+1))] = "\n" + from_acid;
       ++idx;
    }


    const char* const delim = ";";

    std::stringstream imploded;
    std::copy(csv_res.begin(), csv_res.end(),
              std::ostream_iterator<std::string>(imploded, delim));

    return imploded.str();
}

std::vector< std::vector<std::string> > gen_codes::CodonClusteringAlgorithm::generate_value_table_vec() {
    auto csv_vec_length = static_cast<unsigned int>(this->all_acids.size());
    std::vector< std::vector<std::string> > value_table(csv_vec_length);
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
        unsigned long index = str.find(token);
        if (index != std::string::npos && index < str.length()) {
            result.push_back(str.substr(0, index));
            str = str.substr(index + token.size());
            if (str.empty()){
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
    std::vector <std::string> output;
    std::copy(this->all_acids.begin(), this->all_acids.end(), output.begin());
    return output;
}
