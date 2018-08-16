//
// Created by Martin on 27.06.2018.
//

#ifndef CPPFOO_STDGENCODE_H
#define CPPFOO_STDGENCODE_H

#include "AbstractGenCode.h"


class StdGenCode : public AbstractGenCode{

public:
    explicit StdGenCode(std::vector<std::string>);
    StdGenCode(std::string, unsigned int);
    StdGenCode(const StdGenCode &agc);

    bool test_code() override;

    bool is_circular() override;
    bool is_cn_circular() override;
    bool is_self_complementary() override;
    bool is_comma_free() override;
    seq::Seq_Result find_code_in_sequence(const std::string &seq) override;
    void shift_tuples(int shifts=1) override; // NOLINT

protected:
};

#endif //CPPFOO_STDGENCODE_H
