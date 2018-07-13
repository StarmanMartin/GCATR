//
// Created by Martin on 27.06.2018.
//
#include <string>
#include <numeric>
#include <iostream>
#include <regex>

#include "StdGenCode.h"
#include "../tester/Circular.h"
#include "../modification/ShiftTuples.h"


StdGenCode::StdGenCode(std::vector<std::string> code_vec) : AbstractGenCode(code_vec) {

}


bool StdGenCode::test_code() {

    if (!AbstractGenCode::test_code()) {
        return this->is_ok;
    }


    this->word_length.empty();
    this->word_length.push_back((signed) this->code_vec[0].length());

    for (std::string word : this->code_vec) {
        if (this->word_length[0] != (signed) word.length()) {
            this->error_msg = "Word size dose not match";
            this->word_length.empty();
            return (this->is_ok = false);
        }
    }

    return (this->is_ok = true);
}

bool StdGenCode::is_circular() {
    if (!this->test_code()) { return false; }
    auto tester = std::make_shared<Circular>();
    return this->run_test(tester);
}

void StdGenCode::shift_tuples(int shifts) {
    if (!this->test_code()) { return; }
    auto tester = std::make_shared<ShiftTuples>();
    this->run_modification(tester, &shifts);
}