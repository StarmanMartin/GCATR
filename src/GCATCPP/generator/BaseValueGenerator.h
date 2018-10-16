//
// Created by Martin on 10.10.2018.
//

#ifndef GCATCPP_BASEVALUEGENERATOR_H
#define GCATCPP_BASEVALUEGENERATOR_H


#include "AbstractGenerator.h"
#include <map>


class BaseValueGenerator : AbstractGenerator {
public:
    BaseValueGenerator(std::map<std::string, int>, std::vector<size_t>);

    std::vector<std::string> run() override;

private:
    std::map<std::string, int> base_values;

    std::vector<std::string> base_list;
    std::vector<int> value_list;


    size_t word_length;
    std::vector<size_t> power_values;

    void order_base_values();

    int value_of_word(const std::string &word);

    std::string circular_permutation_with_lowest_value(std::string word);
};


#endif //GCATCPP_BASEVALUEGENERATOR_H
