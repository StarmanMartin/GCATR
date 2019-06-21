//
// Created by martins on 18.06.19.
//

#include "TesseraCode.h"
#include "../tester/SelfComplimentary.h"

bool TesseraCode::test_code() {
    if (this->is_tested || !AbstractGenCode::test_code()) {
        return this->is_ok;
    }

    if(this->word_length.size() != 1 || this->word_length[0] != 4) {
        return (this->is_ok = false);
    }


    return (this->is_ok = true);
}

bool TesseraCode::is_self_complementary() {
    if (!this->test_code()) { return false; }
    auto tester = std::make_shared<SelfComplimentary>();
    return this->run_test(tester);
}


void TesseraCode::setTranslTableByIdx(int idx) {
    return AbstractGenCode::setTranslTableByIdx(idx, 3);
}

void TesseraCode::setTranslTableByName(const std::string &name) {
    return AbstractGenCode::setTranslTableByName(name, 3);
}

void TesseraCode::setTranslTableToStandardCode() {
    return AbstractGenCode::setTranslTableToStandardCode(3);
}