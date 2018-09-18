//
// Created by Martin on 27.06.2018.
//
#include <string>
#include <numeric>
#include <iostream>
#include <regex>
#include <utility>
#include <algorithm>
#include <sstream>
#include "StdGenCode.h"
#include "../tester/Circular.h"
#include "../tester/C_n.h"
#include "../tester/SelfComplimentary.h"
#include "../tester/CommaFree.h"

#include "../modification/ShiftTuples.h"

#include "../graph/Graph.h"


StdGenCode::StdGenCode(std::vector<std::string> code_vec) : AbstractGenCode(code_vec) {

}

StdGenCode::StdGenCode(std::string sequence, unsigned int word_length) : AbstractGenCode(std::move(sequence),
                                                                                         word_length) {

}

StdGenCode::StdGenCode(const StdGenCode &agc) = default;

bool StdGenCode::test_code() {
    if (this->is_tested || !AbstractGenCode::test_code()) {
        return this->is_ok;
    }


    this->word_length.empty();
    this->word_length.push_back((signed) this->code_vec[0].length());

    for (const std::string &word : this->code_vec) {
        if (this->word_length[0] != (signed) word.length()) {
            this->add_error_msg("Word size dose not match");
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

bool StdGenCode::is_cn_circular() {
    if (!this->test_code()) { return false; }
    auto tester = std::make_shared<C_n>();
    return this->run_test(tester);
}

bool StdGenCode::is_self_complementary() {
    if (!this->test_code()) { return false; }
    auto tester = std::make_shared<SelfComplimentary>();
    return this->run_test(tester);
}

bool StdGenCode::is_comma_free() {
    if (!this->test_code()) { return false; }
    auto tester = std::make_shared<CommaFree>();
    return this->run_test(tester);
}

void StdGenCode::shift_tuples(int shifts) { // NOLINT
    if (!this->test_code()) { return; }
    auto tester = std::make_shared<ShiftTuples>();
    this->run_modification(tester, &shifts);
}

seq::Seq_Result StdGenCode::find_code_in_sequence(const std::string &seq) {
    this->test_code();
    seq::Seq_Result result = seq::Seq_Result(seq);
    std::stringstream rest;
    std::stringstream parts;
    unsigned int current_match_length = 0;
    for (int i = 0; i < seq.length(); i += this->word_length[0]) {
        bool found = false;
        std::string seq_word = seq.substr(static_cast<unsigned long>(i),
                                          static_cast<unsigned long>(this->word_length[0]));

        for (const std::string &word : this->code_vec) {
            if (seq_word == word) {
                result.words.emplace_back(seq_word);
                result.idx_list.emplace_back(i);
                current_match_length += this->word_length[0];
                found = true;
                break;
            }
        }

        parts.seekg(0, std::ios::end);
        auto size = (int) parts.tellg();

        if(!found && current_match_length > 0 || found && current_match_length == this->word_length[0]) {
            result.parts.emplace_back(parts.str());
            parts.clear();//clear any bits set
            parts.str(std::string());
        }

        parts << seq_word;

        if (!found) {
            rest << seq_word;
            result.longest_match = std::max(current_match_length, result.longest_match);
            result.total_match_in_percent += current_match_length;
            current_match_length = 0;
        }
    }

    result.parts.emplace_back(parts.str());
    result.rest = rest.str();
    result.total_match_in_percent = 100.0 * (result.total_match_in_percent / (double) seq.length());

    return result;

}


void StdGenCode::setTranslTableByIdx(int idx) {
    return AbstractGenCode::setTranslTableByIdx(idx, 3);
}

void StdGenCode::setTranslTableByName(const std::string &name) {
    return  AbstractGenCode::setTranslTableByName(name, 3);
}

void StdGenCode::setTranslTableToStandardCode() {
    return  AbstractGenCode::setTranslTableToStandardCode(3);
}
