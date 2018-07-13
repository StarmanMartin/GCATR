//
// Created by Martin on 13.07.2018.
//

#include "ShiftTuples.h"
#include "../codes/AbstractGenCode.h"

std::vector<std::string> ShiftTuples::modify(AbstractGenCode *code, void* args) {
    int number = 1;
    if(args != NULL) {
        number = *(int*)(args);
    }

    if(number > code->get_word_length()[0] || number < 0) {
        number = 0;
        this->error_msg = "No negative shit or shift higher then word length possible";
    }

    unsigned int u_number = (unsigned) number;
    auto code_vec = code->as_vector();
    for(int i = 0;i < code_vec.size(); ++i  ) {

        code_vec[i] = code_vec[i].substr(u_number, (unsigned) code->get_word_length()[0]) + code_vec[i].substr(0, u_number);
    }

    return code_vec;
}