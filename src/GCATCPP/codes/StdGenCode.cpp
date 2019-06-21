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



bool StdGenCode::test_code() {
    if (this->is_tested || !AbstractGenCode::test_code()) {
        return this->is_ok;
    }

    if(this->word_length.size() != 1 || this->word_length[0] != 3) {
        return (this->is_ok = false);
    }


    return (this->is_ok = true);
}

bool StdGenCode::is_self_complementary() {
    if (!this->test_code()) { return false; }
    auto tester = std::make_shared<SelfComplimentary>();
    return this->run_test(tester);
}


void StdGenCode::setTranslTableByIdx(int idx) {
    return AbstractGenCode::setTranslTableByIdx(idx, 3);
}

void StdGenCode::setTranslTableByName(const std::string &name) {
    return AbstractGenCode::setTranslTableByName(name, 3);
}

void StdGenCode::setTranslTableToStandardCode() {
    return AbstractGenCode::setTranslTableToStandardCode(3);
}
