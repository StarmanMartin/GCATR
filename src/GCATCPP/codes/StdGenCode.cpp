//
// Created by Martin on 27.06.2018.
//
#include <string>
#include <regex>
#include "StdGenCode.h"
#include "../tester/Circular.h"

#include "../modification/ShiftTuples.h"


bool StdGenCode::test_code() {
    if (this->is_tested || !AbstractGenCode::test_code()) {
        return this->is_ok;
    }

    if(this->word_length.size() != 1 || this->word_length[0] != 3) {
        return (this->is_ok = false);
    }


    return (this->is_ok = true);
}

bool StdGenCode::is_translatable() {
    return this->test_code();
}
