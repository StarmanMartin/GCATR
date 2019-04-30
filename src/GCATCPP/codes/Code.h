//
// Created by Martin on 2/7/2019.
//

#ifndef GCATCPP_CODE_H
#define GCATCPP_CODE_H


#include "AbstractCode.h"

class Code : public AbstractCode {
public:
    explicit Code(const std::vector<std::string> &);
    explicit Code(std::string, unsigned int);

    Code(const Code &agc);

    virtual bool test_code() override;
    virtual bool is_k_circular(int k) override;

    bool is_circular() override;
    bool is_cn_circular() override;
    bool is_comma_free() override;
    seq::Seq_Result find_code_in_sequence(const std::string &seq) override;
    void shift_tuples(int shifts=1) override; // NOLINT

protected:
};

#endif //GCATCPP_CODE_H