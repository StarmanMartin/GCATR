//
// Created by Martin on 2/7/2019.
//



//
// Created by Martin on 27.06.2018.
//
#include <string>
#include <iostream>
#include <regex>
#include "StdGenCode.h"
#include "../tester/Circular.h"
#include "../tester/KCircular.h"
#include "../tester/C_n.h"
#include "../tester/CommaFree.h"

#include "../modification/ShiftTuples.h"
#include "../modification/TransformTuples.h"

#define EMPTY_SEQUNECE "#"


Code::Code(const std::string& sequence, unsigned int word_length) : AbstractCode(sequence, word_length) {}

Code::Code(const std::vector<std::string>& code_vec) : AbstractCode(code_vec) {}

Code::Code(const Code& agc) : AbstractCode(agc) {}


bool Code::test_code() {
    if (this->is_tested || !AbstractCode::test_code()) {
        return this->is_ok;
    }

    if (this->word_length.size() != 1) {
        this->add_error_msg("Word size dose not match");
        this->word_length.clear();
        return (this->is_ok = false);
    }

    return (this->is_ok = true);
}

bool Code::is_circular() {
    if (!this->test_code()) { return false; }
    auto tester = std::make_shared<Circular>();
    return this->run_test(tester);
}

bool Code::is_k_circular(int k) {
    if (!this->test_code()) { return false; }
    auto tester = std::make_shared<KCircular>();
    return this->run_test(tester, k);
}

bool Code::is_cn_circular() {
    if (!this->test_code()) { return false; }
    auto tester = std::make_shared<C_n>();
    return this->run_test(tester);
}

bool Code::is_comma_free() {
    if (!this->test_code()) { return false; }
    auto tester = std::make_shared<CommaFree>();
    return this->run_test(tester);
}

void Code::shift_tuples(size_t shifts) { // NOLINT
    if (!this->test_code()) { return; }
    auto tester = std::make_shared<ShiftTuples>(shifts);
    this->run_modification(tester);
}

seq::Seq_Result Code::find_code_in_sequence(const std::string& seq, int frame) {
    if(seq.length() == 0) {
        this->add_error_msg("Sequence should not be empty");
        throw  std::invalid_argument("Sequence should not be empty!");
    }
    int actualFrame = Code::calculateModulo(frame, seq.length());
    this->test_code();
    std::string firstPart = seq.substr(actualFrame, seq.length() - actualFrame);
    std::string secondPart = seq.substr(0, actualFrame);
    std::string copyInFrameShift = firstPart.append(secondPart);

    seq::Seq_Result result = seq::Seq_Result(copyInFrameShift);
    std::stringstream rest;
    std::stringstream parts;
    unsigned int current_match_length = 0;
    for (int i = 0; i < copyInFrameShift.length(); i += this->word_length[0]) {
        bool found = false;
        std::string seq_word = copyInFrameShift.substr(static_cast<unsigned long>(i),
            static_cast<unsigned long>(this->word_length[0]));

        for (const std::string& word : this->code_vec) {
            if (seq_word == word) {
                result.words.emplace_back(seq_word);
                result.circularPermutations.emplace_back(1);
                result.idx_list.emplace_back(i + actualFrame);
                current_match_length += this->word_length[0];
                found = true;
                break;
            }
        }
        if(!found) {
            std::size_t shif_idx = 1;
            std::size_t res_value = 0;
            while(shif_idx <= word_length[0]) {
                ShiftTuples shifter(shif_idx);
                auto temp_seq_word = shifter.modify_word(seq_word);
                shif_idx++;
                for (const std::string& word : this->code_vec) {
                    if (temp_seq_word == word) {
                        res_value = shif_idx;
                        shif_idx = -1;
                        break;
                    }
                }

            }
            result.circularPermutations.emplace_back(res_value);
        }

        parts.seekg(0, std::ios::end);
        auto size = (int)parts.tellg();

        if ((!found && current_match_length > 0) || (found && current_match_length == this->word_length[0])) {
            result.parts.emplace_back(parts.str());
            parts.clear();//clear any bits set
            parts.str(std::string());
        }

        parts << seq_word;

        if (!found) {
            rest << seq_word;
            result.longest_match = std::max(current_match_length, result.longest_match);
            current_match_length = 0;
        }

        if (i == (copyInFrameShift.length() - this->word_length[0]) && found) {
            result.longest_match = std::max(current_match_length, result.longest_match);
        }
    }

    result.parts.emplace_back(parts.str());
    result.rest = rest.str();
    result.total_match_in_percent = 100.0 * ((result.words.size() * this->word_length[0]) / (double) copyInFrameShift.length());

    return result;

}

void Code::transform_tuples(const std::string& from_rule, const std::string& to_rule) { // NOLINT
    if (!this->test_code()) { return; }
    auto tester = std::make_shared<TransformTuples>(from_rule, to_rule);
    this->run_modification(tester);
}
