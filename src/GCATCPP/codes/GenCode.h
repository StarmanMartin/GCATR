//
// Created by Martin on 27.06.2018.
//

#ifndef CPPFOO_GENCODE_H
#define CPPFOO_GENCODE_H

#include "AbstractGenCode.h"


class GenCode : public AbstractGenCode{

public:
    explicit GenCode(const std::vector<std::string>& code_vec) : AbstractGenCode(code_vec){}

    GenCode(std::string sequence, unsigned int word_length) : AbstractGenCode(std::move(sequence), word_length){}

    GenCode(const GenCode &agc) = default;

    bool test_code() override;

protected:
};

#endif //CPPFOO_GENCODE_H
