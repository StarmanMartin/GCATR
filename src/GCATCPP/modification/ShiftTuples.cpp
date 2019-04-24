//
// Created by Martin on 13.07.2018.
//

#include "ShiftTuples.h"
#include "../codes/AbstractCode.h"

std::vector<std::string> ShiftTuples::modify(AbstractCode *code, void* args) {
    int number = 1;
    if(args != nullptr) {
        number = *(int*)(args);
    }

    if(number < 0) {
        number = 0;
        this->add_error_msg("No negative shit or shift higher then word length possible");
    }

    auto u_number = (unsigned) number;
    auto code_vec = code->as_vector();
    for (auto &i : code_vec) {
        i = this->shift_tuple(i, u_number);
    }

    return code_vec;
}

std::string ShiftTuples::modify_word(std::string word, void *args) {
    unsigned long number = 1;
    if(args != nullptr) {
        number = (unsigned long)(*(int*)(args));
    }

    if(number < 0) {
        number = 0;
        this->add_error_msg("No negative shit or shift higher then word length possible");
    }

    return this->shift_tuple(word, number);

}

std::string ShiftTuples::shift_tuple(std::string word, size_t number) {
    number = number % word.length();
    word = word.substr(number, word.length()) + word.substr(0, number);

    return word;
}
