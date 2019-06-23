//
// Created by Martin on 27.06.2018.
//

#ifndef CPPFOO_STDGENCODE_H
#define CPPFOO_STDGENCODE_H

#include "AbstractGenCode.h"


class StdGenCode : public AbstractGenCode{

public:
    explicit StdGenCode(const std::vector<std::string>& code_vec) : AbstractGenCode(code_vec){}

    StdGenCode(std::string sequence, unsigned int word_length) : AbstractGenCode(std::move(sequence), word_length){}

    StdGenCode(const StdGenCode &agc) = default;

    bool test_code() override;

    bool is_self_complementary() override;

protected:
};

#endif //CPPFOO_STDGENCODE_H
