//
// Created by Martin on 10.10.2018.
//

#include "BaseValueGenerator.h"
#include "../modification/ShiftTuples.h"
#include "../codes/StdGenCode.h"
#include <utility>
#include <sstream>
#include <set>
#include <cstring>


BaseValueGenerator::BaseValueGenerator(std::map<std::string, int> base_values,
                                       std::vector<size_t> power_values) : AbstractGenerator(), base_values(
        std::move(base_values)), word_length(power_values.size()), power_values(std::move(power_values)) {

}

std::vector<std::string> BaseValueGenerator::run() {
    this->order_base_values();
    std::set<std::string> result_code;

    std::stringstream max_value_word;
    for (int i = 0; i < this->word_length; ++i) {
        max_value_word << base_list[0];
    }

    int max_value = this->value_of_word(max_value_word.str());
    int current_value = max_value - 1;
    int idx = 1;
    auto number_of_bases = static_cast<int>(this->base_list.size());
    while (max_value > current_value) {
        std::stringstream current_word;
        int new_value = idx++;
        for (int i = 0; i < this->word_length; i++) {
            current_word << this->base_list[new_value % number_of_bases];
            new_value /= number_of_bases;
        }

        std::string current_word_str = this->circular_permutation_with_lowest_value(current_word.str());
        current_value = this->value_of_word(current_word_str);

        if (StdGenCode({current_word_str}).is_circular()) {
            result_code.insert(current_word_str);
        }
    }

    std::vector<std::string> output(result_code.size());
    std::copy(result_code.begin(), result_code.end(), output.begin());

    return output;
}

void BaseValueGenerator::order_base_values() {
    this->base_list.empty();
    this->value_list.empty();

    for (const auto &myPair : this->base_values) {
        bool has_inserted = false;
        auto iterKeys = this->base_list.begin();
        for (auto iter = this->value_list.begin(); iter != this->value_list.end(); ++iter, ++iterKeys) {
            if (iter.operator*() < myPair.second) {
                this->value_list.insert(iter, myPair.second);
                this->base_list.insert(iterKeys, myPair.first);
                has_inserted = true;
                break;
            }
        }

        if (!has_inserted) {
            this->value_list.push_back(myPair.second);
            this->base_list.push_back(myPair.first);
        }
    }
}

int BaseValueGenerator::value_of_word(const std::string &word) {
    int value = 0;
    for (unsigned long i = 0; i < word.length(); ++i) {
        value += this->base_values.at(word.substr(i, 1)) * power_values[i];
    }

    return value;
}

std::string BaseValueGenerator::circular_permutation_with_lowest_value(std::string word) {
    std::string min_word = word;
    int value = this->value_of_word(word);
    ShiftTuples schifter;
    int shifter = 1;
    for (unsigned long i = 1; i < word.length(); ++i) {
        word = schifter.modify_word(word, &shifter);
        int new_value = this->value_of_word(word);
        if (new_value < value) {
            value = new_value;
            min_word = word;
        }
    }

    return min_word;
}

