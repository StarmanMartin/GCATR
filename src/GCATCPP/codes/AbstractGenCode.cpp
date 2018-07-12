//
// Created by Martin on 27.06.2018.
//
#include <string>
#include <numeric>
#include <iostream>
#include <regex>

#include "AbstractGenCode.h"

#define EMPTY_SEQUNECE "#"



AbstractGenCode::AbstractGenCode( std::vector <std::string> code_vec) :
        code_vec(code_vec), is_tested(false), is_ok(false), string_sequence(EMPTY_SEQUNECE) {
    std::vector<int> temp_length(0);
    this->word_length = temp_length;

    std::vector< std::vector<unsigned int> > temp_circle(0);
    this->circle = temp_circle;

}


bool AbstractGenCode::test() {
    if (this->is_tested) {
        return this->is_ok;
    }

    this->is_tested = true;
    this->is_ok = true;

    if (this->code_vec.size() == 0) {
        this->error_msg = "Code is empty";
        return (this->is_ok = false);
    }

    return true;
}

std::string AbstractGenCode::as_string_sequence() {
    if (this->string_sequence != EMPTY_SEQUNECE) {
        return this->string_sequence;
    }

    std::string result;
    for (std::string const &s : this->code_vec) { result += s; }

    return this->string_sequence = result;
}

void AbstractGenCode::add_circle(std::vector<unsigned int> chained_indexes) {
    int min_pos = int(distance(chained_indexes.begin(), min_element(chained_indexes.begin(), chained_indexes.end())));
    std::rotate(chained_indexes.begin(), chained_indexes.begin() + min_pos, chained_indexes.end());

    for (auto vector : this->circle) {
        if (equal(vector.begin(), vector.end(), chained_indexes.begin())) {
            return;
        }
    }

    this->circle.push_back(chained_indexes);
}