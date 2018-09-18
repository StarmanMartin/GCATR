//
// Created by Martin on 18.09.2018.
//

#include <iostream>
#include <algorithm>
#include "CodonClusteringAlgorithm.h"


gen_codes::CodonClusteringAlgorithm::CodonClusteringAlgorithm(const std::vector<std::string> &code) : is_calculated(
        false) {
    this->calculate_cluster_table_for_code(code);
}

void gen_codes::CodonClusteringAlgorithm::calculate_cluster_table_for_code(const std::vector<std::string> &code) {
    this->cluster_table.clear();
    this->all_acids.clear();
    this->class_conductance_values.clear();

    for (int idx = 0; idx < code.size(); idx += 2) {
        auto acid_groups = all_acids_in_group(idx);
        this->all_acids.insert(code[idx + 1]);
        for (int acidIdx : acid_groups) {
            std::pair<std::string, std::string> key(code[idx + 1], code[acidIdx + 1]);
            if (!this->cluster_table.count(key)) {
                this->cluster_table[key] = 0;
            }

            this->cluster_table[key] += 1;
        }
    }
}

std::vector<int> gen_codes::CodonClusteringAlgorithm::all_acids_in_group(int idx) {
    if (idx == 104) {
        std::cout << "DEBUG";
    }
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
    double conductance_max = 0;

    for (const auto &conductance_value :  this->class_conductance_values) {
        conductance_max = std::max(conductance_value.second, conductance_max);
    }

    return conductance_max;
}

double gen_codes::CodonClusteringAlgorithm::get_min_conductance() {
    this->calculate_conductance_values();
    double conductance_min = 1;

    for (const auto &conductance_value :  this->class_conductance_values) {
        conductance_min = std::min(conductance_value.second, conductance_min);
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
