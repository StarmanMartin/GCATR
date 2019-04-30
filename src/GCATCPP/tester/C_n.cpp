//
// Created by Martin on 16.07.2018.
//

#include "C_n.h"
#include <iostream>

bool C_n::test(AbstractCode *code) {
    bool is_circular = true;

    for(int i = 0; i < code->get_word_length()[0]; ++i) {
        code->shift_tuples();
        is_circular = is_circular && this->is_circular(code);
    }

    return is_circular;
}