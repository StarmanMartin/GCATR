//
// Created by Martin on 13.07.2018.
//

#include "ShiftTuples.h"
#include "../codes/AbstractCode.h"

std::vector<std::string> ShiftTuples::modify(AbstractCode *code) {
    if(this->number < 0) {
        this->add_error_msg("No negative shit or shift higher than word length possible");
    }

    auto code_vec = code->as_vector();
    for (auto &i : code_vec) {
        i = this->shift_tuple(i, this->number);
    }

    return code_vec;
}

std::string ShiftTuples::modify_word(std::string word) {
    if(this->number < 0) {
        this->add_error_msg("No negative shit or shift higher than word length possible");
        return word;
    }

    return this->shift_tuple(word, this->number);

}

std::string ShiftTuples::shift_tuple(std::string word, size_t shift_number) {
    shift_number = AbstractCode::calculateModulo(shift_number, word.length());;
    word = word.substr(shift_number, word.length()) + word.substr(0, shift_number);

    return word;
}
