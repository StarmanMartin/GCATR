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

    if(number > code->get_word_length()[0] || number < 0) {
        number = 0;
        this->add_error_msg("No negative shit or shift higher then word length possible");
    }

    auto u_number = (unsigned) number;
    auto code_vec = code->as_vector();
    for (auto &i : code_vec) {
        i = i.substr(u_number, (unsigned) code->get_word_length()[0]) + i.substr(0, u_number);
    }

    return code_vec;
}

std::string ShiftTuples::modify_word(std::string word, void *args) {
    unsigned long number = 1;
    if(args != nullptr) {
        number = (unsigned long)(*(int*)(args));
    }

    word = word.substr(number, word.length()) + word.substr(0, number);

    return word;
}
